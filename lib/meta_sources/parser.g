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

header "post_include_hpp" {

#include "../xparam/xp_value_management.h"
#include "../xparam/xp_parser.h"
#include "xpv_parsed_value_token.h"

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

class xParamParser extends Parser;
options {
  defaultErrorHandler = false;
}
{
  public:
    void set_context(const std::vector<std::string>& redirection_context);

  private:
    static std::string m_int_to_string(int i); 

    static char m_decode_char(const std::string& str);
    static std::string m_decode_string(const std::string& str);

    static ParsedValueList m_cut_shell_strings(const std::string& str);

    std::string m_convert_path(const std::string& path) const;
    Handle<std::istream> m_open_url(const std::string& url_name) const;
    std::vector<std::string> m_new_context(const std::string& url_name) const;

    Handle<ParsedValue> m_url_read_value(const std::string& url_name) const;
    void m_url_read_value_set(const std::string& url_name, AssignmentListener& listener) const;
    
    std::vector<std::string> m_redirection_context;
}

////////////////////////////////////////////////////////////////
// public parser symbols
////////////////////////////////////////////////////////////////

value_set
[ AssignmentListener& listener ]
	:
	( value_set_member[listener] )* (";" | EOF)
;
exception
	catch [ANTLRException& ex] {
		throw Error(ex.what());
	}

value
returns [Handle<ParsedValue> val]
	:
	  val = basic_type
	| val = id_tentative_string
	| val = compound_value
	| val = list_value
	| val = map_value
	| url:URL {val=m_url_read_value(url->getText());}
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
// value_set implementation
////////////////////////////////////////////////////////////////

protected value_set_member
[ AssignmentListener& listener ]
	:
	  (ID "=") => member_assignment[listener]
	| (URL) => url:URL {m_url_read_value_set(url->getText(),listener);}
	| flag_setting[listener]
;

protected member_assignment
[AssignmentListener& listener]
{
  Handle<ParsedValue> val;
}
	:
	id:ID "=" val=global_scope_value {listener.notify(id->getText(),val);}
;
exception
	catch [Error& ex] {
		throw Error("while parsing assignment to parameter '" 
				+ id->getText() + "':\n" + ex.what());
	}
	catch [RecognitionException& ex] {
		throw Error("syntax error parsing assignment to parameter '"
				+ id->getText() + "'");
	}

protected global_scope_value
returns [Handle<ParsedValue> val]
{
  ParsedValueList values;
}
	:
	  values = non_empty_list_of_values {
		if (values.size() == 1) { // it's a single value
			val = values[0];
		}
		else { // it's a list of values
			val = Handle<ParsedValue>(new ParsedListValue(values));
		}
	  }
;

protected flag_setting
[AssignmentListener& listener]
	:
	  flag:FLAG {
		string str = flag->getText();
		bool flag_value = (str[0] == '+');
		string flag_name = str.substr(1,str.size()-1);
		Handle<ParsedValue> parsed_val(new ParsedBoolValue(flag_value));
		listener.notify(flag_name,parsed_val);
	  }
;

////////////////////////////////////////////////////////////////
// value implementation
////////////////////////////////////////////////////////////////

protected compound_value
returns [Handle<ParsedValue> val]
{
  ParsedValueList args;
}
	:
	  tn:TYPENAME "(" args=list_of_values ")" 
		{val = Handle<ParsedValue>(new ParsedCompoundValue(tn->getText(),args));}
;
exception
	catch [Error& ex] {
		throw Error("while parsing constructor for '" + tn->getText() + "':\n" + ex.what());
	}
	catch [RecognitionException& ex] {
		throw Error("syntax error while parsing constructor for '" + tn->getText() + "'");
	}

protected list_value
returns [Handle<ParsedValue> val]
{
  ParsedValueList values;
}
	:
	"[" values=list_of_values "]" { val = Handle<ParsedValue>(new ParsedListValue(values)); }
;
exception
	catch [Error& ex] {
		throw Error("while reading list:\n" + string(ex.what()));
	}
	catch [RecognitionException& ex] {
		throw Error("syntax error while reading list");
	}

protected map_value
returns [Handle<ParsedValue> val]
{
  ParsedPairList map_items;
}
	:
	"{" map_items=list_of_map_items "}" { val = Handle<ParsedValue>(new ParsedMapValue(map_items)); }
;
exception
	catch [Error& ex] {
		throw Error("while reading map:\n" + string(ex.what()));
	}
	catch [RecognitionException& ex] {
		throw Error("syntax error while reading map");
	}


////////////////////////////////////////////////////////////////
// list_of_values implementation
////////////////////////////////////////////////////////////////

protected list_of_values
returns [ParsedValueList list]
	:
	  // empty list
	| list=non_empty_list_of_values
;

protected non_empty_list_of_values
returns [ParsedValueList list]
{
  Handle<ParsedValue> val;
}
	:
	  val=value {list.push_back(val);}
	  ("," val=value {list.push_back(val);})*
;
exception
	catch [Error& ex] {
		if (!list.empty())
			throw Error("while parsing element " 
					+ m_int_to_string(list.size())
					+ " of value list:\n" + ex.what());
		else
			throw;
	}
	catch [RecognitionException& ex] {
		throw Error("syntax error while parsing element "
				+ m_int_to_string(list.size())
				+ " of value list:\n" + ex.what());
	}

////////////////////////////////////////////////////////////////
// list_of_map_items implementation
////////////////////////////////////////////////////////////////

protected list_of_map_items
returns [ParsedPairList map_items]
	:
	  // empty list
	| map_items=non_empty_list_of_map_items
;

protected non_empty_list_of_map_items
returns [ParsedPairList map_items]
{
  ParsedPair item;
}
	:
	  item=map_item {map_items.push_back(item);}
	  ("," item=map_item {map_items.push_back(item);})*
;
exception
	catch [Error& ex] {
		if (!map_items.empty())
			throw Error("while parsing pair " 
					+ m_int_to_string(map_items.size())
					+ " of map:\n" + ex.what());
		else
			throw;
	}
	catch [RecognitionException& ex] {
		throw Error("syntax error while parsing pair "
				+ m_int_to_string(map_items.size())
				+ " of map:\n" + ex.what());
	}

protected map_item
returns [ParsedPair item]
{
  Handle<ParsedValue> item_key;
  Handle<ParsedValue> item_value;
}
	:
	  item_key=value "=>"  item_value=value { item = make_pair(item_key,item_value);}
;
exception
	catch [Error& ex] {
		throw Error("while parsing key=>value pair:\n" 
				+ string(ex.what()));
	}
	catch [RecognitionException& ex] {
		throw Error("syntax error while parsing key=>value pair:\n" 
				+ string(ex.what()));
	}


////////////////////////////////////////////////////////////////
// basic_type implementation
////////////////////////////////////////////////////////////////

protected basic_type
returns [Handle<ParsedValue> val]
	:
	  t:TENTATIVE { 
		val = Handle<ParsedValue>(new ParsedTentativeValue(t->getText()));
	  }
	| c:CHAR {
		char decoded_char = m_decode_char(c->getText());
		val = Handle<ParsedValue>(new ParsedCharValue(decoded_char));
	  }
	| s:STRING {
		string decoded_string = m_decode_string(s->getText());
		val = Handle<ParsedValue>(new ParsedStringValue(decoded_string));
	  }
	| shell_strings:SHELL_STRINGS {
		ParsedValueList strings = m_cut_shell_strings(shell_strings->getText());
		val = Handle<ParsedValue>(new ParsedListValue(strings));
	  }
	| parsed_val:PARSED_VALUE {
		Token* base_token = parsed_val.get();
		assert(base_token != 0);
		ParsedValueToken *parsed_val_token = dynamic_cast<ParsedValueToken*>(base_token);
		assert(parsed_val_token != 0);
		val = parsed_val_token->getValue();
	  }
;

protected id_tentative_string
returns [Handle<ParsedValue> val]
	:
	  id:ID {
		std::string encoded_value = 'S' + id->getText();
		val = Handle<ParsedValue>(new ParsedTentativeValue(encoded_value));
	  }
;