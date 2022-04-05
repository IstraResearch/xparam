#ifndef XPARAM_REG_INHERITANCE_H
#define XPARAM_REG_INHERITANCE_H

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
 * Defines the user's API for registering an inheritance relationship between 
 * two classes.
 */

#include "xp_config.h"
#include "xp_handle.h"
#include "xpv_scheduler.h"
#include "xpv_common_regcom.h"
#include "xpv_type.h"
#include "xpv_iconv_imp.h"
#include "xpv_ctor.h"
#include "xpv_registry.h"

namespace xParam_internal {

	class InheritanceRegCommand : public CommonRegCommand {
	public:
		InheritanceRegCommand(Handle<Ctor> ctor, Handle<IConv> iconv) 
			: CommonRegCommand(iconv->ancestor(), iconv->descendant()), 
				m_ctor(ctor), m_iconv(iconv) {}
			
		virtual void do_registration() const {
			TypeRegistry& registry = type_registry_registration_access();

			Type& parent_type = registry.type(m_iconv->ancestor());
			parent_type.reg_ctor(m_ctor);
			parent_type.reg_conversion_source(m_iconv->descendant(),
												CONV_TO_PARENT);

			Type& derived_type = registry.type(m_iconv->descendant());
			derived_type.reg_iconv(m_iconv);
		}
			
		virtual std::string description() const { 
			return std::string("Inheritance relationship between ") 
				+ m_iconv->descendant().name() + " and its base class " 
				+ m_iconv->ancestor().name();
		}

	private:
		Handle<Ctor> m_ctor;
		Handle<IConv> m_iconv;
	};


	template<class Derived,class Base>
	class InheritanceCtor : public Ctor {
	public:
		InheritanceCtor() 
			: Ctor(typeid(Base), std::vector<ArgDef>(1,ArgDef(typeid(Derived),"derived"))) 
		{}

	protected:
		virtual Handle<Value> actual_create(const ValueList& args) const {
			assert(args.size() == 1);
			Handle<Derived> derived = extract(*args[0],TypeTag<Derived>());
			Handle<Base> base = handle_upcast(derived,TypeTag<Base>());
			return make_value(base);
		}
	};

	template<class T> class DerivedTag {};
	template<class T> class BaseTag {};

	template<class Derived, class Base>	
		void param_inheritance(DerivedTag<Derived>, BaseTag<Base>)
			{
				Handle<Ctor> ctor(new InheritanceCtor<Derived,Base>);
				Handle<IConv> iconv(new DirectIConv<Base,Derived>);
				Handle<RegistrationCommand> command(new InheritanceRegCommand(ctor,iconv));
				registration_scheduler().add_command(command);
			}

} // namespace xParam_internal

#endif // XPARAM_REG_INHERITANCE_H
