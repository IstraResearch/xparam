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

/* $ANTLR 2.7.1: "type_name_parser.g" -> "TypeNameParser.cpp"$ */


#pragma warning (disable: 4786)


#include <../src_include/TypeNameParser.hpp>
#include "antlr/NoViableAltException.hpp"
#include "antlr/SemanticException.hpp"


#include "../xparam/xp_error.h"

using namespace xparam_antlr;
using namespace std;


ANTLR_BEGIN_NAMESPACE(xParam_internal)



TypeNameParser::TypeNameParser(xparam_antlr::TokenBuffer& tokenBuf, int k)
: xparam_antlr::LLkParser(tokenBuf,k)
{
	setTokenNames(_tokenNames);
}

TypeNameParser::TypeNameParser(xparam_antlr::TokenBuffer& tokenBuf)
: xparam_antlr::LLkParser(tokenBuf,1)
{
	setTokenNames(_tokenNames);
}

TypeNameParser::TypeNameParser(xparam_antlr::TokenStream& lexer, int k)
: xparam_antlr::LLkParser(lexer,k)
{
	setTokenNames(_tokenNames);
}

TypeNameParser::TypeNameParser(xparam_antlr::TokenStream& lexer)
: xparam_antlr::LLkParser(lexer,1)
{
	setTokenNames(_tokenNames);
}

TypeNameParser::TypeNameParser(const xparam_antlr::ParserSharedInputState& state)
: xparam_antlr::LLkParser(state,1)
{
	setTokenNames(_tokenNames);
}

 std::string  TypeNameParser::type_name() {

	 std::string name ;

	xparam_antlr::RefToken  tn = xparam_antlr::nullToken;
	
	try {      // for error handling
		tn = LT(1);
		match(TYPENAME);

		name=tn->getText();

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
	return name ;
}

const char* TypeNameParser::_tokenNames[] = {
	"<0>",
	"EOF",
	"<2>",
	"NULL_TREE_LOOKAHEAD",
	"TYPENAME",
	0
};



ANTLR_END_NAMESPACE
