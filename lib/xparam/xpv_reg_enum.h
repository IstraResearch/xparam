#ifndef XPARAM_REG_ENUM_H
#define XPARAM_REG_ENUM_H

/*      Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand
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
 * Defines the user's API for registering an enum
 */

#include <string>
#include <typeinfo>
#include "xparam_extend.h"
#include "xpv_enum_registry.h"
#include "xpv_registry.h"

namespace xParam_internal {
	
	template<class T>
	class enum_output_functor {
	public:
	  static void output(std::ostream& os, T t) {
		  if (enum_registry(TypeTag<T>()).is_registered(t)) {
			  os << (enum_registry(TypeTag<T>()).name(t));
		  } else {
			  os << (type_registry().type(typeid(T)).name());
			  os << '(' << ((int)t) << ')';
		  }
	  }
	};
	
	template<class T>
		class EnumTypeRegCommand : public CommonRegCommand {
		public:
			EnumTypeRegCommand(const std::string& name) 
				: CommonRegCommand(), 
				m_name(name) 
			{}
			
			virtual void do_registration() const {
				param_class<T> temp(m_name);
				TemplateFooler::launder((void*)&temp);
				param_ctor(TypeTag<T>());
				param_explicit_ctor(TypeTag<T>(), ByVal<int>("i"));
				param_conversion_operator(SourceTag<T>(), 
					                      TargetTag<int>(), CONV_STANDARD);
				param_direct_output<T,enum_output_functor<T> >();
			}
			
			virtual std::string description() const {
				return "Enum Type \"" + m_name + '"';
			}
			
		private:
			std::string m_name;
	};
	
	template<class T>
	void param_enum(TypeTag<T>, const std::string& name) {
		Handle<RegistrationCommand> command(new EnumTypeRegCommand<T>(name));
		registration_scheduler().add_command(command);
	}
	
#define PARAM_ENUM(T) param_enum(TypeTag<T>(),#T)
	
#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS	
	template<class T>
	T* param_enum(const std::string& name) {
		param_enum(TypeTag<T>(),name);
		return 0;
	}
#endif

	template<class T>
		class EnumValRegCommand : public CommonRegCommand {
		public:
			EnumValRegCommand(const std::string& name, const T& t) 
				: CommonRegCommand(), 
				m_name(name),
				m_val(t)
			{}
			
			virtual void do_registration() const {
				param_const(m_name,m_val);
				enum_registry(TypeTag<T>()).register_enum(m_name,m_val);
			}
			
			virtual std::string description() const {
				return "Enum value \"" + m_name + '"';
			}
			
		private:
			std::string m_name;
			T m_val;
	};
	
	template<class T>
	void param_enum_val(const std::string& name, const T& t) {
		Handle<RegistrationCommand> command(new EnumValRegCommand<T>(name,t));
		registration_scheduler().add_command(command);
	}

#define PARAM_ENUM_VAL(T) param_enum_val(#T,T);
	
}

#endif // XPARAM_REG_ENUM_H
