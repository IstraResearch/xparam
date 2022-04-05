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

#ifndef INC_xParamParserTokenTypes_hpp_
#define INC_xParamParserTokenTypes_hpp_

ANTLR_BEGIN_NAMESPACE(xParam_internal)
/* $ANTLR 2.7.1: "parser.g" -> "xParamParserTokenTypes.hpp"$ */
struct xParamParserTokenTypes {
	enum {
		EOF_ = 1,
		// ";" = 4
		URL = 5,
		ID = 6,
		// "=" = 7
		FLAG = 8,
		TYPENAME = 9,
		// "(" = 10
		// ")" = 11
		// "[" = 12
		// "]" = 13
		// "{" = 14
		// "}" = 15
		// "," = 16
		// "=>" = 17
		TENTATIVE = 18,
		CHAR = 19,
		STRING = 20,
		SHELL_STRINGS = 21,
		PARSED_VALUE = 22,
		NULL_TREE_LOOKAHEAD = 3
	};
};
ANTLR_END_NAMESPACE
#endif /*INC_xParamParserTokenTypes_hpp_*/
