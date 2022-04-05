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


#pragma warning (disable: 4101)

/* $ANTLR 2.7.1: "loader_parser.g" -> "DynamicLoaderParser.cpp"$ */


#pragma warning (disable: 4786)


#include <../src_include/DynamicLoaderParser.hpp>
#include "antlr/NoViableAltException.hpp"
#include "antlr/SemanticException.hpp"


#include "../xparam/xp_error.h"

using namespace xparam_antlr;
using namespace std;


ANTLR_BEGIN_NAMESPACE(xParam_internal)



DynamicLoaderParser::DynamicLoaderParser(xparam_antlr::TokenBuffer& tokenBuf, int k)
: xparam_antlr::LLkParser(tokenBuf,k)
{
	setTokenNames(_tokenNames);
}

DynamicLoaderParser::DynamicLoaderParser(xparam_antlr::TokenBuffer& tokenBuf)
: xparam_antlr::LLkParser(tokenBuf,1)
{
	setTokenNames(_tokenNames);
}

DynamicLoaderParser::DynamicLoaderParser(xparam_antlr::TokenStream& lexer, int k)
: xparam_antlr::LLkParser(lexer,k)
{
	setTokenNames(_tokenNames);
}

DynamicLoaderParser::DynamicLoaderParser(xparam_antlr::TokenStream& lexer)
: xparam_antlr::LLkParser(lexer,1)
{
	setTokenNames(_tokenNames);
}

DynamicLoaderParser::DynamicLoaderParser(const xparam_antlr::ParserSharedInputState& state)
: xparam_antlr::LLkParser(state,1)
{
	setTokenNames(_tokenNames);
}

std::vector<std::string>  DynamicLoaderParser::matches_for(
	 const std::string& wanted_type 
) {

	std::vector<std::string> matching_libs;

	
	try {      // for error handling

		m_matching_libs.clear();

		{
		for (;;) {
			if ((LA(1)==5||LA(1)==ID||LA(1)==TYPENAME)) {
				mapping(wanted_type);
			}
			else {
				goto _loop3;
			}
			
		}
		_loop3:;
		}
		match(xparam_antlr::Token::EOF_TYPE);

		matching_libs = m_matching_libs;

	}
	catch (NoViableAltException& ex) {

		
				string msg;
				if (LT(1)->getType() == Token::EOF_TYPE)
					msg = "unexpected EOF";
				else
					msg = "unexpected token type";
				throw Error(msg);
			

	}
	catch (ANTLRException& ex) {

		
				throw Error(ex.what());
			

	}
	return matching_libs;
}

void DynamicLoaderParser::mapping(
	 const std::string& wanted_type 
) {

	
	std::vector<string> types;
	std::vector<std::string> libs;
	

	
	try {      // for error handling
		types=type_list();
		match(4);
		libs=lib_list();

		
			    if(std::find(types.begin(),types.end(),wanted_type) != types.end()) {
				if (m_matching_libs.empty())
			        m_matching_libs = libs;
			      else
		throw Error("found more than one mapping for type '" + wanted_type + "'");
			    }
			

	}
	catch (Error& ex) {

		
				throw Error("while parsing types=>libs mapping:\n" + string(ex.what()));
			

	}
	catch (RecognitionException& ex) {

		
				throw Error("syntax error while parsing types=>libs mapping. Next token: " 
						+ LT(1)->getText());
			

	}
}

 std::vector<std::string>  DynamicLoaderParser::type_list() {

	 std::vector<std::string> types ;


	
	std::string name;
	

	
	try {      // for error handling
		switch ( LA(1)) {
		case ID:
		case TYPENAME:
		{
			name=type_name();

			types.push_back(name);

			break;
		}
		case 5:
		{
			match(5);
			name=type_name();

			types.push_back(name);

			{
			for (;;) {
				if ((LA(1)==6)) {
					match(6);
					name=type_name();

					types.push_back(name);

				}
				else {
					goto _loop7;
				}
				
			}
			_loop7:;
			}
			match(7);
			break;
		}
		default:
		{
			throw xparam_antlr::NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (Error& ex) {

		
				throw Error("while parsing type_list:\n" + string(ex.what()));
			

	}
	catch (RecognitionException& ex) {

		
				throw Error("syntax error while parsing type_list. Next token: " 
						+ LT(1)->getText());
			

	}
	return types ;
}

 std::vector<std::string>  DynamicLoaderParser::lib_list() {

	 std::vector<std::string> libs ;


	
	std::string name;
	

	
	try {      // for error handling
		switch ( LA(1)) {
		case FILENAME:
		case ID:
		{
			name=lib_name();

			libs.push_back(name);

			break;
		}
		case 5:
		{
			match(5);
			name=lib_name();

			libs.push_back(name);

			{
			for (;;) {
				if ((LA(1)==6)) {
					match(6);
					name=lib_name();

					libs.push_back(name);

				}
				else {
					goto _loop10;
				}
				
			}
			_loop10:;
			}
			match(7);
			break;
		}
		default:
		{
			throw xparam_antlr::NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (Error& ex) {

		
				throw Error("while parsing lib_list:\n" + string(ex.what()));
			

	}
	catch (RecognitionException& ex) {

		
				throw Error("syntax error while parsing lib_list. Next token: " 
						+ LT(1)->getText());
			

	}
	return libs ;
}

 std::string  DynamicLoaderParser::type_name() {

	 std::string name ;

	xparam_antlr::RefToken  tn = xparam_antlr::nullToken;
	xparam_antlr::RefToken  id = xparam_antlr::nullToken;
	
	try {      // for error handling
		switch ( LA(1)) {
		case TYPENAME:
		{
			tn = LT(1);
			match(TYPENAME);

			name=tn->getText();

			break;
		}
		case ID:
		{
			id = LT(1);
			match(ID);

			name=id->getText();

			break;
		}
		default:
		{
			throw xparam_antlr::NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (Error& ex) {

		
				throw Error("while parsing type name:\n" + string(ex.what()));
			

	}
	catch (RecognitionException& ex) {

		
				throw Error("syntax error while parsing type name. Next token: " 
						+ LT(1)->getText());
			

	}
	return name ;
}

 std::string  DynamicLoaderParser::lib_name() {

	 std::string name ;

	xparam_antlr::RefToken  f = xparam_antlr::nullToken;
	xparam_antlr::RefToken  id = xparam_antlr::nullToken;
	
	try {      // for error handling
		switch ( LA(1)) {
		case FILENAME:
		{
			f = LT(1);
			match(FILENAME);

			name=f->getText();

			break;
		}
		case ID:
		{
			id = LT(1);
			match(ID);

			name=id->getText();

			break;
		}
		default:
		{
			throw xparam_antlr::NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (Error& ex) {

		
				throw Error("while parsing library name:\n" + string(ex.what()));
			

	}
	catch (RecognitionException& ex) {

		
				throw Error("syntax error while parsing library name. Next token: " 
						+ LT(1)->getText());
			

	}
	return name ;
}

const char* DynamicLoaderParser::_tokenNames[] = {
	"<0>",
	"EOF",
	"<2>",
	"NULL_TREE_LOOKAHEAD",
	"\"=>\"",
	"\"[\"",
	"\",\"",
	"\"]\"",
	"FILENAME",
	"ID",
	"TYPENAME",
	0
};



ANTLR_END_NAMESPACE
