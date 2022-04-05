#ifndef XPARAM_REG_TYPED_TUPLE_H
#define XPARAM_REG_TYPED_TUPLE_H

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
 * Defines the user's API for registering a Typed_K_Tuple
 */

#include <typeinfo>
#include <iosfwd>
#include <utility>
#include <memory>
#include "xp_config.h"
#include "xpv_scheduler.h"
#include "xpv_common_regcom.h"
#include "xpv_registry.h"
#include "xpv_type.h"
#include "xpv_convweight.h"
#include "xpv_typed_tuple_registry.h"
#include "xpv_typed_tuple_creator_imp.h"

namespace xParam_internal {

	/////////////////////////////////////
	// RegistrationCommand
	/////////////////////////////////////

	template<class T0,class T1>
	class Typed_2_TupleClassRegCommand : public ClassRegCommand< Typed_2_Tuple<T0,T1> > {
		public:
			typedef Typed_2_Tuple<T0,T1> TypedTuple;

			Typed_2_TupleClassRegCommand() 
				: ClassRegCommand< TypedTuple >(typeid(T0),typeid(T1)) 
			{}

			virtual std::string type_name() const {
				return "xParam::Typed_2_Tuple<"
						+ xparam_or_cpp_name(typeid(T0)) 
						+ ","
						+ xparam_or_cpp_name(typeid(T1)) 
						+ ">";
			}
	};

	
	template<class T0, class T1>
	class Typed_2_TupleRegCommand : public CommonRegCommand {
		public:
			typedef Typed_2_Tuple<T0,T1> TypedTuple;

			Typed_2_TupleRegCommand() : CommonRegCommand(typeid(T0),typeid(T1)) {}

			virtual void do_registration() const 
			{
				// register TypedTupleCreator
				Handle<TypedTupleCreator> creator(new Typed_2_TupleCreator<T0,T1>);
				typed_tuple_registry().reg_creator(creator);

				// register class
				param_class< TypedTuple >(new Typed_2_TupleClassRegCommand<T0,T1>());

				// register ctor from ValueTuple 
				typedef GeneralTyped_2_TupleCreator<T0,T1> Creator;
				param_explicit_creator(TypeTag<TypedTuple>(), 
										TypeTag<Creator>(),
										ConstRef<ValueTuple>("tuple"));

				// register special conversion source
				TypeRegistry& registry = type_registry_registration_access();
				assert(registry.is_registered(typeid(TypedTuple)));
				Type& typed_tuple_type = registry.type(typeid(TypedTuple));

				std::vector<const std::type_info*> member_types;
				member_types.push_back( &typeid(T0) );
				member_types.push_back( &typeid(T1) );
				ScalarConvWeight w(member_types); // tuple weight
				typed_tuple_type.reg_conversion_source(typeid(ValueTuple),w);
			}

			virtual std::string description() const {
				return "Typed_2_Tuple for types " 
						+ xparam_or_cpp_name(typeid(T0))
						+ " and " 
						+ xparam_or_cpp_name(typeid(T1));
			}
	};


	/////////////////////////////////////
	// registration API (used by vector,list,map)
	/////////////////////////////////////

	template<class T0, class T1>	
		class register_typed_2_tuple {
		public:
			register_typed_2_tuple()
			{
				Handle<RegistrationCommand> command(new Typed_2_TupleRegCommand<T0,T1>);
				registration_scheduler().add_command(command);
			}
		};

} // namespace xParam_internal

#endif // XPARAM_REG_TYPED_TUPLE_H
