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

#include "../xparam/xparam_extend.h"
#include "../src_include/xpv_link_patch.h"

#ifdef XPARAM_STATIC_LIB
namespace xParam_internal {
void link_in_regtype_short() {}
}
#endif

using namespace xParam;

class short_output_functor {
  public:
    static ValueList sub_objects(short s) {
      ValueList vl;
      return vl << Val( static_cast<int>(s) );
    }
};

PARAM_BEGIN_REG

  PARAM_CLASS(short);
  param_explicit_ctor(TypeTag<short>(),AsConvertedVal<char,short>("c"));
  param_weighted_ctor(TypeTag<short>(),AsConvertedVal<unsigned char,short>("uc"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<short>(),AsConvertedVal<unsigned short,short>("us"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<short>(),AsConvertedVal<int,short>("i"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<short>(),AsConvertedVal<unsigned int,short>("ui"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<short>(),AsConvertedVal<long,short>("l"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<short>(),AsConvertedVal<unsigned long,short>("ul"),CONV_STANDARD);

#ifndef NO_LONG_LONG
  param_weighted_ctor(TypeTag<short>(),AsConvertedVal<long long,short>("ll"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<short>(),AsConvertedVal<unsigned long long,short>("ull"),CONV_STANDARD);
#endif

  param_weighted_ctor(TypeTag<short>(),AsConvertedVal<double,short>("d"),CONV_STANDARD);

#ifndef NO_LONG_DOUBLE
  param_weighted_ctor(TypeTag<short>(),AsConvertedVal<long double,short>("ld"),CONV_STANDARD);
#endif

  param_weighted_ctor(TypeTag<short>(),AsConvertedVal<float,short>("f"),CONV_STANDARD);
  param_output<short, short_output_functor>();

  param_vector<short>();

PARAM_END_REG
