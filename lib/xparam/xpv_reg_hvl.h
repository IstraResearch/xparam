#ifndef XPARAM_REG_HVL_H
#define XPARAM_REG_HVL_H

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
 * Defines the user's API for registering an HVL
 */

#include <iosfwd>
#include <utility>
#include <memory>
#include "xp_config.h"
#include "xpv_scheduler.h"
#include "xpv_common_regcom.h"
#include "xpv_registry.h"
#include "xpv_type.h"
#include "xpv_convweight.h"
#include "xpv_hvl_registry.h"
#include "xpv_hvl_creator_imp.h"

namespace xParam_internal {

	/////////////////////////////////////
	// HVL Output Function
	/////////////////////////////////////

	template<class T>
		class HVL_output {
		public:
			static void output(std::ostream& os, const HVL<T>& hvl) 
			{
				os << "[";

				typename HVL<T>::const_iterator i;
				for (i=hvl.begin(); i!=hvl.end(); ++i) {
					if (i!=hvl.begin())
						os << ',';
					
					Handle<Value> val = make_value(*i);
					val->output(os);
				}

				os << "]";
			}
	};

	/////////////////////////////////////
	// RegistrationCommand
	/////////////////////////////////////

	template<class T>
	class HVLClassRegCommand : public ClassRegCommand< HVL<T> > {
		public:
			HVLClassRegCommand() 
				: ClassRegCommand< HVL<T> >(typeid(T)) {}

			virtual std::string type_name() const {
				return "xParam::HVL<"
						+ xparam_or_cpp_name(typeid(T)) 
						+ ">";
			}
	};

	
	template<class T>
	class HVLRegCommand : public CommonRegCommand {
		public:
			HVLRegCommand() : CommonRegCommand(typeid(T)) {}

			virtual void do_registration() const 
			{
				// register HVL Creator
				Handle<HVLCreator> creator(new TypedHVLCreator<T>);
				hvl_registry().reg_creator(creator);

				// register class
				param_class< HVL<T> >(new HVLClassRegCommand<T>());

				// register ctor from ValueList 
				typedef GeneralHVLCreator<T> Creator;
				param_explicit_creator(TypeTag< HVL<T> >(),
										TypeTag<Creator>(),
										ConstRef<ValueList>("list"));

				// register special conversion source
				TypeRegistry& registry = type_registry_registration_access();
				assert(registry.is_registered(typeid(HVL<T>)));
				Type& hvl_type = registry.type(typeid(HVL<T>));

				ScalarConvWeight w(typeid(T)); // list weight
				hvl_type.reg_conversion_source(typeid(ValueList),w);

				// register output
				param_direct_output< HVL<T>, HVL_output<T> >();
			}

			virtual std::string description() const {
				return "HVL for type " + xparam_or_cpp_name(typeid(T));
			}
	};


	/////////////////////////////////////
	// registration API (used by vector,list,map)
	/////////////////////////////////////

	template<class T>	
		class register_hvl {
		public:
			register_hvl()
			{
				Handle<RegistrationCommand> command(new HVLRegCommand<T>);
				registration_scheduler().add_command(command);
			}
		};

} // namespace xParam_internal

#endif // XPARAM_REG_HVL_H
