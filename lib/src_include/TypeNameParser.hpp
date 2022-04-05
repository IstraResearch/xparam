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

#ifndef INC_TypeNameParser_hpp_
#define INC_TypeNameParser_hpp_



#include <vector>
#include <string>
#include <algorithm>


#include "antlr/config.hpp"
/* $ANTLR 2.7.1: "type_name_parser.g" -> "TypeNameParser.hpp"$ */
#include "antlr/TokenStream.hpp"
#include "antlr/TokenBuffer.hpp"
#include <../src_include/TypeNameParserTokenTypes.hpp>
#include "antlr/LLkParser.hpp"

ANTLR_BEGIN_NAMESPACE(xParam_internal)
class TypeNameParser : public xparam_antlr::LLkParser, public TypeNameParserTokenTypes
 {


protected:
	TypeNameParser(xparam_antlr::TokenBuffer& tokenBuf, int k);
public:
	TypeNameParser(xparam_antlr::TokenBuffer& tokenBuf);
protected:
	TypeNameParser(xparam_antlr::TokenStream& lexer, int k);
public:
	TypeNameParser(xparam_antlr::TokenStream& lexer);
	TypeNameParser(const xparam_antlr::ParserSharedInputState& state);
	public:  std::string  type_name();
private:
	static const char* _tokenNames[];
	
};

ANTLR_END_NAMESPACE
#endif /*INC_TypeNameParser_hpp_*/
