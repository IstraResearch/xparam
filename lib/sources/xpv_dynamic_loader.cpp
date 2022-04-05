/*	Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * As a special exception, the copyright holders give permission
 * for additional uses of the text contained in its release of XPARAM.
 *
 * The exception is that, if you link the XPARAM library with other files
 * to produce an executable, this does not by itself cause the
 * resulting executable to be covered by the GNU General Public License.
 * Your use of that executable is in no way restricted on account of
 * linking the XPARAM library code into it.
 *
 * This exception does not however invalidate any other reasons why
 * the executable file might be covered by the GNU General Public License.
 *
 * If you write modifications of your own for XPARAM, it is your choice
 * whether to permit this exception to apply to your modifications.
 * If you do not wish that, delete this exception notice.  
 */

#pragma warning (disable: 4786)

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iterator>
#include "../src_include/xp_sstream.h"
#include "../xparam/xp_error.h"
#include "../src_include/xpv_dynamic_loader.h"
#include "../src_include/xpv_dynamic_loader_parser.h"
#include "../xparam/xpv_registry.h"
#include "../src_include/xp_file_utils.h"

using namespace std;

//////////////////////////////////////////////////////////////
// NO DYNAMIC LOADING 
//////////////////////////////////////////////////////////////

#ifdef NO_DYNAMIC_LOADING

namespace xParam_internal {
	void dynamic_load(const string& type_name)
	{
		throw Error("Unknown type name - '" + type_name + "'");
	}
} // end namespace xParam_internal

#else // dyanmic loading enabled

//////////////////////////////////////////////////////////////
// DynamicLoader base class
//////////////////////////////////////////////////////////////
namespace xParam_internal {

class DynamicLoaderBase {
public:
	void load(const string& type_name) const;
	static string mapfile_extension() {return "xpn";}
	
private:
	vector<string> get_path() const;
	string full_path(const string& dir, const string& file) const;
	vector<string> get_mapfiles(const vector<string>& path) const;
		
protected:
	virtual vector<string> 
		get_mapfiles_in(const string& dir) const = 0;
	
	virtual void load_lib(const string& full_libname) const = 0;
};


void DynamicLoaderBase::load(const string& type_name) const
{
	try {
		vector<string> path = get_path();

		vector<string>::const_iterator iDir;
		for (iDir=path.begin(); iDir!=path.end(); ++iDir) {
			vector<string> mapfiles = get_mapfiles_in(*iDir);
			
			vector<string>::const_iterator iFile;
			for (iFile=mapfiles.begin(); iFile!=mapfiles.end(); ++iFile) {
				string filename = full_path(*iDir,*iFile);

				// open and parse mapfile for libs matched to 'type_name'
				vector<string> libs = matching_libs(filename,type_name);
				
				// match not found for this mapfile - go to next
				if (libs.empty())
					continue;
				
				// match found - load all mapped libraries
				vector<string>::const_iterator iLib;
				for (iLib=libs.begin(); iLib!=libs.end(); ++iLib) {
					string full_libname = *iLib;
					if (FileUtils::is_relative(*iLib))
						full_libname = full_path(*iDir,*iLib);

					try {
						load_lib(full_libname);
					}
					catch(Error& ex) {
						throw Error("Loading of library '" + full_libname
									+ "' failed - " + ex.what());
					}
				}
				
				// verify type is now loaded
				if (!type_registry().is_registered(type_name)) {
					Oss oss;
					oss << "Type still not registered after loading libs:" << endl;
					for (iLib=libs.begin(); iLib!=libs.end(); ++iLib) {
						oss << "* " << (*iLib) << endl;
					}
					throw Error(oss.str());
				}
				
				// type successfully loaded - return
				return;
			}
		}

		throw Error("No library mapping found");
	}
	catch(Error& ex) {
		throw Error("dynamic loading of '" + type_name 
			+ "' failed:\n" + ex.what());
	}
}

vector<string> DynamicLoaderBase::get_path() const
{
	// get path from environment variable 
	const char* path_cstr = getenv("XPARAM_CLASSPATH");
	if (path_cstr == NULL)
		throw Error("XPARAM_CLASSPATH not set");
	string path = path_cstr;
		
	// split path into separate directories
	vector<string> dirs;
	char sep = FileUtils::path_separator();

	string::size_type pos = 0;
	string::size_type new_pos = path.find(sep,pos);
	while (new_pos != string::npos) {
		string::size_type dir_size = new_pos - pos;
		dirs.push_back(path.substr(pos,dir_size));
		pos = new_pos+1; // skip separator
		new_pos = path.find(sep,pos);
	}
	dirs.push_back(path.substr(pos));
	
	return dirs;
}

string DynamicLoaderBase::full_path(const string& dir, 
									const string& file) const
{
	// An empty 'dir' should cause an error before this point, but
	// just in case (so we don't crash when accessing last char) ...
	if ( dir.empty() )
		return ""; 

	if (dir[dir.size()-1] != FileUtils::path_slash_char())
		return dir + FileUtils::path_slash_char() + file;
	else
		return dir + file;
}


} // end namespace xParam_internal

#if defined(OS_UNIX)
//////////////////////////////////////////////////////////////
// Unix Implementation
//////////////////////////////////////////////////////////////
#include <dlfcn.h>
#include<dirent.h>

namespace xParam_internal {

class UnixDynamicLoader : public DynamicLoaderBase {
		
protected:
	virtual vector<string> 
		get_mapfiles_in(const string& dir) const;
	
	virtual void load_lib(const string& full_libname) const;
};

void dynamic_load(const string& type_name)
{
	UnixDynamicLoader loader;
	loader.load(type_name);
}

int file_selector(const struct dirent* my_dirent)
{
	string filename = my_dirent->d_name;
	string wanted_ending = '.' + DynamicLoaderBase::mapfile_extension();

	if (filename.size() < wanted_ending.size())
		return false;

	string::size_type start = filename.size() - wanted_ending.size();
	return filename.substr(start) == wanted_ending;
}

vector<string> UnixDynamicLoader::get_mapfiles_in(const string& dir) const
{
  struct dirent** namelist;
  int num_selected = scandir(dir.c_str(),&namelist,&file_selector,&alphasort);

  if (num_selected==-1)
	  throw Error("Error scanning directory '" + dir + "'");

  vector<string> filenames;
  for(int i=0; i<num_selected; ++i)
	  filenames.push_back(namelist[i]->d_name);

  for (int i=0; i<num_selected; ++i)
	  free(namelist[i]);
  free(namelist);

  return filenames;
}

	
void UnixDynamicLoader::load_lib(const string& full_libname) const
{
	void* table_handle = dlopen(full_libname.c_str(), RTLD_NOW);
	if (table_handle==NULL) 
		throw Error(dlerror());
}

} // end namespace xParam_internal

#elif defined(OS_WINDOWS)
//////////////////////////////////////////////////////////////
// Windows Implementation
//////////////////////////////////////////////////////////////
#error Dynamic loading not yet supported on Windows

#include <io.h>
#include <direct.h>
#include <windows.h>

namespace xParam_internal {

class WindowsDynamicLoader : public DynamicLoaderBase {
		
protected:
	virtual vector<string> 
		get_mapfiles_in(const string& dir) const;
	
	virtual void load_lib(const string& full_libname) const;
};

void dynamic_load(const string& type_name)
{
	WindowsDynamicLoader loader;
	loader.load(type_name);
}

class FileGlob {
public:
	FileGlob(const string& directory, const string& mask) 
	{
		struct _finddata_t file_data;
		hFile = -1;
		
		if (_chdir(directory.c_str()))
			throw Error("unable to change directory to " + directory);
		
		hFile = _findfirst(mask.c_str(),&file_data);
		if(hFile == -1)
			last_file = "";	
		else
			last_file = file_data.name;
	}
	
	~FileGlob() {
		if (hFile != -1L)
			_findclose(hFile);
	}
	
	// returns next filename, or "" when finished
	string next() { 
		string filename = last_file;
		struct _finddata_t file_data;
		if (!filename.empty()) { // if we aren't already finished
			if ( _findnext( hFile, &file_data ) == 0 )
				last_file = file_data.name;
			else
				last_file = "";
		}
		return filename;
	}

private:
	long hFile;
	string last_file;
};


vector<string> 
	WindowsDynamicLoader::get_mapfiles_in(const string& dir) const
{
	string libmap_mask = "*." + mapfile_extension();
	FileGlob glob(dir,libmap_mask);

	vector<string> mapfiles;
	string filename;
	for (filename=glob.next(); !filename.empty(); filename=glob.next()) {
		mapfiles.push_back(filename);
	}
	return mapfiles;
}

void WindowsDynamicLoader::load_lib(const string& full_libname) const
{
	if (LoadLibrary(full_libname.c_str()) == NULL)
		throw Error("DLL loading failed");
}


} // end namespace xParam_internal

#else // none of above operating systems
//////////////////////////////////////////////////////////////
// Unsupported OS
//////////////////////////////////////////////////////////////
#error Dynamic loading error - unknown OS
#endif // Which OS

#endif // NO_DYNAMIC_LOADING


