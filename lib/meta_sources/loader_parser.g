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

header "pre_include_hpp" {
#include <vector>
#include <string>
#include <algorithm>
}

header "pre_include_cpp" {
#pragma warning (disable: 4786)
}

header "post_include_cpp" {
#include "../xparam/xp_error.h"

using namespace xparam_antlr;
using namespace std;
}

options {
  language = "Cpp";
  namespace = "xParam_internal";
  namespaceStd="std";
  namespaceAntlr="xparam_antlr";     
}

class DynamicLoaderParser extends Parser;
options {
  defaultErrorHandler = false;
}
{
  private:
    std::vector<std::string> m_matching_libs;
}

////////////////////////////////////////////////////////////////
// public parser symbols
////////////////////////////////////////////////////////////////

matches_for
[ const std::string& wanted_type ]
returns [std::vector<std::string> matching_libs]
	:
	{m_matching_libs.clear();} // Needed when parser is invoked more than once.
	(mapping[wanted_type])* EOF
	{matching_libs = m_matching_libs;}
;
exception
	catch [NoViableAltException& ex] {
		string msg;
		if (LT(1)->getType() == Token::EOF_TYPE)
			msg = "unexpected EOF";
		else
			msg = "unexpected token type";
		throw Error(msg);
	}
	catch [ANTLRException& ex] {
		throw Error(ex.what());
	}


////////////////////////////////////////////////////////////////
// mapfile sub-rules
////////////////////////////////////////////////////////////////

protected mapping
[ const std::string& wanted_type ]
{
  std::vector<string> types;
  std::vector<std::string> libs;
}
	:
	  types=type_list "=>" libs=lib_list
	  { 
	    if(std::find(types.begin(),types.end(),wanted_type) != types.end()) {
		if (m_matching_libs.empty())
	        m_matching_libs = libs;
	      else
              throw Error("found more than one mapping for type '" + wanted_type + "'");
	    }
	  }
;
exception
	catch [Error& ex] {
		throw Error("while parsing types=>libs mapping:\n" + string(ex.what()));
	}
	catch [RecognitionException& ex] {
		throw Error("syntax error while parsing types=>libs mapping. Next token: " 
				+ LT(1)->getText());
	}

protected type_list
returns [ std::vector<std::string> types ]
{
  std::string name;
}
	:
	  name=type_name {types.push_back(name);} 
	| "[" name=type_name {types.push_back(name);} 
	                 ("," name=type_name {types.push_back(name);})* "]"
;
exception
	catch [Error& ex] {
		throw Error("while parsing type_list:\n" + string(ex.what()));
	}
	catch [RecognitionException& ex] {
		throw Error("syntax error while parsing type_list. Next token: " 
				+ LT(1)->getText());
	}


protected lib_list
returns [ std::vector<std::string> libs ]
{
  std::string name;
}
	:
	  name=lib_name {libs.push_back(name);} 
	| "[" name=lib_name {libs.push_back(name);} 
	                 ("," name=lib_name {libs.push_back(name);})* "]"
;
exception
	catch [Error& ex] {
		throw Error("while parsing lib_list:\n" + string(ex.what()));
	}
	catch [RecognitionException& ex] {
		throw Error("syntax error while parsing lib_list. Next token: " 
				+ LT(1)->getText());
	}


protected lib_name
returns [ std::string name ]
	:
	  f:FILENAME {name=f->getText();}
	| id:ID {name=id->getText();}
;
exception
	catch [Error& ex] {
		throw Error("while parsing library name:\n" + string(ex.what()));
	}
	catch [RecognitionException& ex] {
		throw Error("syntax error while parsing library name. Next token: " 
				+ LT(1)->getText());
	}


protected type_name
returns [ std::string name ]
	:
	  tn:TYPENAME {name=tn->getText();}
	| id:ID {name=id->getText();}
;
exception
	catch [Error& ex] {
		throw Error("while parsing type name:\n" + string(ex.what()));
	}
	catch [RecognitionException& ex] {
		throw Error("syntax error while parsing type name. Next token: " 
				+ LT(1)->getText());
	}
