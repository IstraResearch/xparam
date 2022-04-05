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

#ifndef INC_xParamParser_hpp_
#define INC_xParamParser_hpp_

#include "antlr/config.hpp"
/* $ANTLR 2.7.1: "parser.g" -> "xParamParser.hpp"$ */
#include "antlr/TokenStream.hpp"
#include "antlr/TokenBuffer.hpp"
#include <../src_include/xParamParserTokenTypes.hpp>
#include "antlr/LLkParser.hpp"




#include "../xparam/xp_value_management.h"
#include "../xparam/xp_parser.h"
#include "xpv_parsed_value_token.h"



ANTLR_BEGIN_NAMESPACE(xParam_internal)
class xParamParser : public xparam_antlr::LLkParser, public xParamParserTokenTypes
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

protected:
	xParamParser(xparam_antlr::TokenBuffer& tokenBuf, int k);
public:
	xParamParser(xparam_antlr::TokenBuffer& tokenBuf);
protected:
	xParamParser(xparam_antlr::TokenStream& lexer, int k);
public:
	xParamParser(xparam_antlr::TokenStream& lexer);
	xParamParser(const xparam_antlr::ParserSharedInputState& state);
	public: void value_set(
		 AssignmentListener& listener 
	);
	protected: void value_set_member(
		 AssignmentListener& listener 
	);
	public: Handle<ParsedValue>  value();
	protected: Handle<ParsedValue>  basic_type();
	protected: Handle<ParsedValue>  id_tentative_string();
	protected: Handle<ParsedValue>  compound_value();
	protected: Handle<ParsedValue>  list_value();
	protected: Handle<ParsedValue>  map_value();
	protected: void member_assignment(
		AssignmentListener& listener
	);
	protected: void flag_setting(
		AssignmentListener& listener
	);
	protected: Handle<ParsedValue>  global_scope_value();
	protected: ParsedValueList  non_empty_list_of_values();
	protected: ParsedValueList  list_of_values();
	protected: ParsedPairList  list_of_map_items();
	protected: ParsedPairList  non_empty_list_of_map_items();
	protected: ParsedPair  map_item();
private:
	static const char* _tokenNames[];
	
};

ANTLR_END_NAMESPACE
#endif /*INC_xParamParser_hpp_*/
