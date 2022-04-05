#ifndef XPARAM_REG_PAIR_H
#define XPARAM_REG_PAIR_H

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

/*
 * Defines the user's API for registering std::pairs
 */

#include <iosfwd>
#include <utility>

#include "xp_config.h"
#include "xp_value_list.h"
#include "xpv_arg_passers.h"
#include "xpv_scheduler.h"
#include "xpv_common_regcom.h"
#include "xpv_registry.h"
#include "xpv_type.h"
#include "xpv_convweight.h"

#include "xpv_reg_class.h"
#include "xpv_reg_ctor.h"
#include "xpv_reg_output.h"
#include "xpv_reg_conversion.h"


namespace xParam_internal {


	/////////////////////////////////////
	// Output Function
	/////////////////////////////////////

	template<class X, class Y>
		class PairOutput {
		public:
			static ValueList sub_objects(const std::pair<X,Y>& pair) 
			{
				ValueList vl;
				return vl << Val(pair.first) << Val(pair.second);
			}
	};


	/////////////////////////////////////
	// RegistrationCommand
	/////////////////////////////////////

	template<class X, class Y>
	class PairRegCommand : public ClassRegCommand< std::pair<X,Y> > {
		public:
			PairRegCommand() 
				: ClassRegCommand< std::pair<X,Y> >(typeid(X),typeid(Y)) {}

			virtual std::string type_name() const {
				return "pair<" 
						+ xparam_or_cpp_name(typeid(X)) 
						+ "," 
						+ xparam_or_cpp_name(typeid(Y)) 
						+ ">";
			}
	};


	/////////////////////////////////////
	// User registration API
	/////////////////////////////////////

	template<class X, class Y>	
		class param_pair {
		public:
			typedef std::pair<X,Y> Pair;

			param_pair()
			{
				// register class
				param_class<Pair>(new PairRegCommand<X,Y>());

				// register ctor from two values
				param_ctor(TypeTag<Pair>(), ByVal<X>("first"), ByVal<Y>("second"));

				// register output
				param_output< Pair, PairOutput<X,Y> >();
			}
		};

} // namespace xParam_internal

#endif // XPARAM_REG_PAIR_H
