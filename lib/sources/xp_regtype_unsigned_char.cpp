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
#include "../xparam/xparam_extend.h"
#include "../src_include/xp_regtype_char_body_output.h"
#include "../src_include/xpv_link_patch.h"

#ifdef XPARAM_STATIC_LIB
namespace xParam_internal {
void link_in_regtype_uchar() {}
}
#endif

using namespace xParam;

class unsigned_char_output_functor {
  public:
    static ValueList sub_objects(unsigned char c) {
      ValueList vl;
      return vl << Val( static_cast<char>(c) );
    }
};

PARAM_BEGIN_REG

  param_class<unsigned char>("uchar");
  param_weighted_ctor(TypeTag<unsigned char>(),AsConvertedVal<bool,unsigned char>("b"),CONV_STANDARD);
  param_explicit_ctor(TypeTag<unsigned char>(),AsConvertedVal<char,unsigned char>("c"));
  param_weighted_ctor(TypeTag<unsigned char>(),AsConvertedVal<short,unsigned char>("s"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<unsigned char>(),AsConvertedVal<unsigned short,unsigned char>("us"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<unsigned char>(),AsConvertedVal<int,unsigned char>("i"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<unsigned char>(),AsConvertedVal<unsigned int,unsigned char>("ui"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<unsigned char>(),AsConvertedVal<long,unsigned char>("l"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<unsigned char>(),AsConvertedVal<unsigned long,unsigned char>("ul"),CONV_STANDARD);

#ifndef NO_LONG_LONG
  param_weighted_ctor(TypeTag<unsigned char>(),AsConvertedVal<long long,unsigned char>("ll"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<unsigned char>(),AsConvertedVal<unsigned long long,unsigned char>("ull"),CONV_STANDARD);
#endif

  param_weighted_ctor(TypeTag<unsigned char>(),AsConvertedVal<double,unsigned char>("d"),CONV_STANDARD);

#ifndef NO_LONG_DOUBLE
  param_weighted_ctor(TypeTag<unsigned char>(),AsConvertedVal<long double,unsigned char>("ld"),CONV_STANDARD);
#endif

  param_weighted_ctor(TypeTag<unsigned char>(),AsConvertedVal<float,unsigned char>("f"),CONV_STANDARD);
  param_output<unsigned char,unsigned_char_output_functor>();

  param_vector<unsigned char>();

PARAM_END_REG
