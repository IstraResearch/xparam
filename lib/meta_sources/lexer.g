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
#include "../xparam/xp_parser.h"
#include "xpv_parsed_value_token.h"
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

class xParamLexer extends Lexer;
options {
  charVocabulary = '\u0000' .. '\u00FF';
  importVocab = xParamParser;
  defaultErrorHandler = false;
}

{
  private:
	Handle<ParsedValue> m_read_raw_bytes();

}

protected GLUE_CHAR: '\1' 
	{assert(cmdline_glue_char() == 1);}
;

protected WS: GLUE_CHAR | ' ' | '\t' | '\r' | '\n';
protected SINGLE_LINE_WS: GLUE_CHAR | ' ' | '\t';

MAIN_SWITCH:
	  RESERVED_SYMBOL
	| (WS)+ { $setType(Token::SKIP); }
	| COMMENT { $setType(Token::SKIP); }
	| (RAW_BYTES_HEADER) => r:RAW_BYTES { r->setType(PARSED_VALUE); $setToken(r); }
	| (ID ('<' | '(' | "::")) => TYPENAME {$setType(TYPENAME);}
	| (ID (~('/' | '\\' | '.' | '-' | ':') | {LA(1) == EOF_CHAR}?)) => ID {$setType(ID);}
	| (FLAG) => FLAG { $setType(FLAG); }
	| CHAR {$setType(CHAR);}
	| STRING {$setType(STRING);}
	| TENTATIVE {$setType(TENTATIVE);}
	| URL {$setType(URL);}
	| SHELL_STRINGS { $setType(SHELL_STRINGS); }	
;
exception
	catch[RecognitionException& ex] {
		throw Error("illegal token - " + getText());
	}

////////////////////////////////////////////////////////////
// tentative types are kept as strings, but have the 
// best suited type encoded as their first character - 
// 'R' means REAL, 'I' means INT, and 'S' means FREE_STRING
// (which could also be a single character).
////////////////////////////////////////////////////////////
protected TENTATIVE:
	  (REAL (~('a'..'z' | 'A'..'Z' | '0'..'9' | '_' | '/' 
			  | '\\' | '.' | '-' | ':') | {LA(1)==EOF_CHAR}?)) => REAL {text = 'R' + text;}
	| (INT (~('a'..'z' | 'A'..'Z' | '0'..'9' | '_' | '/' 
			  | '\\' | '.' | '-' | ':') | {LA(1)==EOF_CHAR}?)) => INT {text = 'I' + text;}
	| FREE_STRING {text = 'S' + text;}
;

protected RESERVED_SYMBOL:
	'(' | ')' | '[' | ']' | '{' | '}' | ('=' ('>')?) | ',' | ';'
;

protected COMMENT:
	'#' (~'\n')* ('\n')?
;

protected URL:
	'@'! (WS!)* URL_NAME
;
exception
	catch[RecognitionException& ex] {
		throw Error("Bad URL name");
	}

protected URL_NAME:
	('a'..'z' | 'A'..'Z' | '0'..'9' | '_' | '-' | '/' | '\\' | ':' | '.')+
;

///////////////////////////////////////////////////////////////////////////
// string returned:
// str[0] is '+' or '-' according to whether the flag is turned on or off
// str[1] etc. is the flag name.
///////////////////////////////////////////////////////////////////////////
protected FLAG
{
  bool negated = false;
}
	:
	  '-'! (("no_") => "no_" {negated=true;} | )! {text = negated ? "-" : "+";} ID
;
exception
	catch[RecognitionException& ex] {
			throw Error("Bad flag setting");
	}

protected ID:
	('a'..'z' | 'A'..'Z' | '_') ('a'..'z' | 'A'..'Z' | '_' | '0'..'9')*
;

// '-' isn't allowed as the first character of a FREE_STRING to avoid confusion with FLAG
// ':' isn't allowed as first character, to allow future syntax extension
protected FIRST_FREE_CHAR: 'a'..'z' | 'A'..'Z' | '_' | '0'..'9' | '/' | '\\' | '.';
protected FREE_STRING:
	FIRST_FREE_CHAR (FIRST_FREE_CHAR | '-' | ':')*
;

/////////////////////////////////////////////////////////////////
// INT rules
/////////////////////////////////////////////////////////////////
protected DIGIT: 			'0'..'9';
protected HEX_DIGIT:		'0'..'9' | 'a'..'f' | 'A'..'F';
protected OCT_DIGIT:		'0'..'7';
protected BIN_DIGIT: 		'0'..'1';
protected SIGN:  			'+' | '-';
protected HEX_MARKER:		'0' ('x'|'X');
protected BIN_MARKER:		'0' ('b'|'B');

protected UNSIGNED_DEC_INT: '1'..'9' (DIGIT)*;
protected UNSIGNED_OCT_INT: '0' (OCT_DIGIT)*;
protected UNSIGNED_HEX_INT: HEX_MARKER (HEX_DIGIT)+;
protected UNSIGNED_BIN_INT: BIN_MARKER (BIN_DIGIT)+;

protected UNSIGNED_QUALIFIER: 'U' | 'u';
protected LONG_QUALIFIER: 'L' | 'l';

protected INT
{
  char long_qualifier = 'X';
  char unsigned_qualifier = 'X';
  char base;
}
	:
	(SIGN)? (  (HEX_MARKER) => UNSIGNED_HEX_INT {base='H';}
	         | (BIN_MARKER) => UNSIGNED_BIN_INT {base='B';}
		   | UNSIGNED_OCT_INT {base='O';}
	         | UNSIGNED_DEC_INT {base='D';} )
	(UNSIGNED_QUALIFIER {unsigned_qualifier = 'U';} )? 
	(LONG_QUALIFIER {long_qualifier = 'L';} )?
	{
	  text = string(1,base) + unsigned_qualifier + long_qualifier + text;
	}
;

/////////////////////////////////////////////////////////////////
// REAL rules
/////////////////////////////////////////////////////////////////

protected FLOATING_POINT_MANTISA:
	  (DIGIT)+ '.' (DIGIT)*
	| '.' (DIGIT)+
;

protected EXPONENT:
	('e'|'E') (SIGN)? (DIGIT)+
;

protected REAL:
	(SIGN)? ( (FLOATING_POINT_MANTISA) => FLOATING_POINT_MANTISA (EXPONENT)?
		    | (DIGIT)+ EXPONENT ) ('f'|'F'|'l'|'L')?
;

/////////////////////////////////////////////////////////////////
// CHAR and STRING rules
//
// in both CHAR and STRING we keep the first APOSTROPHE or QUOTES
// in the token text, so that characters like ')' aren't converted 
// by ANTLR to special tokens (here RESERVED_SYMBOL) because they
// are found in the lexer's literal table.
/////////////////////////////////////////////////////////////////

protected APOSTROPHE: '\'';
protected QUOTES: '"';
protected BACKSLASH: '\\';

protected CHAR:
	APOSTROPHE (CHAR_BODY | QUOTES) APOSTROPHE!
;
exception
	catch[RecognitionException& ex] {
		throw Error("Bad char literal");
	}

protected STRING:
	QUOTES (CHAR_BODY | APOSTROPHE)* QUOTES!
;
exception
	catch[RecognitionException& ex] {
		throw Error("Bad string literal");
	}

protected CHAR_BODY:
	  ~('\\' | '"' | '\'')
	| (HEX_ESC_CHAR_BODY) => HEX_ESC_CHAR_BODY
	| BACKSLASH .
;

protected HEX_ESC_CHAR_BODY:
	BACKSLASH ('x'|'X') HEX_DIGIT HEX_DIGIT
;


////////////////////////////////////////////////////////////////
// TYPENAME rules
//
// we support namespaces, and template arguments with "const"
// and "*" modifiers. 
// EXAMPLE: Foo::Bar<const X*, Y<Z>>
// NOTE: only class template parameters are currently supported.
////////////////////////////////////////////////////////////////


// protected SCOPED_NAME: ID ("::" ID)*;

// Greedy WS
protected GWS: (options {greedy=true;}:WS!)*;

protected TYPENAME: 
	ID GWS
	("::" GWS ID GWS)*
	(TEMPLATE_ARGS)?
;
exception
	catch[RecognitionException& ex] {
		throw Error("Bad Typename");
	}

protected TEMPLATE_ARGS:
	  '<' GWS ONE_TEMPLATE_ARG GWS (',' GWS ONE_TEMPLATE_ARG GWS)* '>'
;

protected ONE_TEMPLATE_ARG:
	   POSSIBLE_CONST TYPENAME GWS ('*')?;


// leave exactly a single space after "const", so typenames have canonical form
protected POSSIBLE_CONST:
	("const" WS) => "const" (WS!)+ {text+=' ';} 
	|
;

//====================================================
// SHELL_STRINGS
// DESCRIPTION: A list of strings separated by the shell
//              (in the lexer separations are marked
//               by GLUE_CHARs).
//              The rule starts with a ':' and ends in
//              either EOF, or another ':' which appears
//              just after a GLUE_CHAR.
//              Neither colon is appended to the text
//              for this rule.
//====================================================
protected SHELL_STRINGS
{
  bool last_was_glue = false;
}
	:
	  ':'! GLUE_CHAR ( options {greedy=true;}: 
		   GLUE_CHAR {last_was_glue = true;}
		   | {!last_was_glue}? ':'
		   | ~('\1' | ':') {last_was_glue = false;}
		 )*
	  (':'! | {LA(1) == EOF_CHAR}? )
;


//====================================================
// RAW_BYTES
// DESCRIPTION: Transfer control of the input stream to the 
//              RawBytes constructor to read the object, and
//              Return it as a PARSED_VALUE of type RawBytes.
//====================================================

protected RAW_BYTES_HEADER: "raw<<<";


protected RAW_BYTES
	: RAW_BYTES_HEADER {
		Handle<ParsedValue> parsed_val = m_read_raw_bytes();
		ParsedValueToken *t = new ParsedValueToken(parsed_val);
		$setToken(RefToken(t));
	  }
;
