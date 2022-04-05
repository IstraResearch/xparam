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

#include <iostream>
#include <string.h>
#include "../xparam/xparam_extend.h"
#include "../xparam/xp_raw_bytes.h"
#include "../src_include/xpv_link_patch.h"

#ifdef XPARAM_STATIC_LIB
namespace xParam_internal {
void link_in_regtype_raw_bytes() {}
}
#endif

using namespace xParam;
using namespace std;

namespace {
	class RawBytesOutput {
	public:
		//-------------------------------------------------------------------
		// FUNCTION: print_raw_bytes
		// DESCRIPTION: Writes the RawBytes object to 'os' in machine readable format.
		//
		// FORMAT: the format consists of the following fields:
		//         1) the fixed bytes in RAW_header
		//         2) 4 bytes which encode size in big endian format (signed 32 bits).
		//         3) the actual data bytes
		//         4) the fixed bytes in Raw_trailer - 3 bytes for error checking
		//-------------------------------------------------------------------
		static void output(ostream& os, const RawBytes& raw_bytes) {
			const char RAW_header[] = "raw<<<"; 
			const char RAW_trailer[] = ">>>";
			
			string write_err_msg = "Error while writing RawBytes to ostream";
			
			// write header
			os.write(RAW_header,strlen(RAW_header));
			if (!os)
				throw Error(write_err_msg);
			
			// write length
			long size = raw_bytes.size();  
			assert(size >= 0);
			assert((size >> 24) < (1L<<8)); // make sure we don't have more than 32 bits
			for (int i=0; i<4; ++i) {
				char c = (size >> (8*(3-i))) & 0xFF;
				os.put(c);
				if (!os)
					throw Error(write_err_msg);
			}
			
			// write actual data
			for (RawBytes::const_iterator j=raw_bytes.begin(); j!=raw_bytes.end(); ++j) {
				char c = (char) *j;
				os.put(c);
			}
			if (!os)
				throw Error(write_err_msg);  
			
			// write trailer
			os.write(RAW_trailer,strlen(RAW_trailer));
			if (!os)
				throw Error(write_err_msg);
		}
	};
}

PARAM_BEGIN_REG
  // no ctor registration - ctor is only invoked directly by parser
  param_class<RawBytes>("RawBytes");
  param_direct_output<RawBytes,RawBytesOutput>();
  param_conversion_operator(SourceTag<RawBytes>(), TargetTag< vector<unsigned char> >());
PARAM_END_REG

