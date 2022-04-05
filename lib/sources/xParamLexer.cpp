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

/* $ANTLR 2.7.1: "lexer.g" -> "xParamLexer.cpp"$ */
#include <../src_include/xParamLexer.hpp>
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



xParamLexer::xParamLexer(std::istream& in)
	: xparam_antlr::CharScanner(new xparam_antlr::CharBuffer(in))
{
	setCaseSensitive(true);
	initLiterals();
}

xParamLexer::xParamLexer(xparam_antlr::InputBuffer& ib)
	: xparam_antlr::CharScanner(ib)
{
	setCaseSensitive(true);
	initLiterals();
}

xParamLexer::xParamLexer(const xparam_antlr::LexerSharedInputState& state)
	: xparam_antlr::CharScanner(state)
{
	setCaseSensitive(true);
	initLiterals();
}

void xParamLexer::initLiterals()
{
	literals["["] = 12;
	literals["=>"] = 17;
	literals[")"] = 11;
	literals[","] = 16;
	literals["]"] = 13;
	literals[";"] = 4;
	literals["{"] = 14;
	literals["("] = 10;
	literals["="] = 7;
	literals["}"] = 15;
}
bool xParamLexer::getCaseSensitiveLiterals() const
{
	return true;
}

xparam_antlr::RefToken xParamLexer::nextToken()
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

void xParamLexer::mGLUE_CHAR(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = GLUE_CHAR;
	int _saveIndex;
	
	match(static_cast<unsigned char>('\1'));
	if ( inputState->guessing==0 ) {

		assert(cmdline_glue_char() == 1);

	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mWS(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = WS;
	int _saveIndex;
	
	switch ( LA(1)) {
	case static_cast<unsigned char>('\1'):
	{
		mGLUE_CHAR(false);
		break;
	}
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

void xParamLexer::mSINGLE_LINE_WS(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = SINGLE_LINE_WS;
	int _saveIndex;
	
	switch ( LA(1)) {
	case static_cast<unsigned char>('\1'):
	{
		mGLUE_CHAR(false);
		break;
	}
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

void xParamLexer::mMAIN_SWITCH(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = MAIN_SWITCH;
	int _saveIndex;
	xparam_antlr::RefToken r;
	
	try {      // for error handling
		switch ( LA(1)) {
		case static_cast<unsigned char>('('):
		case static_cast<unsigned char>(')'):
		case static_cast<unsigned char>(','):
		case static_cast<unsigned char>(';'):
		case static_cast<unsigned char>('='):
		case static_cast<unsigned char>('['):
		case static_cast<unsigned char>(']'):
		case static_cast<unsigned char>('{'):
		case static_cast<unsigned char>('}'):
		{
			mRESERVED_SYMBOL(false);
			break;
		}
		case static_cast<unsigned char>('\1'):
		case static_cast<unsigned char>('\t'):
		case static_cast<unsigned char>('\n'):
		case static_cast<unsigned char>('\r'):
		case static_cast<unsigned char>(' '):
		{
			{
			int _cnt6=0;
			for (;;) {
				if ((_tokenSet_1.member(LA(1)))) {
					mWS(false);
				}
				else {
					if ( _cnt6>=1 ) { goto _loop6; } else {throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
				}
				
				_cnt6++;
			}
			_loop6:;
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
		case static_cast<unsigned char>('\''):
		{
			mCHAR(false);
			if ( inputState->guessing==0 ) {

				_ttype = CHAR;

			}
			break;
		}
		case static_cast<unsigned char>('"'):
		{
			mSTRING(false);
			if ( inputState->guessing==0 ) {

				_ttype = STRING;

			}
			break;
		}
		case static_cast<unsigned char>('@'):
		{
			mURL(false);
			if ( inputState->guessing==0 ) {

				_ttype = URL;

			}
			break;
		}
		case static_cast<unsigned char>(':'):
		{
			mSHELL_STRINGS(false);
			if ( inputState->guessing==0 ) {

				_ttype = SHELL_STRINGS;

			}
			break;
		}
		default:
			bool synPredMatched8 = false;
			if (((LA(1)==static_cast<unsigned char>('r')))) {
				int _m8 = mark();
				synPredMatched8 = true;
				inputState->guessing++;
				try {
					{
					mRAW_BYTES_HEADER(false);
					}
				}
				catch (xparam_antlr::RecognitionException& pe) {
					synPredMatched8 = false;
				}
				rewind(_m8);
				inputState->guessing--;
			}
			if ( synPredMatched8 ) {
				mRAW_BYTES(true);
				r=_returnToken;
				if ( inputState->guessing==0 ) {

					r->setType(PARSED_VALUE); _token = r;

				}
			}
			else {
				bool synPredMatched11 = false;
				if (((_tokenSet_2.member(LA(1))))) {
					int _m11 = mark();
					synPredMatched11 = true;
					inputState->guessing++;
					try {
						{
						mID(false);
						{
						switch ( LA(1)) {
						case static_cast<unsigned char>('<'):
						{
							match(static_cast<unsigned char>('<'));
							break;
						}
						case static_cast<unsigned char>('('):
						{
							match(static_cast<unsigned char>('('));
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
						synPredMatched11 = false;
					}
					rewind(_m11);
					inputState->guessing--;
				}
				if ( synPredMatched11 ) {
					mTYPENAME(false);
					if ( inputState->guessing==0 ) {

						_ttype = TYPENAME;

					}
				}
				else {
					bool synPredMatched15 = false;
					if (((_tokenSet_2.member(LA(1))))) {
						int _m15 = mark();
						synPredMatched15 = true;
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
							synPredMatched15 = false;
						}
						rewind(_m15);
						inputState->guessing--;
					}
					if ( synPredMatched15 ) {
						mID(false);
						if ( inputState->guessing==0 ) {

							_ttype = ID;

						}
					}
					else {
						bool synPredMatched17 = false;
						if (((LA(1)==static_cast<unsigned char>('-')))) {
							int _m17 = mark();
							synPredMatched17 = true;
							inputState->guessing++;
							try {
								{
								mFLAG(false);
								}
							}
							catch (xparam_antlr::RecognitionException& pe) {
								synPredMatched17 = false;
							}
							rewind(_m17);
							inputState->guessing--;
						}
						if ( synPredMatched17 ) {
							mFLAG(false);
							if ( inputState->guessing==0 ) {

								_ttype = FLAG;

							}
						}
						else if ((_tokenSet_4.member(LA(1)))) {
							mTENTATIVE(false);
							if ( inputState->guessing==0 ) {

								_ttype = TENTATIVE;

							}
						}
		else {
			throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
		}
		}}}}
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

void xParamLexer::mRESERVED_SYMBOL(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = RESERVED_SYMBOL;
	int _saveIndex;
	
	switch ( LA(1)) {
	case static_cast<unsigned char>('('):
	{
		match(static_cast<unsigned char>('('));
		break;
	}
	case static_cast<unsigned char>(')'):
	{
		match(static_cast<unsigned char>(')'));
		break;
	}
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
	case static_cast<unsigned char>('{'):
	{
		match(static_cast<unsigned char>('{'));
		break;
	}
	case static_cast<unsigned char>('}'):
	{
		match(static_cast<unsigned char>('}'));
		break;
	}
	case static_cast<unsigned char>('='):
	{
		{
		match(static_cast<unsigned char>('='));
		{
		if ((LA(1)==static_cast<unsigned char>('>'))) {
			match(static_cast<unsigned char>('>'));
		}
		else {
		}
		
		}
		}
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

void xParamLexer::mCOMMENT(bool _createToken) {
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
			goto _loop32;
		}
		
	}
	_loop32:;
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

void xParamLexer::mRAW_BYTES_HEADER(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = RAW_BYTES_HEADER;
	int _saveIndex;
	
	match("raw<<<");
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mRAW_BYTES(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = RAW_BYTES;
	int _saveIndex;
	
	mRAW_BYTES_HEADER(false);
	if ( inputState->guessing==0 ) {

		
				Handle<ParsedValue> parsed_val = m_read_raw_bytes();
				ParsedValueToken *t = new ParsedValueToken(parsed_val);
				_token = RefToken(t);
			

	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mID(bool _createToken) {
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
			goto _loop47;
		}
		}
	}
	_loop47:;
	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mTYPENAME(bool _createToken) {
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
				goto _loop124;
			}
			
		}
		_loop124:;
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

void xParamLexer::mFLAG(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = FLAG;
	int _saveIndex;

	
	bool negated = false;
	

	
	try {      // for error handling
		_saveIndex=text.length();
		match(static_cast<unsigned char>('-'));
		text.erase(_saveIndex);
		{
		bool synPredMatched43 = false;
		if (((LA(1)==static_cast<unsigned char>('n')))) {
			int _m43 = mark();
			synPredMatched43 = true;
			inputState->guessing++;
			try {
				{
				match("no_");
				}
			}
			catch (xparam_antlr::RecognitionException& pe) {
				synPredMatched43 = false;
			}
			rewind(_m43);
			inputState->guessing--;
		}
		if ( synPredMatched43 ) {
			match("no_");
			if ( inputState->guessing==0 ) {

				negated=true;

			}
		}
		else if ((_tokenSet_2.member(LA(1)))) {
		}
		else {
			throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
		}
		
		}
		if ( inputState->guessing==0 ) {

			text = negated ? "-" : "+";

		}
		mID(false);
	}
	catch (RecognitionException& ex) {
		if (inputState->guessing==0) {

			
						throw Error("Bad flag setting");
				

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

void xParamLexer::mCHAR(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = CHAR;
	int _saveIndex;
	
	try {      // for error handling
		mAPOSTROPHE(false);
		{
		if ((_tokenSet_6.member(LA(1)))) {
			mCHAR_BODY(false);
		}
		else if ((LA(1)==static_cast<unsigned char>('"'))) {
			mQUOTES(false);
		}
		else {
			throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
		}
		
		}
		_saveIndex = text.length();
		mAPOSTROPHE(false);
		text.erase(_saveIndex);
	}
	catch (RecognitionException& ex) {
		if (inputState->guessing==0) {

			
					throw Error("Bad char literal");
				

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

void xParamLexer::mSTRING(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = STRING;
	int _saveIndex;
	
	try {      // for error handling
		mQUOTES(false);
		{
		for (;;) {
			if ((_tokenSet_6.member(LA(1)))) {
				mCHAR_BODY(false);
			}
			else if ((LA(1)==static_cast<unsigned char>('\''))) {
				mAPOSTROPHE(false);
			}
			else {
				goto _loop112;
			}
			
		}
		_loop112:;
		}
		_saveIndex = text.length();
		mQUOTES(false);
		text.erase(_saveIndex);
	}
	catch (RecognitionException& ex) {
		if (inputState->guessing==0) {

			
					throw Error("Bad string literal");
				

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

void xParamLexer::mTENTATIVE(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = TENTATIVE;
	int _saveIndex;
	
	bool synPredMatched22 = false;
	if (((_tokenSet_7.member(LA(1))))) {
		int _m22 = mark();
		synPredMatched22 = true;
		inputState->guessing++;
		try {
			{
			mREAL(false);
			{
			if ((_tokenSet_8.member(LA(1)))) {
				{
				match(_tokenSet_8);
				}
			}
			else if (true&&(LA(1)==EOF_CHAR)) {
			}
			else {
				throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
			}
			
			}
			}
		}
		catch (xparam_antlr::RecognitionException& pe) {
			synPredMatched22 = false;
		}
		rewind(_m22);
		inputState->guessing--;
	}
	if ( synPredMatched22 ) {
		mREAL(false);
		if ( inputState->guessing==0 ) {

			text = 'R' + text;

		}
	}
	else {
		bool synPredMatched26 = false;
		if (((_tokenSet_9.member(LA(1))))) {
			int _m26 = mark();
			synPredMatched26 = true;
			inputState->guessing++;
			try {
				{
				mINT(false);
				{
				if ((_tokenSet_8.member(LA(1)))) {
					{
					match(_tokenSet_8);
					}
				}
				else if (true&&(LA(1)==EOF_CHAR)) {
				}
				else {
					throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
				}
				
				}
				}
			}
			catch (xparam_antlr::RecognitionException& pe) {
				synPredMatched26 = false;
			}
			rewind(_m26);
			inputState->guessing--;
		}
		if ( synPredMatched26 ) {
			mINT(false);
			if ( inputState->guessing==0 ) {

				text = 'I' + text;

			}
		}
		else if ((_tokenSet_10.member(LA(1)))) {
			mFREE_STRING(false);
			if ( inputState->guessing==0 ) {

				text = 'S' + text;

			}
		}
	else {
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

void xParamLexer::mURL(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = URL;
	int _saveIndex;
	
	try {      // for error handling
		_saveIndex=text.length();
		match(static_cast<unsigned char>('@'));
		text.erase(_saveIndex);
		{
		for (;;) {
			if ((_tokenSet_1.member(LA(1)))) {
				_saveIndex = text.length();
				mWS(false);
				text.erase(_saveIndex);
			}
			else {
				goto _loop36;
			}
			
		}
		_loop36:;
		}
		mURL_NAME(false);
	}
	catch (RecognitionException& ex) {
		if (inputState->guessing==0) {

			
					throw Error("Bad URL name");
				

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

void xParamLexer::mSHELL_STRINGS(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = SHELL_STRINGS;
	int _saveIndex;

	
	bool last_was_glue = false;
	

	
	_saveIndex=text.length();
	match(static_cast<unsigned char>(':'));
	text.erase(_saveIndex);
	mGLUE_CHAR(false);
	{
	for (;;) {
		if ((LA(1)==static_cast<unsigned char>('\1'))) {
			mGLUE_CHAR(false);
			if ( inputState->guessing==0 ) {

				last_was_glue = true;

			}
		}
		else if (((LA(1)==static_cast<unsigned char>(':')))&&(!last_was_glue)) {
			match(static_cast<unsigned char>(':'));
		}
		else if ((_tokenSet_11.member(LA(1)))) {
			{
			match(_tokenSet_11);
			}
			if ( inputState->guessing==0 ) {

				last_was_glue = false;

			}
		}
		else {
			goto _loop139;
		}
		
	}
	_loop139:;
	}
	{
	if ((LA(1)==static_cast<unsigned char>(':'))) {
		_saveIndex=text.length();
		match(static_cast<unsigned char>(':'));
		text.erase(_saveIndex);
	}
	else if (true&&(LA(1) == EOF_CHAR)) {
	}
	else {
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

void xParamLexer::mREAL(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = REAL;
	int _saveIndex;
	
	{
	switch ( LA(1)) {
	case static_cast<unsigned char>('+'):
	case static_cast<unsigned char>('-'):
	{
		mSIGN(false);
		break;
	}
	case static_cast<unsigned char>('.'):
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
		break;
	}
	default:
	{
		throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
	}
	}
	}
	{
	bool synPredMatched100 = false;
	if (((_tokenSet_12.member(LA(1))))) {
		int _m100 = mark();
		synPredMatched100 = true;
		inputState->guessing++;
		try {
			{
			mFLOATING_POINT_MANTISA(false);
			}
		}
		catch (xparam_antlr::RecognitionException& pe) {
			synPredMatched100 = false;
		}
		rewind(_m100);
		inputState->guessing--;
	}
	if ( synPredMatched100 ) {
		mFLOATING_POINT_MANTISA(false);
		{
		if ((LA(1)==static_cast<unsigned char>('E')||LA(1)==static_cast<unsigned char>('e'))) {
			mEXPONENT(false);
		}
		else {
		}
		
		}
	}
	else if (((LA(1) >= static_cast<unsigned char>('0') && LA(1) <= static_cast<unsigned char>('9')))) {
		{
		int _cnt103=0;
		for (;;) {
			if (((LA(1) >= static_cast<unsigned char>('0') && LA(1) <= static_cast<unsigned char>('9')))) {
				mDIGIT(false);
			}
			else {
				if ( _cnt103>=1 ) { goto _loop103; } else {throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
			}
			
			_cnt103++;
		}
		_loop103:;
		}
		mEXPONENT(false);
	}
	else {
		throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
	}
	
	}
	{
	switch ( LA(1)) {
	case static_cast<unsigned char>('f'):
	{
		match(static_cast<unsigned char>('f'));
		break;
	}
	case static_cast<unsigned char>('F'):
	{
		match(static_cast<unsigned char>('F'));
		break;
	}
	case static_cast<unsigned char>('l'):
	{
		match(static_cast<unsigned char>('l'));
		break;
	}
	case static_cast<unsigned char>('L'):
	{
		match(static_cast<unsigned char>('L'));
		break;
	}
	default:
		{
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

void xParamLexer::mINT(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = INT;
	int _saveIndex;

	
	char long_qualifier = 'X';
	char unsigned_qualifier = 'X';
	char base;
	

	
	{
	switch ( LA(1)) {
	case static_cast<unsigned char>('+'):
	case static_cast<unsigned char>('-'):
	{
		mSIGN(false);
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
		break;
	}
	default:
	{
		throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
	}
	}
	}
	{
	bool synPredMatched79 = false;
	if (((LA(1)==static_cast<unsigned char>('0')))) {
		int _m79 = mark();
		synPredMatched79 = true;
		inputState->guessing++;
		try {
			{
			mHEX_MARKER(false);
			}
		}
		catch (xparam_antlr::RecognitionException& pe) {
			synPredMatched79 = false;
		}
		rewind(_m79);
		inputState->guessing--;
	}
	if ( synPredMatched79 ) {
		mUNSIGNED_HEX_INT(false);
		if ( inputState->guessing==0 ) {

			base='H';

		}
	}
	else {
		bool synPredMatched81 = false;
		if (((LA(1)==static_cast<unsigned char>('0')))) {
			int _m81 = mark();
			synPredMatched81 = true;
			inputState->guessing++;
			try {
				{
				mBIN_MARKER(false);
				}
			}
			catch (xparam_antlr::RecognitionException& pe) {
				synPredMatched81 = false;
			}
			rewind(_m81);
			inputState->guessing--;
		}
		if ( synPredMatched81 ) {
			mUNSIGNED_BIN_INT(false);
			if ( inputState->guessing==0 ) {

				base='B';

			}
		}
		else if ((LA(1)==static_cast<unsigned char>('0'))) {
			mUNSIGNED_OCT_INT(false);
			if ( inputState->guessing==0 ) {

				base='O';

			}
		}
		else if (((LA(1) >= static_cast<unsigned char>('1') && LA(1) <= static_cast<unsigned char>('9')))) {
			mUNSIGNED_DEC_INT(false);
			if ( inputState->guessing==0 ) {

				base='D';

			}
		}
	else {
		throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
	}
	}
	}
	{
	if ((LA(1)==static_cast<unsigned char>('U')||LA(1)==static_cast<unsigned char>('u'))) {
		mUNSIGNED_QUALIFIER(false);
		if ( inputState->guessing==0 ) {

			unsigned_qualifier = 'U';

		}
	}
	else {
	}
	
	}
	{
	if ((LA(1)==static_cast<unsigned char>('L')||LA(1)==static_cast<unsigned char>('l'))) {
		mLONG_QUALIFIER(false);
		if ( inputState->guessing==0 ) {

			long_qualifier = 'L';

		}
	}
	else {
	}
	
	}
	if ( inputState->guessing==0 ) {

		
			  text = string(1,base) + unsigned_qualifier + long_qualifier + text;
			

	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mFREE_STRING(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = FREE_STRING;
	int _saveIndex;
	
	mFIRST_FREE_CHAR(false);
	{
	for (;;) {
		switch ( LA(1)) {
		case static_cast<unsigned char>('.'):
		case static_cast<unsigned char>('/'):
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
		case static_cast<unsigned char>('\\'):
		case static_cast<unsigned char>('_'):
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
			mFIRST_FREE_CHAR(false);
			break;
		}
		case static_cast<unsigned char>('-'):
		{
			match(static_cast<unsigned char>('-'));
			break;
		}
		case static_cast<unsigned char>(':'):
		{
			match(static_cast<unsigned char>(':'));
			break;
		}
		default:
		{
			goto _loop51;
		}
		}
	}
	_loop51:;
	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mURL_NAME(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = URL_NAME;
	int _saveIndex;
	
	{
	int _cnt39=0;
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
		case static_cast<unsigned char>('_'):
		{
			match(static_cast<unsigned char>('_'));
			break;
		}
		case static_cast<unsigned char>('-'):
		{
			match(static_cast<unsigned char>('-'));
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
		case static_cast<unsigned char>(':'):
		{
			match(static_cast<unsigned char>(':'));
			break;
		}
		case static_cast<unsigned char>('.'):
		{
			match(static_cast<unsigned char>('.'));
			break;
		}
		default:
		{
			if ( _cnt39>=1 ) { goto _loop39; } else {throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
		}
		}
		_cnt39++;
	}
	_loop39:;
	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mFIRST_FREE_CHAR(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = FIRST_FREE_CHAR;
	int _saveIndex;
	
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

void xParamLexer::mDIGIT(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = DIGIT;
	int _saveIndex;
	
	matchRange(static_cast<unsigned char>('0'),static_cast<unsigned char>('9'));
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mHEX_DIGIT(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = HEX_DIGIT;
	int _saveIndex;
	
	switch ( LA(1)) {
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
	case static_cast<unsigned char>('a'):
	case static_cast<unsigned char>('b'):
	case static_cast<unsigned char>('c'):
	case static_cast<unsigned char>('d'):
	case static_cast<unsigned char>('e'):
	case static_cast<unsigned char>('f'):
	{
		matchRange(static_cast<unsigned char>('a'),static_cast<unsigned char>('f'));
		break;
	}
	case static_cast<unsigned char>('A'):
	case static_cast<unsigned char>('B'):
	case static_cast<unsigned char>('C'):
	case static_cast<unsigned char>('D'):
	case static_cast<unsigned char>('E'):
	case static_cast<unsigned char>('F'):
	{
		matchRange(static_cast<unsigned char>('A'),static_cast<unsigned char>('F'));
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

void xParamLexer::mOCT_DIGIT(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = OCT_DIGIT;
	int _saveIndex;
	
	matchRange(static_cast<unsigned char>('0'),static_cast<unsigned char>('7'));
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mBIN_DIGIT(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = BIN_DIGIT;
	int _saveIndex;
	
	matchRange(static_cast<unsigned char>('0'),static_cast<unsigned char>('1'));
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mSIGN(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = SIGN;
	int _saveIndex;
	
	switch ( LA(1)) {
	case static_cast<unsigned char>('+'):
	{
		match(static_cast<unsigned char>('+'));
		break;
	}
	case static_cast<unsigned char>('-'):
	{
		match(static_cast<unsigned char>('-'));
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

void xParamLexer::mHEX_MARKER(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = HEX_MARKER;
	int _saveIndex;
	
	match(static_cast<unsigned char>('0'));
	{
	switch ( LA(1)) {
	case static_cast<unsigned char>('x'):
	{
		match(static_cast<unsigned char>('x'));
		break;
	}
	case static_cast<unsigned char>('X'):
	{
		match(static_cast<unsigned char>('X'));
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

void xParamLexer::mBIN_MARKER(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = BIN_MARKER;
	int _saveIndex;
	
	match(static_cast<unsigned char>('0'));
	{
	switch ( LA(1)) {
	case static_cast<unsigned char>('b'):
	{
		match(static_cast<unsigned char>('b'));
		break;
	}
	case static_cast<unsigned char>('B'):
	{
		match(static_cast<unsigned char>('B'));
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

void xParamLexer::mUNSIGNED_DEC_INT(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = UNSIGNED_DEC_INT;
	int _saveIndex;
	
	matchRange(static_cast<unsigned char>('1'),static_cast<unsigned char>('9'));
	{
	for (;;) {
		if (((LA(1) >= static_cast<unsigned char>('0') && LA(1) <= static_cast<unsigned char>('9')))) {
			mDIGIT(false);
		}
		else {
			goto _loop63;
		}
		
	}
	_loop63:;
	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mUNSIGNED_OCT_INT(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = UNSIGNED_OCT_INT;
	int _saveIndex;
	
	match(static_cast<unsigned char>('0'));
	{
	for (;;) {
		if (((LA(1) >= static_cast<unsigned char>('0') && LA(1) <= static_cast<unsigned char>('7')))) {
			mOCT_DIGIT(false);
		}
		else {
			goto _loop66;
		}
		
	}
	_loop66:;
	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mUNSIGNED_HEX_INT(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = UNSIGNED_HEX_INT;
	int _saveIndex;
	
	mHEX_MARKER(false);
	{
	int _cnt69=0;
	for (;;) {
		if ((_tokenSet_13.member(LA(1)))) {
			mHEX_DIGIT(false);
		}
		else {
			if ( _cnt69>=1 ) { goto _loop69; } else {throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
		}
		
		_cnt69++;
	}
	_loop69:;
	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mUNSIGNED_BIN_INT(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = UNSIGNED_BIN_INT;
	int _saveIndex;
	
	mBIN_MARKER(false);
	{
	int _cnt72=0;
	for (;;) {
		if ((LA(1)==static_cast<unsigned char>('0')||LA(1)==static_cast<unsigned char>('1'))) {
			mBIN_DIGIT(false);
		}
		else {
			if ( _cnt72>=1 ) { goto _loop72; } else {throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
		}
		
		_cnt72++;
	}
	_loop72:;
	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mUNSIGNED_QUALIFIER(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = UNSIGNED_QUALIFIER;
	int _saveIndex;
	
	switch ( LA(1)) {
	case static_cast<unsigned char>('U'):
	{
		match(static_cast<unsigned char>('U'));
		break;
	}
	case static_cast<unsigned char>('u'):
	{
		match(static_cast<unsigned char>('u'));
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

void xParamLexer::mLONG_QUALIFIER(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = LONG_QUALIFIER;
	int _saveIndex;
	
	switch ( LA(1)) {
	case static_cast<unsigned char>('L'):
	{
		match(static_cast<unsigned char>('L'));
		break;
	}
	case static_cast<unsigned char>('l'):
	{
		match(static_cast<unsigned char>('l'));
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

void xParamLexer::mFLOATING_POINT_MANTISA(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = FLOATING_POINT_MANTISA;
	int _saveIndex;
	
	switch ( LA(1)) {
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
		{
		int _cnt86=0;
		for (;;) {
			if (((LA(1) >= static_cast<unsigned char>('0') && LA(1) <= static_cast<unsigned char>('9')))) {
				mDIGIT(false);
			}
			else {
				if ( _cnt86>=1 ) { goto _loop86; } else {throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
			}
			
			_cnt86++;
		}
		_loop86:;
		}
		match(static_cast<unsigned char>('.'));
		{
		for (;;) {
			if (((LA(1) >= static_cast<unsigned char>('0') && LA(1) <= static_cast<unsigned char>('9')))) {
				mDIGIT(false);
			}
			else {
				goto _loop88;
			}
			
		}
		_loop88:;
		}
		break;
	}
	case static_cast<unsigned char>('.'):
	{
		match(static_cast<unsigned char>('.'));
		{
		int _cnt90=0;
		for (;;) {
			if (((LA(1) >= static_cast<unsigned char>('0') && LA(1) <= static_cast<unsigned char>('9')))) {
				mDIGIT(false);
			}
			else {
				if ( _cnt90>=1 ) { goto _loop90; } else {throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
			}
			
			_cnt90++;
		}
		_loop90:;
		}
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

void xParamLexer::mEXPONENT(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = EXPONENT;
	int _saveIndex;
	
	{
	switch ( LA(1)) {
	case static_cast<unsigned char>('e'):
	{
		match(static_cast<unsigned char>('e'));
		break;
	}
	case static_cast<unsigned char>('E'):
	{
		match(static_cast<unsigned char>('E'));
		break;
	}
	default:
	{
		throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
	}
	}
	}
	{
	switch ( LA(1)) {
	case static_cast<unsigned char>('+'):
	case static_cast<unsigned char>('-'):
	{
		mSIGN(false);
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
		break;
	}
	default:
	{
		throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
	}
	}
	}
	{
	int _cnt95=0;
	for (;;) {
		if (((LA(1) >= static_cast<unsigned char>('0') && LA(1) <= static_cast<unsigned char>('9')))) {
			mDIGIT(false);
		}
		else {
			if ( _cnt95>=1 ) { goto _loop95; } else {throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
		}
		
		_cnt95++;
	}
	_loop95:;
	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mAPOSTROPHE(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = APOSTROPHE;
	int _saveIndex;
	
	match(static_cast<unsigned char>('\''));
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mQUOTES(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = QUOTES;
	int _saveIndex;
	
	match(static_cast<unsigned char>('"'));
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mBACKSLASH(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = BACKSLASH;
	int _saveIndex;
	
	match(static_cast<unsigned char>('\\'));
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mCHAR_BODY(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = CHAR_BODY;
	int _saveIndex;
	
	if ((_tokenSet_14.member(LA(1)))) {
		{
		match(_tokenSet_14);
		}
	}
	else {
		bool synPredMatched116 = false;
		if (((LA(1)==static_cast<unsigned char>('\\')))) {
			int _m116 = mark();
			synPredMatched116 = true;
			inputState->guessing++;
			try {
				{
				mHEX_ESC_CHAR_BODY(false);
				}
			}
			catch (xparam_antlr::RecognitionException& pe) {
				synPredMatched116 = false;
			}
			rewind(_m116);
			inputState->guessing--;
		}
		if ( synPredMatched116 ) {
			mHEX_ESC_CHAR_BODY(false);
		}
		else if ((LA(1)==static_cast<unsigned char>('\\'))) {
			mBACKSLASH(false);
			matchNot(EOF/*_CHAR*/);
		}
	else {
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

void xParamLexer::mHEX_ESC_CHAR_BODY(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = HEX_ESC_CHAR_BODY;
	int _saveIndex;
	
	mBACKSLASH(false);
	{
	switch ( LA(1)) {
	case static_cast<unsigned char>('x'):
	{
		match(static_cast<unsigned char>('x'));
		break;
	}
	case static_cast<unsigned char>('X'):
	{
		match(static_cast<unsigned char>('X'));
		break;
	}
	default:
	{
		throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
	}
	}
	}
	mHEX_DIGIT(false);
	mHEX_DIGIT(false);
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mGWS(bool _createToken) {
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
			goto _loop121;
		}
		
	}
	_loop121:;
	}
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mTEMPLATE_ARGS(bool _createToken) {
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
			goto _loop128;
		}
		
	}
	_loop128:;
	}
	match(static_cast<unsigned char>('>'));
	if ( _createToken && _token==xparam_antlr::nullToken && _ttype!=xparam_antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void xParamLexer::mONE_TEMPLATE_ARG(bool _createToken) {
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
	case static_cast<unsigned char>('\1'):
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

void xParamLexer::mPOSSIBLE_CONST(bool _createToken) {
	int _ttype; xparam_antlr::RefToken _token; int _begin=text.length();
	_ttype = POSSIBLE_CONST;
	int _saveIndex;
	
	bool synPredMatched133 = false;
	if (((LA(1)==static_cast<unsigned char>('c')))) {
		int _m133 = mark();
		synPredMatched133 = true;
		inputState->guessing++;
		try {
			{
			match("const");
			mWS(false);
			}
		}
		catch (xparam_antlr::RecognitionException& pe) {
			synPredMatched133 = false;
		}
		rewind(_m133);
		inputState->guessing--;
	}
	if ( synPredMatched133 ) {
		match("const");
		{
		int _cnt135=0;
		for (;;) {
			if ((_tokenSet_1.member(LA(1)))) {
				_saveIndex = text.length();
				mWS(false);
				text.erase(_saveIndex);
			}
			else {
				if ( _cnt135>=1 ) { goto _loop135; } else {throw xparam_antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
			}
			
			_cnt135++;
		}
		_loop135:;
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


const unsigned long xParamLexer::_tokenSet_0_data_[] = { 9730UL, 805305229UL, 3221225471UL, 805306366UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet xParamLexer::_tokenSet_0(_tokenSet_0_data_,10);
const unsigned long xParamLexer::_tokenSet_1_data_[] = { 9730UL, 1UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet xParamLexer::_tokenSet_1(_tokenSet_1_data_,10);
const unsigned long xParamLexer::_tokenSet_2_data_[] = { 0UL, 0UL, 2281701374UL, 134217726UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet xParamLexer::_tokenSet_2(_tokenSet_2_data_,10);
const unsigned long xParamLexer::_tokenSet_3_data_[] = { 4294967295UL, 4227801087UL, 4026531839UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet xParamLexer::_tokenSet_3(_tokenSet_3_data_,16);
const unsigned long xParamLexer::_tokenSet_4_data_[] = { 0UL, 67102720UL, 2550136830UL, 134217726UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet xParamLexer::_tokenSet_4(_tokenSet_4_data_,10);
const unsigned long xParamLexer::_tokenSet_5_data_[] = { 4294966271UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet xParamLexer::_tokenSet_5(_tokenSet_5_data_,16);
const unsigned long xParamLexer::_tokenSet_6_data_[] = { 4294967295UL, 4294967163UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet xParamLexer::_tokenSet_6(_tokenSet_6_data_,16);
const unsigned long xParamLexer::_tokenSet_7_data_[] = { 0UL, 67069952UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet xParamLexer::_tokenSet_7(_tokenSet_7_data_,10);
const unsigned long xParamLexer::_tokenSet_8_data_[] = { 4294967295UL, 4160757759UL, 1744830465UL, 4160749569UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet xParamLexer::_tokenSet_8(_tokenSet_8_data_,16);
const unsigned long xParamLexer::_tokenSet_9_data_[] = { 0UL, 67053568UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet xParamLexer::_tokenSet_9(_tokenSet_9_data_,10);
const unsigned long xParamLexer::_tokenSet_10_data_[] = { 0UL, 67092480UL, 2550136830UL, 134217726UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet xParamLexer::_tokenSet_10(_tokenSet_10_data_,10);
const unsigned long xParamLexer::_tokenSet_11_data_[] = { 4294967293UL, 4227858431UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet xParamLexer::_tokenSet_11(_tokenSet_11_data_,16);
const unsigned long xParamLexer::_tokenSet_12_data_[] = { 0UL, 67059712UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet xParamLexer::_tokenSet_12(_tokenSet_12_data_,10);
const unsigned long xParamLexer::_tokenSet_13_data_[] = { 0UL, 67043328UL, 126UL, 126UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet xParamLexer::_tokenSet_13(_tokenSet_13_data_,10);
const unsigned long xParamLexer::_tokenSet_14_data_[] = { 4294967295UL, 4294967163UL, 4026531839UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const xparam_antlr::BitSet xParamLexer::_tokenSet_14(_tokenSet_14_data_,16);

ANTLR_END_NAMESPACE
