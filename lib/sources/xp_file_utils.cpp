
/*	Copyright (C) 2001,2002,2003 Free Software Foundation, Inc.
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

#include "../src_include/xp_file_utils.h"

using namespace std;

namespace xParam_internal {

namespace FileUtils {

//////////////////////////////////////////////////////////////
// OS Independent code
//////////////////////////////////////////////////////////////
string dir_part(const string& path)
{
	string::size_type pos = path.rfind(path_slash_char());
	if (pos == string::npos)
		return "";
	else
		return path.substr(0,pos+1);
}

//////////////////////////////////////////////////////////////
// Unix Implementation
//////////////////////////////////////////////////////////////
#if defined(OS_UNIX)

string canonical_form(const string& path)
{
	return path;
}

char path_separator() 
{ 
	return ':'; 
}

char path_slash_char() 
{ 
	return '/'; 
}

bool is_relative(const string& libname)
{
	if (libname.empty())
		return true;
	return libname[0] != '/';
}


#elif defined(OS_WINDOWS)
//////////////////////////////////////////////////////////////
// Windows Implementation
//////////////////////////////////////////////////////////////

// Under windows, sometimes / (slash) is supported in a path
// as well as \ (backslash), but trying to support both in
// this code can cause some problems, so it's easier to just
// convert everything to backslashes.
string canonical_form(const string& path)
{
	string canonical = path;

	string::iterator i;
	for (i=canonical.begin(); i!=canonical.end(); ++i)
		if ((*i) == '/')
			(*i) = '\\';
	return canonical;
}

char path_separator()
{ 
	return ';';
}

char path_slash_char()
{ 
	return '\\'; 
}

bool is_relative(const string& libname)
{
	return libname.find(':') == string::npos;
}

#else // none of above operating systems
//////////////////////////////////////////////////////////////
// Unsupported OS
//////////////////////////////////////////////////////////////
#error FileUtils error - unknown OS
#endif // Which OS

} // end namespace FileUtils

} // end namespace xParam_internal



