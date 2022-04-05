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

#ifndef INC_DynamicLoaderLexer_hpp_
#define INC_DynamicLoaderLexer_hpp_

#include "antlr/config.hpp"
/* $ANTLR 2.7.1: "loader_lexer.g" -> "DynamicLoaderLexer.hpp"$ */
#include "antlr/CommonToken.hpp"
#include "antlr/InputBuffer.hpp"
#include "antlr/BitSet.hpp"
#include <../src_include/DynamicLoaderLexerTokenTypes.hpp>
#include "antlr/CharScanner.hpp"
ANTLR_BEGIN_NAMESPACE(xParam_internal)
class DynamicLoaderLexer : public xparam_antlr::CharScanner, public DynamicLoaderLexerTokenTypes
 {


private:
	void initLiterals();
public:
	bool getCaseSensitiveLiterals() const;
public:
	DynamicLoaderLexer(std::istream& in);
	DynamicLoaderLexer(xparam_antlr::InputBuffer& ib);
	DynamicLoaderLexer(const xparam_antlr::LexerSharedInputState& state);
	xparam_antlr::RefToken nextToken();
	protected: void mWS(bool _createToken);
	public: void mMAIN_SWITCH(bool _createToken);
	protected: void mRESERVED_SYMBOL(bool _createToken);
	protected: void mCOMMENT(bool _createToken);
	protected: void mID(bool _createToken);
	protected: void mTYPENAME(bool _createToken);
	protected: void mFILENAME(bool _createToken);
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
};

ANTLR_END_NAMESPACE
#endif /*INC_DynamicLoaderLexer_hpp_*/
