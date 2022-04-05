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

header "pre_include_cpp" {
#pragma warning (disable: 4786)
}

header "post_include_cpp" {
#include "../xparam/xp_error.h"

using namespace xparam_antlr;
using namespace std;
}

options {
  language="Cpp";
  namespace = "xParam_internal";
  namespaceStd="std";
  namespaceAntlr="xparam_antlr";     
}

class TypeNameLexer extends Lexer;
options {
  charVocabulary = '\u0000' .. '\u00FF';
  defaultErrorHandler = false;

  // following option makes sure antlr doesn't generate
  // static bitset objects, which would make it impossible
  // to run the parser before main() (since they might not
  // yet be initialized).
  codeGenBitsetTestThreshold=999; 
}

////////////////////////////////////////////////////////////////
// TYPENAME rules
//
// we support namespaces, and template arguments with "const"
// and "*" modifiers. 
// EXAMPLE: Foo::Bar<const X*, Y<Z>>
// NOTE: only class template parameters are currently supported.
////////////////////////////////////////////////////////////////

TYPENAME:
	GWS ID GWS
	("::" GWS ID GWS)* 
	(TEMPLATE_ARGS)?
;
exception
	catch[RecognitionException& ex] {
		throw Error("Bad Typename");
	}

protected WS: ' ' | '\t' | '\r' | '\n';

// Greedy WS
protected GWS: (options {greedy=true;}:WS!)*;

protected ID:
	('a'..'z' | 'A'..'Z' | '_') ('a'..'z' | 'A'..'Z' | '_' | '0'..'9')*
;

protected TEMPLATE_ARGS:
	  '<' GWS ONE_TEMPLATE_ARG GWS (',' GWS ONE_TEMPLATE_ARG GWS)* '>'
;

protected ONE_TEMPLATE_ARG:
	   POSSIBLE_CONST TYPENAME GWS ('*')?;


// leave exactly a single space after "const", so typenames have canonical form
protected POSSIBLE_CONST:
	("const" WS) => "const" (options {greedy=true;}:WS!)+ {text+=' ';} 
	|
;


