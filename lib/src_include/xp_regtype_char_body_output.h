#ifndef __XP_CHAR_BODY_OUTPUT__
#define __XP_CHAR_BODY_OUTPUT__

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

#include <assert.h>
#include<iostream>
#include "../xparam/xp_config.h"

class CharBodyOutput {
  public:
	// is_string tells the routine whether it should assume the 
	// output is inside single or double quotes, since these 
	// quotes need to be protected by preceding them with a backslash.
    static void output(std::ostream& os, char c, bool is_string) {
		switch (c) {
			case '\n': os << "\\n"; return;
			case '\t': os << "\\t"; return;
			case '\v': os << "\\v"; return;
			case '\b': os << "\\b"; return;
			case '\r': os << "\\r"; return;
			case '\f': os << "\\f"; return;
			case '\a': os << "\\a"; return;
			case '\\': os << "\\\\"; return;
			case '\'': os << (is_string ? "'" : "\\'"); return;
			case '"' : os << (is_string ? "\\\"" : "\""); return;
		}

		if (isprint(c)) {
			os << c;
			return;
		}

		// 2 digit hex encoding
		int high_digit = (c>>4) & 0xF;
		int low_digit = c & 0xF;
		os << "\\x" << encode_hex(high_digit) << encode_hex(low_digit);
    }

  private:
	  static char encode_hex(int digit) {
		  assert(digit>=0 && digit<16);
		  if (digit<10)
			  return '0' + digit;
		  else
			  return 'A' + digit - 10;
	  }
};

#endif // __XP_CHAR_BODY_OUTPUT__
