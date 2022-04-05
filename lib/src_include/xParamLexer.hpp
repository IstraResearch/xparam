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

#ifndef INC_xParamLexer_hpp_
#define INC_xParamLexer_hpp_

#include "antlr/config.hpp"
/* $ANTLR 2.7.1: "lexer.g" -> "xParamLexer.hpp"$ */
#include "antlr/CommonToken.hpp"
#include "antlr/InputBuffer.hpp"
#include "antlr/BitSet.hpp"
#include <../src_include/xParamLexerTokenTypes.hpp>
#include "antlr/CharScanner.hpp"


#include "../xparam/xp_parser.h"
#include "xpv_parsed_value_token.h"


ANTLR_BEGIN_NAMESPACE(xParam_internal)
class xParamLexer : public xparam_antlr::CharScanner, public xParamLexerTokenTypes
 {


  private:
	Handle<ParsedValue> m_read_raw_bytes();


private:
	void initLiterals();
public:
	bool getCaseSensitiveLiterals() const;
public:
	xParamLexer(std::istream& in);
	xParamLexer(xparam_antlr::InputBuffer& ib);
	xParamLexer(const xparam_antlr::LexerSharedInputState& state);
	xparam_antlr::RefToken nextToken();
	protected: void mGLUE_CHAR(bool _createToken);
	protected: void mWS(bool _createToken);
	protected: void mSINGLE_LINE_WS(bool _createToken);
	public: void mMAIN_SWITCH(bool _createToken);
	protected: void mRESERVED_SYMBOL(bool _createToken);
	protected: void mCOMMENT(bool _createToken);
	protected: void mRAW_BYTES_HEADER(bool _createToken);
	protected: void mRAW_BYTES(bool _createToken);
	protected: void mID(bool _createToken);
	protected: void mTYPENAME(bool _createToken);
	protected: void mFLAG(bool _createToken);
	protected: void mCHAR(bool _createToken);
	protected: void mSTRING(bool _createToken);
	protected: void mTENTATIVE(bool _createToken);
	protected: void mURL(bool _createToken);
	protected: void mSHELL_STRINGS(bool _createToken);
	protected: void mREAL(bool _createToken);
	protected: void mINT(bool _createToken);
	protected: void mFREE_STRING(bool _createToken);
	protected: void mURL_NAME(bool _createToken);
	protected: void mFIRST_FREE_CHAR(bool _createToken);
	protected: void mDIGIT(bool _createToken);
	protected: void mHEX_DIGIT(bool _createToken);
	protected: void mOCT_DIGIT(bool _createToken);
	protected: void mBIN_DIGIT(bool _createToken);
	protected: void mSIGN(bool _createToken);
	protected: void mHEX_MARKER(bool _createToken);
	protected: void mBIN_MARKER(bool _createToken);
	protected: void mUNSIGNED_DEC_INT(bool _createToken);
	protected: void mUNSIGNED_OCT_INT(bool _createToken);
	protected: void mUNSIGNED_HEX_INT(bool _createToken);
	protected: void mUNSIGNED_BIN_INT(bool _createToken);
	protected: void mUNSIGNED_QUALIFIER(bool _createToken);
	protected: void mLONG_QUALIFIER(bool _createToken);
	protected: void mFLOATING_POINT_MANTISA(bool _createToken);
	protected: void mEXPONENT(bool _createToken);
	protected: void mAPOSTROPHE(bool _createToken);
	protected: void mQUOTES(bool _createToken);
	protected: void mBACKSLASH(bool _createToken);
	protected: void mCHAR_BODY(bool _createToken);
	protected: void mHEX_ESC_CHAR_BODY(bool _createToken);
	protected: void mGWS(bool _createToken);
	protected: void mTEMPLATE_ARGS(bool _createToken);
	protected: void mONE_TEMPLATE_ARG(bool _createToken);
	protected: void mPOSSIBLE_CONST(bool _createToken);
private:
	
	static const unsigned long _tokenSet_0_data_[];
	static const xparam_antlr::BitSet _tokenSet_0;
	static const unsigned long _tokenSet_1_data_[];
	static const xparam_antlr::BitSet _tokenSet_1;
	static const unsigned long _tokenSet_2_data_[];
	static const xparam_antlr::BitSet _tokenSet_2;
	static const unsigned long _tokenSet_3_data_[];
	static const xparam_antlr::BitSet _tokenSet_3;
	static const unsigned long _tokenSet_4_data_[];
	static const xparam_antlr::BitSet _tokenSet_4;
	static const unsigned long _tokenSet_5_data_[];
	static const xparam_antlr::BitSet _tokenSet_5;
	static const unsigned long _tokenSet_6_data_[];
	static const xparam_antlr::BitSet _tokenSet_6;
	static const unsigned long _tokenSet_7_data_[];
	static const xparam_antlr::BitSet _tokenSet_7;
	static const unsigned long _tokenSet_8_data_[];
	static const xparam_antlr::BitSet _tokenSet_8;
	static const unsigned long _tokenSet_9_data_[];
	static const xparam_antlr::BitSet _tokenSet_9;
	static const unsigned long _tokenSet_10_data_[];
	static const xparam_antlr::BitSet _tokenSet_10;
	static const unsigned long _tokenSet_11_data_[];
	static const xparam_antlr::BitSet _tokenSet_11;
	static const unsigned long _tokenSet_12_data_[];
	static const xparam_antlr::BitSet _tokenSet_12;
	static const unsigned long _tokenSet_13_data_[];
	static const xparam_antlr::BitSet _tokenSet_13;
	static const unsigned long _tokenSet_14_data_[];
	static const xparam_antlr::BitSet _tokenSet_14;
};

ANTLR_END_NAMESPACE
#endif /*INC_xParamLexer_hpp_*/
