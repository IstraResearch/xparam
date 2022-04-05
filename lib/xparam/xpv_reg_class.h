#ifndef XPARAM_REG_CLASS_H
#define XPARAM_REG_CLASS_H

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
 * Defines the user's API for registering a class
 */

#include <typeinfo>
#include <string>
#include "xp_config.h"
#include "xp_handle.h"
#include "xpv_facade_imp.h"
#include "xpv_type.h"
#include "xpv_registry.h"
#include "xpv_copier_imp.h"
#include "xpv_dtor_imp.h"
#include "xpv_reg_conversion.h"
#include "xpv_reg_ctor_imp.h"
#include "xpv_template_fooler.h"
#include "xpv_untyped_null.h"


namespace xParam_internal {

	template<class T> void instantiate_value_manipulation(TypeTag<T>)
	{
		if (TemplateFooler::always_false()) {
			TemplateFooler::assert_false();
			
			Handle<T> t;
			Handle<Value> val = make_value(t);
			const T& t_ref = *t;
			val = make_value_copy(t_ref);
			val = make_value_copy_ptr(&t_ref);
			extract(*val,TypeTag<T>());
			get_owned_copy(*val,TypeTag<T>());
			get_copy_of(t_ref);
		}
	}

	template<class T>
	class NullCreator {
		public:
			static T* create(UntypedNull null) { return 0; }
	};

	inline void register_class(const std::type_info& ti, 
								const std::string& name, 
								bool is_abstract,
								const Handle<Copier>& copier,
								const Handle<Dtor>& dtor)
	{
		Handle<Type> type(new Type(ti,name,is_abstract));
		type->reg_copier(copier);
		type->reg_dtor(dtor);
		type_registry_registration_access().register_type(type);
	}

	template<class T> 
		void typed_register_class(TypeTag<T>, 
									const std::string& name, 
									bool is_abstract,
									const Handle<Copier>& copier,
									const Handle<Dtor>& dtor)
		{
			register_class(typeid(T),name,is_abstract,copier,dtor);

			if (typeid(T) != typeid(UntypedNull)) {  
				// the if saves a few loops when searching for conversions

				param_weighted_creator(TypeTag<T>(), TypeTag< NullCreator<T> >(), 
														ByVal<UntypedNull>("null"), 
														CONV_STANDARD);
			}

			instantiate_value_manipulation(TypeTag<T>());
		}


	/////////////////////////////////////
	// ClassKinds
	/////////////////////////////////////

	template<class T>
	class ConcreteClassKind {
	public:
		static std::string kind_name() {
			return "Type";
		}

		static bool is_abstract() { return false; }

		static Handle<Copier> get_copier() {
			return Handle<Copier>(new CopyCtorCopier<T>());
		}

		static Handle<Dtor> get_dtor() {
			return Handle<Dtor>(new TypedDtor<T>());
		}

		static void do_more_registration() {
			// register copy-ctor
			param_explicit_ctor(TypeTag<T>(),ByVal<T>("other"));
		}
	};

	template<class T>
	class AbstractClassKind {
	public:
		static std::string kind_name() {
			return "Abstract Type";
		}

		static bool is_abstract() { return true; }

		static Handle<Copier> get_copier() {
			return Handle<Copier>(new ErrorCopier(typeid(T)));
		}

		static Handle<Dtor> get_dtor() {
			return Handle<Dtor>(new ErrorDtor(typeid(T)));
		}

		static void do_more_registration() {}
	};


	/////////////////////////////////////
	// RegistrationCommand
	/////////////////////////////////////

	template<class T, class ClassKind = ConcreteClassKind<T> >
		class ClassRegCommand : public CommonRegCommand {
		public:
			ClassRegCommand(const std::string& name) 
				: CommonRegCommand(), m_name(name) {}

			ClassRegCommand(const DependencyVector& deps = DependencyVector()) 
				: CommonRegCommand(deps) {}

			ClassRegCommand(const std::type_info& dep) 
				: CommonRegCommand(dep) {}

			ClassRegCommand(const std::type_info& dep1, const std::type_info& dep2)
				: CommonRegCommand(dep1,dep2) {}

			virtual std::string type_name() const {
				return m_name.empty() ? "NO_NAME_GIVEN" : m_name;
			}
			  
			virtual void do_registration() const {
				Handle<Copier> copier = ClassKind::get_copier();
				Handle<Dtor> dtor = ClassKind::get_dtor();
				bool is_abstract = ClassKind::is_abstract();
				typed_register_class(TypeTag<T>(), type_name(), is_abstract, copier, dtor);
				ClassKind::do_more_registration();
			}
			
			virtual std::string description() const {
				return ClassKind::kind_name() + " \"" + type_name() + '"';
			}
			
		private:
			std::string m_name;
	};

	/////////////////////////////////////
	// User registration API
	/////////////////////////////////////

	template<class T>
		class param_class {
			public:
				param_class(const std::string& name)
				{
					Handle<RegistrationCommand> command(new ClassRegCommand<T>(name));
					registration_scheduler().add_command(command);
				}

				param_class(ClassRegCommand<T>* cmd_ptr) 
				{
					Handle<RegistrationCommand> command(cmd_ptr);
					registration_scheduler().add_command(command);
				}
		};


#define PARAM_CLASS(T) param_class<T>(#T)

	template<class T>	
		class param_abstract_class {
			public: 
				typedef ClassRegCommand<T,AbstractClassKind<T> > CommandType;

				param_abstract_class(const std::string& name)
				{
					Handle<RegistrationCommand> command(new CommandType(name));
					registration_scheduler().add_command(command);
				}

				param_abstract_class(CommandType* cmd_ptr) 
				{
					Handle<RegistrationCommand> command(cmd_ptr);
					registration_scheduler().add_command(command);
				}
		};

#define PARAM_ABSTRACT_CLASS(T) param_abstract_class<T>(#T)

} // namespace xParam_internal

#endif // XPARAM_REG_CLASS_H
