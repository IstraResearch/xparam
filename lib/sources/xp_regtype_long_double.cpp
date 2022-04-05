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

#include <algorithm>

#ifndef NO_LIMITS
#include <limits>
#endif

#include "../xparam/xparam_extend.h"
#include "../src_include/xp_sstream.h"
#include "../src_include/xp_regtype_real_output.h"
#include "../src_include/xpv_link_patch.h"

#ifdef XPARAM_STATIC_LIB
namespace xParam_internal {
void link_in_regtype_long_double() {}
}
#endif

using namespace xParam;
using namespace std;

#ifndef NO_LONG_DOUBLE

typedef long double long_double_type;

class long_double_output_functor {
  public:
    static void output(ostream& os, long_double_type d) {
		xParam_internal::output_real_number(os,d);
		os << "L";
    }
};

PARAM_BEGIN_REG

  param_class<long_double_type>("long_double");
  param_explicit_ctor(TypeTag<long_double_type>(),AsConvertedVal<char,long_double_type>("c"));
  param_weighted_ctor(TypeTag<long_double_type>(),AsConvertedVal<unsigned char,long_double_type>("uc"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<long_double_type>(),AsConvertedVal<short,long_double_type>("s"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<long_double_type>(),AsConvertedVal<unsigned short,long_double_type>("us"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<long_double_type>(),AsConvertedVal<int,long_double_type>("i"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<long_double_type>(),AsConvertedVal<unsigned int,long_double_type>("ui"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<long_double_type>(),AsConvertedVal<long,long_double_type>("l"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<long_double_type>(),AsConvertedVal<unsigned long,long_double_type>("ul"),CONV_STANDARD);

#ifndef NO_LONG_LONG
  param_weighted_ctor(TypeTag<long_double_type>(),AsConvertedVal<long long,long_double_type>("ll"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<long_double_type>(),AsConvertedVal<unsigned long long,long_double_type>("ull"),CONV_STANDARD);
#endif

  param_weighted_ctor(TypeTag<long_double_type>(),AsConvertedVal<float,long_double_type>("f"),CONV_PROMOTION);
  param_weighted_ctor(TypeTag<long_double_type>(),AsConvertedVal<double,long_double_type>("d"),CONV_PROMOTION);
  param_direct_output<long_double_type,long_double_output_functor>();

#ifdef NO_LIMITS
  double a=0.0;
  param_const("NaNL",((long double)(a/a)));
#else
  param_const("NaNL",numeric_limits<long double>::quiet_NaN());
#endif

  param_vector<long_double_type>();

PARAM_END_REG

#endif 
