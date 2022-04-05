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

#include <algorithm>
#include "../xparam/xp_param_imp.h"

using namespace std;

namespace xParam_internal {

	class not_in_ws {
	public:
		bool operator()(const char ch) {
			string ws=" \n\t\v\r\f";
			return find(ws.begin(),ws.end(),ch) == ws.end();
		}
	};
	
	string ParamPartialImp::trim(const string& s) {
		string::const_iterator start = find_if(s.begin(),s.end(),not_in_ws());
		if (start == s.end())
			return "";
		
		string::const_reverse_iterator rstart = find_if(s.rbegin(),s.rend(),not_in_ws());
		string::const_iterator end = s.end() - (rstart - s.rbegin());
		
		return string(start,end);
	}
	
	void ParamPartialImp::separate_name_and_description(const string& s)
	{
		// find separator (if it exists)
		string::const_iterator separator = find(s.begin(),s.end(),'!');

		// extract description
		string description;
		if (separator != s.end()) {
			description.assign(separator+1,s.end());
			description = trim(description);
		}
		m_description = description;

		// extract name
		string name = trim(string(s.begin(),separator));
		m_name = name;

		// verify name is a legal identifier
		if (name.empty()) {
			throw Error("empty parameter name in '" + s + "'");
		}

		const string first_char = 
				"_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		const string id_chars = first_char + "0123456789";

		const string msg = "'" + name + "' isn't a legal parameter name";
		if (find(first_char.begin(),first_char.end(),name[0]) == first_char.end()) {
			throw Error(msg + ": '" + name[0] 
							+ "' is not allowed as first character");
		}

		string::const_iterator i;
		for (i=name.begin()+1; i!=name.end(); ++i) {
			const char c = *i;
			if (find(id_chars.begin(),id_chars.end(),c) == id_chars.end()) {
				throw Error(msg + ": character '" + c + "' is not allowed");
			}
		}
	}

}
