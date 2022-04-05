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
void link_in_regtype_ulong() {}
}
#endif

using namespace xParam;

class ulong_output_functor {
  public:
    static void output(std::ostream& os, unsigned long ul) {
      os << ul << "UL";
    }
};

PARAM_BEGIN_REG

  param_class<unsigned long>("ulong");
  param_weighted_ctor(TypeTag<unsigned long>(),AsConvertedVal<unsigned char,unsigned long>("uc"),CONV_STANDARD);
  param_explicit_ctor(TypeTag<unsigned long>(),AsConvertedVal<char,unsigned long>("c"));
  param_weighted_ctor(TypeTag<unsigned long>(),AsConvertedVal<unsigned short,unsigned long>("us"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<unsigned long>(),AsConvertedVal<short,unsigned long>("s"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<unsigned long>(),AsConvertedVal<unsigned int,unsigned long>("ui"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<unsigned long>(),AsConvertedVal<int,unsigned long>("i"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<unsigned long>(),AsConvertedVal<long,unsigned long>("l"),CONV_STANDARD);

#ifndef NO_LONG_LONG
  param_weighted_ctor(TypeTag<unsigned long>(),AsConvertedVal<unsigned long long,unsigned long>("ull"),CONV_STANDARD);
  param_weighted_ctor(TypeTag<unsigned long>(),AsConvertedVal<long long,unsigned long>("ll"),CONV_STANDARD);
#endif

  param_weighted_ctor(TypeTag<unsigned long>(),AsConvertedVal<double,unsigned long>("d"),CONV_STANDARD);

#ifndef NO_LONG_DOUBLE
  param_weighted_ctor(TypeTag<unsigned long>(),AsConvertedVal<long double,unsigned long>("ld"),CONV_STANDARD);
#endif

  param_weighted_ctor(TypeTag<unsigned long>(),AsConvertedVal<float,unsigned long>("f"),CONV_STANDARD);
  param_direct_output<unsigned long,ulong_output_functor>();

  param_vector<unsigned long>();

PARAM_END_REG
