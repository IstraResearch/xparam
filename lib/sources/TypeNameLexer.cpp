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

/* $ANTLR 2.7.1: "type_name_lexer.g" -> "TypeNameLexer.cpp"$ */


#pragma warning (disable: 4786)


#include <../src_include/TypeNameLexer.hpp>
#include "antlr/CharBuffer.hpp"
#include "antlr/TokenStreamException.hpp"
#include "antlr/TokenStreamIOException.hpp"
#include "antlr/TokenStreamRecognitionException.hpp"
#include "antlr/CharStreamException.hpp"
#include "antlr/CharStreamIOException.hpp"
#include "antlr/NoViableAltForCharException.hpp"



#include "../xparam/xp_error.h"

using namespace xparam_antlr;
using namespace std;


ANTLR_BEGIN_NAMESPACE(xParam_internal)



TypeNameLexer::TypeNameLexer(std::istream& in)
	: xparam_antlr::CharScanner(new xparam_antlr::CharBuffer(in))
{
	setCaseSensitive(true);
	initLiterals();
}

TypeNameLexer::TypeNameLexer(xparam_antlr::InputBuffer& ib)
	: xparam_antlr::CharScanner(ib)
{
	setCaseSensitive(true);
	initLiterals();
}

TypeNameLexer::TypeNameLexer(const xparam_antlr::LexerSharedInputState& state)
	: xparam_antlr::CharScanner(state)
{
	setCaseSensitive(true);
	initLiterals();
}

void TypeNameLexer::initLiterals()
{
}
bool TypeNameLexer::getCaseSensitiveLiterals() const
{
	return true;
}

xparam_antlr::RefToken TypeNameLexer::nextToken()
{
	xparam_antlr::RefToken theRetToken;
	for (;;) {
		xparam_antlr::RefToken theRetToken;
		int _ttype = xparam_antlr::Token::INVALID_TYPE;
		resetText();
		try {   // for char stream error handling
			try {   // for lexical error handling
				if ((LA(1)==static_cast<unsigned char>('\t')||LA(1)==static_cast<unsigned char>('\n')||LA(1)==static_cast<unsigned char>('\r')||LA(1)==static_cast<unsigned char>(' ')||LA(1)==static_cast<unsigned char>('A')||LA(1)==static_cast<unsigned char>('B')||LA(1)==static_cast<unsigned char>('C')||LA(1)==static_cast<unsigned char>('D')||LA(1)==static_cast<unsigned char>('E')||LA(1)==static_cast<unsigned char>('F')||LA(1)==static_cast<unsigned char>('G')||LA(1)==static_cast<unsigned char>('H')||LA(1)==static_cast<unsigned char>('I')||LA(1)==static_cast<unsigned char>('J')||LA(1)==static_cast<unsigned char>('K')||LA(1)==static_cast<unsigned char>('L')||LA(1)==static_cast<unsigned char>('M')||LA(1)==static_cast<unsigned char>('N')||LA(1)==static_cast<unsigned char>('O')||LA(1)==static_cast<unsigned char>('P')||LA(1)==static_cast<unsigned char>('Q')||LA(1)==static_cast<unsigned char>('R')||LA(1)==static_cast<unsigned char>('S')||LA(1)==static_cast<unsigned char>('T')||LA(1)==static_cast<unsigned char>('U')||LA(1)==static_cast<unsigned char>('V')||LA(1)==static_cast<unsigned char>('W')||LA(1)==static_cast<unsigned char>('X')||LA(1)==static_cast<unsigned char>('Y')||LA(1)==static_cast<unsigned char>('Z')||LA(1)==static_cast<unsigned char>('_')||LA(1)==static_cast<unsigned char>('a')||LA(1)==static_cast<unsigned char>('b')||LA(1)==static_cast<unsigned char>('c')||LA(1)==static_cast<unsigned char>('d')||LA(1)==static_cast<unsigned char>('e')||LA(1)==static_cast<unsigned char>('f')||LA(1)==static_cast<unsigned char>('g')||LA(1)==static_cast<unsigned char>('h')||LA(1)==static_cast<unsigned char>('i')||LA(1)==static_cast<unsigned char>('j')||LA(1)==static_cast<unsigned char>('k')||LA(1)==static_cast<unsigned char>('l')||LA(1)==static_cast<unsigned char>('m')||LA(1)==static_cast<unsigned char>('n')||LA(1)==static_cast<unsigned char>('o')||LA(1)==static_cast<unsigned char>('p')||LA(1)==static_cast<unsigned char>('q')||LA(1)==static_cast<unsigned char>('r')||LA(1)==static_cast<unsigned char>('s')||LA(1)==static_cast<unsigned char>('t')||LA(1)==static_cast<unsigned char>('u')||LA(1)==static_cast<unsigned char>('v')||LA(1)==static_cast<unsigned char>('w')||LA(1)==static_cast<unsigned char>('x')||LA(1)==static_cast<unsigned char>('y')||LA(1)==static_cast<unsigned char>('z'))) {
					mTYPENAME(true);
					theRetToken=_returnToken;
				}
				else {
					if (LA(1)==EOF_CHAR) {uponEOF(); _returnToken = makeToken(xparam_antlr::Token::EOF_TYPE);}
				else {throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
				}
				
				if ( !_returnToken ) goto tryAgain; // found SKIP token
				_ttype = _returnToken->getType();
				_ttype = testLiteralsTable(_ttype);
				_returnToken->setType(_ttype);
				return _returnToken;
			}
			catch (xparam_antlr::RecognitionException& e) {
				throw xparam_antlr::TokenStreamRecognitionException(e);
			}
		}
		catch (xparam_antlr::CharStreamIOException& csie) {
		   throw xparam_antlr::TokenStreamIOException(csie.io);
		}
		catch (xparam_antlr::CharStreamException& cse) {
		   throw xparam_antlr::TokenStreamException(cse.getMessage());
		}
tryAgain:;
	}
}

void TypeNameLexer::mTYPENAME(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = TYPENAME;
	int _saveIndex;
	
	try {      // for error handling
		mGWS(false);
		mID(false);
		mGWS(false);
		{
		for (;;) {
			if ((LA(1)==static_cast<unsigned char>(':'))) {
				match("::");
				mGWS(false);
				mID(false);
				mGWS(false);
			}
			else {
				goto _loop3;
			}
			
		}
		_loop3:;
		}
		{
		if ((LA(1)==static_cast<unsigned char>('<'))) {
			mTEMPLATE_ARGS(false);
		}
		else {
		}
		
		}
	}
	catch (RecognitionException& ex) {
		if (inputState->guessing==0) {

			
					throw Error("Bad Typename");
				

		} else {
			throw ex;
		}
	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void TypeNameLexer::mGWS(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = GWS;
	int _saveIndex;
	
	{
	for (;;) {
		if ((LA(1)==static_cast<unsigned char>('\t')||LA(1)==static_cast<unsigned char>('\n')||LA(1)==static_cast<unsigned char>('\r')||LA(1)==static_cast<unsigned char>(' '))) {
			_saveIndex = text.length();
			mWS(false);
			text.erase(_saveIndex);
		}
		else {
			goto _loop8;
		}
		
	}
	_loop8:;
	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void TypeNameLexer::mID(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = ID;
	int _saveIndex;
	
	{
	switch ( LA(1)) {
	case static_cast<unsigned char>('a'):
	case static_cast<unsigned char>('b'):
	case static_cast<unsigned char>('c'):
	case static_cast<unsigned char>('d'):
	case static_cast<unsigned char>('e'):
	case static_cast<unsigned char>('f'):
	case static_cast<unsigned char>('g'):
	case static_cast<unsigned char>('h'):
	case static_cast<unsigned char>('i'):
	case static_cast<unsigned char>('j'):
	case static_cast<unsigned char>('k'):
	case static_cast<unsigned char>('l'):
	case static_cast<unsigned char>('m'):
	case static_cast<unsigned char>('n'):
	case static_cast<unsigned char>('o'):
	case static_cast<unsigned char>('p'):
	case static_cast<unsigned char>('q'):
	case static_cast<unsigned char>('r'):
	case static_cast<unsigned char>('s'):
	case static_cast<unsigned char>('t'):
	case static_cast<unsigned char>('u'):
	case static_cast<unsigned char>('v'):
	case static_cast<unsigned char>('w'):
	case static_cast<unsigned char>('x'):
	case static_cast<unsigned char>('y'):
	case static_cast<unsigned char>('z'):
	{
		matchRange(static_cast<unsigned char>('a'),static_cast<unsigned char>('z'));
		break;
	}
	case static_cast<unsigned char>('A'):
	case static_cast<unsigned char>('B'):
	case static_cast<unsigned char>('C'):
	case static_cast<unsigned char>('D'):
	case static_cast<unsigned char>('E'):
	case static_cast<unsigned char>('F'):
	case static_cast<unsigned char>('G'):
	case static_cast<unsigned char>('H'):
	case static_cast<unsigned char>('I'):
	case static_cast<unsigned char>('J'):
	case static_cast<unsigned char>('K'):
	case static_cast<unsigned char>('L'):
	case static_cast<unsigned char>('M'):
	case static_cast<unsigned char>('N'):
	case static_cast<unsigned char>('O'):
	case static_cast<unsigned char>('P'):
	case static_cast<unsigned char>('Q'):
	case static_cast<unsigned char>('R'):
	case static_cast<unsigned char>('S'):
	case static_cast<unsigned char>('T'):
	case static_cast<unsigned char>('U'):
	case static_cast<unsigned char>('V'):
	case static_cast<unsigned char>('W'):
	case static_cast<unsigned char>('X'):
	case static_cast<unsigned char>('Y'):
	case static_cast<unsigned char>('Z'):
	{
		matchRange(static_cast<unsigned char>('A'),static_cast<unsigned char>('Z'));
		break;
	}
	case static_cast<unsigned char>('_'):
	{
		match(static_cast<unsigned char>('_'));
		break;
	}
	default:
	{
		throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
	}
	}
	}
	{
	for (;;) {
		switch ( LA(1)) {
		case static_cast<unsigned char>('a'):
		case static_cast<unsigned char>('b'):
		case static_cast<unsigned char>('c'):
		case static_cast<unsigned char>('d'):
		case static_cast<unsigned char>('e'):
		case static_cast<unsigned char>('f'):
		case static_cast<unsigned char>('g'):
		case static_cast<unsigned char>('h'):
		case static_cast<unsigned char>('i'):
		case static_cast<unsigned char>('j'):
		case static_cast<unsigned char>('k'):
		case static_cast<unsigned char>('l'):
		case static_cast<unsigned char>('m'):
		case static_cast<unsigned char>('n'):
		case static_cast<unsigned char>('o'):
		case static_cast<unsigned char>('p'):
		case static_cast<unsigned char>('q'):
		case static_cast<unsigned char>('r'):
		case static_cast<unsigned char>('s'):
		case static_cast<unsigned char>('t'):
		case static_cast<unsigned char>('u'):
		case static_cast<unsigned char>('v'):
		case static_cast<unsigned char>('w'):
		case static_cast<unsigned char>('x'):
		case static_cast<unsigned char>('y'):
		case static_cast<unsigned char>('z'):
		{
			matchRange(static_cast<unsigned char>('a'),static_cast<unsigned char>('z'));
			break;
		}
		case static_cast<unsigned char>('A'):
		case static_cast<unsigned char>('B'):
		case static_cast<unsigned char>('C'):
		case static_cast<unsigned char>('D'):
		case static_cast<unsigned char>('E'):
		case static_cast<unsigned char>('F'):
		case static_cast<unsigned char>('G'):
		case static_cast<unsigned char>('H'):
		case static_cast<unsigned char>('I'):
		case static_cast<unsigned char>('J'):
		case static_cast<unsigned char>('K'):
		case static_cast<unsigned char>('L'):
		case static_cast<unsigned char>('M'):
		case static_cast<unsigned char>('N'):
		case static_cast<unsigned char>('O'):
		case static_cast<unsigned char>('P'):
		case static_cast<unsigned char>('Q'):
		case static_cast<unsigned char>('R'):
		case static_cast<unsigned char>('S'):
		case static_cast<unsigned char>('T'):
		case static_cast<unsigned char>('U'):
		case static_cast<unsigned char>('V'):
		case static_cast<unsigned char>('W'):
		case static_cast<unsigned char>('X'):
		case static_cast<unsigned char>('Y'):
		case static_cast<unsigned char>('Z'):
		{
			matchRange(static_cast<unsigned char>('A'),static_cast<unsigned char>('Z'));
			break;
		}
		case static_cast<unsigned char>('_'):
		{
			match(static_cast<unsigned char>('_'));
			break;
		}
		case static_cast<unsigned char>('0'):
		case static_cast<unsigned char>('1'):
		case static_cast<unsigned char>('2'):
		case static_cast<unsigned char>('3'):
		case static_cast<unsigned char>('4'):
		case static_cast<unsigned char>('5'):
		case static_cast<unsigned char>('6'):
		case static_cast<unsigned char>('7'):
		case static_cast<unsigned char>('8'):
		case static_cast<unsigned char>('9'):
		{
			matchRange(static_cast<unsigned char>('0'),static_cast<unsigned char>('9'));
			break;
		}
		default:
		{
			goto _loop12;
		}
		}
	}
	_loop12:;
	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void TypeNameLexer::mTEMPLATE_ARGS(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = TEMPLATE_ARGS;
	int _saveIndex;
	
	match(static_cast<unsigned char>('<'));
	mGWS(false);
	mONE_TEMPLATE_ARG(false);
	mGWS(false);
	{
	for (;;) {
		if ((LA(1)==static_cast<unsigned char>(','))) {
			match(static_cast<unsigned char>(','));
			mGWS(false);
			mONE_TEMPLATE_ARG(false);
			mGWS(false);
		}
		else {
			goto _loop15;
		}
		
	}
	_loop15:;
	}
	match(static_cast<unsigned char>('>'));
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void TypeNameLexer::mWS(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = WS;
	int _saveIndex;
	
	switch ( LA(1)) {
	case static_cast<unsigned char>(' '):
	{
		match(static_cast<unsigned char>(' '));
		break;
	}
	case static_cast<unsigned char>('\t'):
	{
		match(static_cast<unsigned char>('\t'));
		break;
	}
	case static_cast<unsigned char>('\r'):
	{
		match(static_cast<unsigned char>('\r'));
		break;
	}
	case static_cast<unsigned char>('\n'):
	{
		match(static_cast<unsigned char>('\n'));
		break;
	}
	default:
	{
		throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
	}
	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void TypeNameLexer::mONE_TEMPLATE_ARG(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = ONE_TEMPLATE_ARG;
	int _saveIndex;
	
	mPOSSIBLE_CONST(false);
	mTYPENAME(false);
	mGWS(false);
	{
	switch ( LA(1)) {
	case static_cast<unsigned char>('*'):
	{
		match(static_cast<unsigned char>('*'));
		break;
	}
	case static_cast<unsigned char>('\t'):
	case static_cast<unsigned char>('\n'):
	case static_cast<unsigned char>('\r'):
	case static_cast<unsigned char>(' '):
	case static_cast<unsigned char>(','):
	case static_cast<unsigned char>('>'):
	{
		break;
	}
	default:
	{
		throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
	}
	}
	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void TypeNameLexer::mPOSSIBLE_CONST(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = POSSIBLE_CONST;
	int _saveIndex;
	
	bool synPredMatched20 = false;
	if (((LA(1)==static_cast<unsigned char>('c')))) {
		int _m20 = mark();
		synPredMatched20 = true;
		inputState->guessing++;
		try {
			{
			match("const");
			mWS(false);
			}
		}
		catch (xparam_antlr::RecognitionException& pe) {
			synPredMatched20 = false;
		}
		rewind(_m20);
		inputState->guessing--;
	}
	if ( synPredMatched20 ) {
		match("const");
		{
		int _cnt22=0;
		for (;;) {
			if ((LA(1)==static_cast<unsigned char>('\t')||LA(1)==static_cast<unsigned char>('\n')||LA(1)==static_cast<unsigned char>('\r')||LA(1)==static_cast<unsigned char>(' '))) {
				_saveIndex = text.length();
				mWS(false);
				text.erase(_saveIndex);
			}
			else {
				if ( _cnt22>=1 ) { goto _loop22; } else {throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
			}
			
			_cnt22++;
		}
		_loop22:;
		}
		if ( inputState->guessing==0 ) {

			text+=' ';

		}
	}
	else if ((LA(1)==static_cast<unsigned char>('\t')||LA(1)==static_cast<unsigned char>('\n')||LA(1)==static_cast<unsigned char>('\r')||LA(1)==static_cast<unsigned char>(' ')||LA(1)==static_cast<unsigned char>('A')||LA(1)==static_cast<unsigned char>('B')||LA(1)==static_cast<unsigned char>('C')||LA(1)==static_cast<unsigned char>('D')||LA(1)==static_cast<unsigned char>('E')||LA(1)==static_cast<unsigned char>('F')||LA(1)==static_cast<unsigned char>('G')||LA(1)==static_cast<unsigned char>('H')||LA(1)==static_cast<unsigned char>('I')||LA(1)==static_cast<unsigned char>('J')||LA(1)==static_cast<unsigned char>('K')||LA(1)==static_cast<unsigned char>('L')||LA(1)==static_cast<unsigned char>('M')||LA(1)==static_cast<unsigned char>('N')||LA(1)==static_cast<unsigned char>('O')||LA(1)==static_cast<unsigned char>('P')||LA(1)==static_cast<unsigned char>('Q')||LA(1)==static_cast<unsigned char>('R')||LA(1)==static_cast<unsigned char>('S')||LA(1)==static_cast<unsigned char>('T')||LA(1)==static_cast<unsigned char>('U')||LA(1)==static_cast<unsigned char>('V')||LA(1)==static_cast<unsigned char>('W')||LA(1)==static_cast<unsigned char>('X')||LA(1)==static_cast<unsigned char>('Y')||LA(1)==static_cast<unsigned char>('Z')||LA(1)==static_cast<unsigned char>('_')||LA(1)==static_cast<unsigned char>('a')||LA(1)==static_cast<unsigned char>('b')||LA(1)==static_cast<unsigned char>('c')||LA(1)==static_cast<unsigned char>('d')||LA(1)==static_cast<unsigned char>('e')||LA(1)==static_cast<unsigned char>('f')||LA(1)==static_cast<unsigned char>('g')||LA(1)==static_cast<unsigned char>('h')||LA(1)==static_cast<unsigned char>('i')||LA(1)==static_cast<unsigned char>('j')||LA(1)==static_cast<unsigned char>('k')||LA(1)==static_cast<unsigned char>('l')||LA(1)==static_cast<unsigned char>('m')||LA(1)==static_cast<unsigned char>('n')||LA(1)==static_cast<unsigned char>('o')||LA(1)==static_cast<unsigned char>('p')||LA(1)==static_cast<unsigned char>('q')||LA(1)==static_cast<unsigned char>('r')||LA(1)==static_cast<unsigned char>('s')||LA(1)==static_cast<unsigned char>('t')||LA(1)==static_cast<unsigned char>('u')||LA(1)==static_cast<unsigned char>('v')||LA(1)==static_cast<unsigned char>('w')||LA(1)==static_cast<unsigned char>('x')||LA(1)==static_cast<unsigned char>('y')||LA(1)==static_cast<unsigned char>('z'))) {
	}
	else {
		throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
	}
	
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}



ANTLR_END_NAMESPACE
