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

#pragma warning (disable: 4786)

/*
* implementation of xParamLexer's added private methods (those not defined 
* by ANTLR).
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <assert.h>
#include "antlr/InputBuffer.hpp"
#include "../src_include/xParamLexer.hpp"
#include "../xparam/xp_error.h"
#include "../xparam/xp_raw_bytes.h"

using namespace xparam_antlr;
using namespace std;

namespace xParam_internal {
	
	//-------------------------------------------------------------------
	// METHOD: m_read_raw_bytes
	// DESCRIPTION: Builds a RawBytes object according to the data read
	//              from the lexer's input-buffer.
	//
	// FORMAT: the format consists of the following fields:
	//         1) the fixed bytes in RAW_header
	//         2) 4 bytes which encode size in big endian format (signed 32 bits).
	//         3) the actual data bytes
	//         4) the fixed bytes in RAW_trailer - 3 bytes for error checking
	// The first field should have been read by ANTLR before we reach here, so
	// we start parsing from the second field (the size).
	//------------------------------------------------------------------- 
	Handle<ParsedValue> xParamLexer::m_read_raw_bytes()
	{
		const char RAW_trailer[] = ">>>";

		InputBuffer& in_buf = getInputBuffer(); 
		long i;
		int c;
		
		// reconstruct size from first 4 bytes
		assert(sizeof(long) >= 4);
		long size = 0L;
		for (i=0; i<4; ++i) {
			c = in_buf.getChar();
			if ((c & 0xFF) != c)
				throw Error("error while reading RawBytes size");
			size = (size << 8) | c;
		}
		if (size < 0)
			throw Error("Got Negative length while reading RawBytes");
		
		// create RawBytes object with given size
		Handle<RawBytes> raw_bytes(new RawBytes(size));
		RawBytes& rb = *raw_bytes;
		
		// fill rb with bytes from input
		for (i=0; i<size; i++) {
			c = in_buf.getChar();
			if ((c & 0xFF) != c)
				throw Error("error while reading RawBytes body");
			rb[i] = (unsigned char) c;
		}
		
		// read and check trailer
		int n_trailer = strlen(RAW_trailer);
		for (i=0; i<n_trailer; i++) {
			c = in_buf.getChar();
			if ((c & 0xFF) != c)
				throw Error("error while reading RawBytes trailer");
			if (c != RAW_trailer[i])
				throw Error("Illegal trailer while reading RawBytes");
		}

		return Handle<ParsedValue>(new ParsedRawBytesValue(raw_bytes));
	} 
	
	
} // namespace xParam_internal
