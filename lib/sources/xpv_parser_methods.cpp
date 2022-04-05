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

/*
 * implementation of xParamParser's added private methods (those not defined 
 * by ANTLR).
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include "../src_include/xParamParser.hpp"
#include "../xparam/xp_parser.h"
#include "../xparam/xp_error.h"
#include "../src_include/xp_sstream.h"
#include "../src_include/xp_file_utils.h"

using namespace xparam_antlr;
using namespace std;

namespace {
	unsigned char hex_value(char digit) {
		if (digit>='0' && digit<='9')
			return digit - '0';
		if (digit>='A' && digit<='F')
			return 10 + digit - 'A';

		assert(digit>='a' && digit<='f');
		return 10 + digit - 'f';
	}

	char decode_next_char(const string& str, string::size_type& pos)
	{
		assert(pos < str.size());

		char c = str[pos++];
		if (c != '\\')
			return c;

		c =  str[pos++];
		if (c=='x' || c=='X') {
			char most_digit = str[pos++];
			char least_digit = str[pos++];
			unsigned char uc = (unsigned char)(hex_value(most_digit)<<4 | hex_value(least_digit));
			return char(uc);
		}

		switch (c) {
		  case 'n': return '\n';
		  case 't': return '\t';
		  case 'v': return '\v';
		  case 'b': return '\b';
		  case 'r': return '\r';
		  case 'f': return '\f';
		  case 'a': return '\a';
		  default: return c;
		}
	}

} // annonymous namespace

namespace xParam_internal {

    void xParamParser::set_context(const vector<string>& redirection_context)
	{
		m_redirection_context = redirection_context;
	}

    string xParamParser::m_int_to_string(int i) 
	{
		Oss oss;
		oss << i;
		return oss.str();
	}


	char xParamParser::m_decode_char(const string& str)
	{
		char decoded_char;

		assert(str[0] == '\'');
		string::size_type pos = 1;
		decoded_char = decode_next_char(str,pos);
		assert(pos == str.size()); // make sure we only have one encoded char
		
		return decoded_char;
	}

	string xParamParser::m_decode_string(const string& str)
	{
		string decoded_string; 

		assert(str[0] == '"');
		string::size_type pos = 1;
		while (pos < str.size()) {
			decoded_string += decode_next_char(str,pos);
		}
		assert(pos == str.size());

		return decoded_string;
	}

    ParsedValueList xParamParser::m_cut_shell_strings(const std::string& str)
	{
		ParsedValueList cut_strings;

		string last_string;

		// cut strings according to glue-char
		for (string::const_iterator i=str.begin(); i!=str.end(); ++i) {
			char c = *i;
			if (c == cmdline_glue_char()) {
				if (!last_string.empty()) { // don't add empty strings
					Handle<ParsedValue> val(new ParsedStringValue(last_string));
					cut_strings.push_back(val);
					last_string = "";
				}
			}
			else {
				last_string += c;
			}
		}
		
		// add last string built (if it's not empty)
		if (!last_string.empty()) {
			Handle<ParsedValue> val(new ParsedStringValue(last_string));
			cut_strings.push_back(val);
		}
		
		return cut_strings;
	}


	// convert path relative to current position to path
	// relative to original working directory
	// (absolute path remains unchanged)
	string xParamParser::m_convert_path(const string& path) const
	{
		if (!FileUtils::is_relative(path))
			return path;

		// find last absolute path and use it as base directory
		// or use "" if all paths are relative.
		string base_dir = "";
		vector<string>::const_iterator i;
		for (i=m_redirection_context.end()-1; 
			 i!=m_redirection_context.begin()-1;
			 --i) 
		{
			const string& p = *i;

			if (!FileUtils::is_relative(p)) {
				base_dir = FileUtils::dir_part(p);
				break;
			}
		}

		++i; // i now points to first file after base directory
		for (; i!=m_redirection_context.end(); ++i)
			base_dir += FileUtils::dir_part(*i);

		return base_dir + path;
	}


	Handle<istream> xParamParser::m_open_url(const string& url_name) const
	{
		// special case for reading from standard input
		if (url_name == "stdin")
			return Handle<istream>(&std::cin,false);

		// check context for cyclic redirection
		vector<string>::const_iterator i;
		for (i=m_redirection_context.begin(); i!=m_redirection_context.end(); ++i)
			if ((*i) == url_name)
				throw Error("Cyclic redirection");

		string path = m_convert_path(url_name);

		// open file and return handle to it
		Handle<istream> ifs(new ifstream(path.c_str()));
		if (!(*ifs))
			throw Error("error opening file");
		return ifs;
	}

	vector<string> xParamParser::m_new_context(const string& url_name) const
	{
		vector<string> context = m_redirection_context;
		context.push_back(url_name);
		return context;
	}

	Handle<ParsedValue> xParamParser::m_url_read_value(const string& url_name) const
	{
		std::string canonical_url = FileUtils::canonical_form(url_name);
		try {
			Handle<istream> ish = m_open_url(canonical_url);
			return parse_value(*ish,m_new_context(canonical_url));
		}
		catch(Error& ex) {
			throw Error("during value redirection from file '" 
						+ canonical_url + "':\n" + ex.what());
		}
	}

	void xParamParser::m_url_read_value_set(const string& url_name, AssignmentListener& listener) const
	{
		std::string canonical_url = FileUtils::canonical_form(url_name);
		try {
			Handle<istream> ish = m_open_url(canonical_url);
			parse_value_set(*ish,listener,m_new_context(canonical_url));
		}
		catch(Error& ex) {
			throw Error("during value-set redirection from file '" 
						+ canonical_url + "':\n" + ex.what());
		}
	}


} // namespace xParam_internal
