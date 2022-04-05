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

/* $ANTLR 2.7.1: "loader_lexer.g" -> "DynamicLoaderLexer.cpp"$ */


#pragma warning (disable: 4786)


#include <../src_include/DynamicLoaderLexer.hpp>
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



DynamicLoaderLexer::DynamicLoaderLexer(std::istream& in)
	: xparam_antlr::CharScanner(new xparam_antlr::CharBuffer(in))
{
	setCaseSensitive(true);
	initLiterals();
}

DynamicLoaderLexer::DynamicLoaderLexer(xparam_antlr::InputBuffer& ib)
	: xparam_antlr::CharScanner(ib)
{
	setCaseSensitive(true);
	initLiterals();
}

DynamicLoaderLexer::DynamicLoaderLexer(const xparam_antlr::LexerSharedInputState& state)
	: xparam_antlr::CharScanner(state)
{
	setCaseSensitive(true);
	initLiterals();
}

void DynamicLoaderLexer::initLiterals()
{
	literals["["] = 5;
	literals["=>"] = 4;
	literals["]"] = 7;
	literals[","] = 6;
}
bool DynamicLoaderLexer::getCaseSensitiveLiterals() const
{
	return true;
}

xparam_antlr::RefToken DynamicLoaderLexer::nextToken()
{
	xparam_antlr::RefToken theRetToken;
	for (;;) {
		xparam_antlr::RefToken theRetToken;
		int _ttype = xparam_antlr::Token::INVALID_TYPE;
		resetText();
		try {   // for char stream error handling
			try {   // for lexical error handling
				if ((_tokenSet_0.member(LA(1)))) {
					mMAIN_SWITCH(true);
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

void DynamicLoaderLexer::mWS(bool _createToken) {
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

void DynamicLoaderLexer::mMAIN_SWITCH(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = MAIN_SWITCH;
	int _saveIndex;
	
	try {      // for error handling
		switch ( LA(1)) {
		case static_cast<unsigned char>(','):
		case static_cast<unsigned char>(';'):
		case static_cast<unsigned char>('['):
		case static_cast<unsigned char>(']'):
		{
			mRESERVED_SYMBOL(false);
			break;
		}
		case static_cast<unsigned char>('\t'):
		case static_cast<unsigned char>('\n'):
		case static_cast<unsigned char>('\r'):
		case static_cast<unsigned char>(' '):
		{
			{
			int _cnt4=0;
			for (;;) {
				if ((_tokenSet_1.member(LA(1)))) {
					mWS(false);
				}
				else {
					if ( _cnt4>=1 ) { goto _loop4; } else {throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
				}
				
				_cnt4++;
			}
			_loop4:;
			}
			if ( inputState->guessing==0 ) {

				_ttype = Token::SKIP;

			}
			break;
		}
		case static_cast<unsigned char>('#'):
		{
			mCOMMENT(false);
			if ( inputState->guessing==0 ) {

				_ttype = Token::SKIP;

			}
			break;
		}
		case static_cast<unsigned char>('='):
		{
			match("=>");
			break;
		}
		default:
			bool synPredMatched9 = false;
			if (((_tokenSet_2.member(LA(1))))) {
				int _m9 = mark();
				synPredMatched9 = true;
				inputState->guessing++;
				try {
					{
					mID(false);
					{
					for (;;) {
						if ((_tokenSet_1.member(LA(1)))) {
							mWS(false);
						}
						else {
							goto _loop7;
						}
						
					}
					_loop7:;
					}
					{
					switch ( LA(1)) {
					case static_cast<unsigned char>('<'):
					{
						match(static_cast<unsigned char>('<'));
						break;
					}
					case static_cast<unsigned char>(':'):
					{
						match("::");
						break;
					}
					default:
					{
						throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
					}
					}
					}
					}
				}
				catch (xparam_antlr::RecognitionException& pe) {
					synPredMatched9 = false;
				}
				rewind(_m9);
				inputState->guessing--;
			}
			if ( synPredMatched9 ) {
				mTYPENAME(false);
				if ( inputState->guessing==0 ) {

					_ttype = TYPENAME;

				}
			}
			else {
				bool synPredMatched13 = false;
				if (((_tokenSet_2.member(LA(1))))) {
					int _m13 = mark();
					synPredMatched13 = true;
					inputState->guessing++;
					try {
						{
						mID(false);
						{
						if ((_tokenSet_3.member(LA(1)))) {
							{
							match(_tokenSet_3);
							}
						}
						else if (true&&(LA(1) == EOF_CHAR)) {
						}
						else {
							throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
						}
						
						}
						}
					}
					catch (xparam_antlr::RecognitionException& pe) {
						synPredMatched13 = false;
					}
					rewind(_m13);
					inputState->guessing--;
				}
				if ( synPredMatched13 ) {
					mID(false);
					if ( inputState->guessing==0 ) {

						_ttype = ID;

					}
				}
				else if ((_tokenSet_4.member(LA(1)))) {
					mFILENAME(false);
					if ( inputState->guessing==0 ) {

						_ttype = FILENAME;

					}
				}
		else {
			throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
		}
		}}
	}
	catch (RecognitionException& ex) {
		if (inputState->guessing==0) {

			
					throw Error("illegal token - " + getText());
				

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

void DynamicLoaderLexer::mRESERVED_SYMBOL(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = RESERVED_SYMBOL;
	int _saveIndex;
	
	switch ( LA(1)) {
	case static_cast<unsigned char>('['):
	{
		match(static_cast<unsigned char>('['));
		break;
	}
	case static_cast<unsigned char>(']'):
	{
		match(static_cast<unsigned char>(']'));
		break;
	}
	case static_cast<unsigned char>(','):
	{
		match(static_cast<unsigned char>(','));
		break;
	}
	case static_cast<unsigned char>(';'):
	{
		match(static_cast<unsigned char>(';'));
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

void DynamicLoaderLexer::mCOMMENT(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = COMMENT;
	int _saveIndex;
	
	match(static_cast<unsigned char>('#'));
	{
	for (;;) {
		if ((_tokenSet_5.member(LA(1)))) {
			matchNot(static_cast<unsigned char>('\n'));
		}
		else {
			goto _loop17;
		}
		
	}
	_loop17:;
	}
	{
	if ((LA(1)==static_cast<unsigned char>('\n'))) {
		match(static_cast<unsigned char>('\n'));
	}
	else {
	}
	
	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void DynamicLoaderLexer::mID(bool _createToken) {
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
			goto _loop22;
		}
		}
	}
	_loop22:;
	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void DynamicLoaderLexer::mTYPENAME(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = TYPENAME;
	int _saveIndex;
	
	try {      // for error handling
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
				goto _loop31;
			}
			
		}
		_loop31:;
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

void DynamicLoaderLexer::mFILENAME(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = FILENAME;
	int _saveIndex;
	
	{
	int _cnt25=0;
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
		case static_cast<unsigned char>('/'):
		{
			match(static_cast<unsigned char>('/'));
			break;
		}
		case static_cast<unsigned char>('\\'):
		{
			match(static_cast<unsigned char>('\\'));
			break;
		}
		case static_cast<unsigned char>('.'):
		{
			match(static_cast<unsigned char>('.'));
			break;
		}
		case static_cast<unsigned char>('-'):
		{
			match(static_cast<unsigned char>('-'));
			break;
		}
		default:
		{
			if ( _cnt25>=1 ) { goto _loop25; } else {throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
		}
		}
		_cnt25++;
	}
	_loop25:;
	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void DynamicLoaderLexer::mGWS(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = GWS;
	int _saveIndex;
	
	{
	for (;;) {
		if ((_tokenSet_1.member(LA(1)))) {
			_saveIndex = text.length();
			mWS(false);
			text.erase(_saveIndex);
		}
		else {
			goto _loop28;
		}
		
	}
	_loop28:;
	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void DynamicLoaderLexer::mTEMPLATE_ARGS(bool _createToken) {
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
			goto _loop35;
		}
		
	}
	_loop35:;
	}
	match(static_cast<unsigned char>('>'));
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void DynamicLoaderLexer::mONE_TEMPLATE_ARG(bool _createToken) {
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

void DynamicLoaderLexer::mPOSSIBLE_CONST(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = POSSIBLE_CONST;
	int _saveIndex;
	
	bool synPredMatched40 = false;
	if (((LA(1)==static_cast<unsigned char>('c')))) {
		int _m40 = mark();
		synPredMatched40 = true;
		inputState->guessing++;
		try {
			{
			match("const");
			mWS(false);
			}
		}
		catch (xparam_antlr::RecognitionException& pe) {
			synPredMatched40 = false;
		}
		rewind(_m40);
		inputState->guessing--;
	}
	if ( synPredMatched40 ) {
		match("const");
		{
		int _cnt42=0;
		for (;;) {
			if ((_tokenSet_1.member(LA(1)))) {
				_saveIndex = text.length();
				mWS(false);
				text.erase(_saveIndex);
			}
			else {
				if ( _cnt42>=1 ) { goto _loop42; } else {throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
			}
			
			_cnt42++;
		}
		_loop42:;
		}
		if ( inputState->guessing==0 ) {

			text+=' ';

		}
	}
	else if ((_tokenSet_2.member(LA(1)))) {
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


const unsigned long DynamicLoaderLexer::_tokenSet_0_data_[] = { 9728UL, 738193417UL, 3221225470UL, 134217726UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet DynamicLoaderLexer::_tokenSet_0(_tokenSet_0_data_,10);
const unsigned long DynamicLoaderLexer::_tokenSet_1_data_[] = { 9728UL, 1UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet DynamicLoaderLexer::_tokenSet_1(_tokenSet_1_data_,10);
const unsigned long DynamicLoaderLexer::_tokenSet_2_data_[] = { 0UL, 0UL, 2281701374UL, 134217726UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet DynamicLoaderLexer::_tokenSet_2(_tokenSet_2_data_,10);
const unsigned long DynamicLoaderLexer::_tokenSet_3_data_[] = { 4294967295UL, 4294909951UL, 4026531839UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet DynamicLoaderLexer::_tokenSet_3(_tokenSet_3_data_,16);
const unsigned long DynamicLoaderLexer::_tokenSet_4_data_[] = { 0UL, 67100672UL, 2550136830UL, 134217726UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet DynamicLoaderLexer::_tokenSet_4(_tokenSet_4_data_,10);
const unsigned long DynamicLoaderLexer::_tokenSet_5_data_[] = { 4294966271UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet DynamicLoaderLexer::_tokenSet_5(_tokenSet_5_data_,16);

ANTLR_END_NAMESPACE
