#ifndef XPARAM_REG_CONVERSION_H
#define XPARAM_REG_CONVERSION_H

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
 * Defines the user's API for registering a conversion
 */

#include <typeinfo>
#include <assert.h>
#include "xp_config.h"
#include "xpv_convweight.h"
#include "xpv_scheduler.h"
#include "xpv_common_regcom.h"
#include "xpv_ctor_imp.h"
#include "xpv_type.h"
#include "xpv_registry.h"
#include "xpv_arg_passers.h"


namespace xParam_internal {

///////////////////////////////////////////////////////////////
// ConversionRegCommand
///////////////////////////////////////////////////////////////

	class ConversionRegCommand : public CommonRegCommand {
		public:
			ConversionRegCommand(Handle<Ctor> ctor, const ScalarConvWeight& w) 
				: CommonRegCommand(get_deps_from(ctor)), m_ctor(ctor), m_weight(w) {}
			
			virtual void do_registration() const {
				Type& t = type_registry_registration_access().type(m_ctor->constructed_type());
				t.reg_ctor(m_ctor);
				assert(m_ctor->n_args() == 1);
				const std::type_info& source_type = (m_ctor->arg_defs())[0].type();
				t.reg_conversion_source(source_type,m_weight);
			}
			
			virtual std::string description() const { 
				assert(m_ctor->n_args() == 1);
				const std::type_info& source = (m_ctor->arg_defs())[0].type();
				const std::type_info& target = m_ctor->constructed_type();
				return std::string("Conversion from ") + source.name() + " to "
					+ target.name();
			}

		private:
			static std::vector<const std::type_info*>
				get_deps_from(const Handle<Ctor>& ctor) 
			{
				std::vector<const std::type_info*> deps = ctor->arg_types();
				deps.push_back(&ctor->constructed_type());
				return deps;
			}

			Handle<Ctor> m_ctor;
			ScalarConvWeight m_weight;
	};


///////////////////////////////////////////////////////////////
// param_weighted_creator
///////////////////////////////////////////////////////////////

	template<class T, class Creator, class ArgPasser> 
		void param_weighted_creator(TypeTag<T>, TypeTag<Creator>, 
									const ArgPasser& arg, ScalarConvWeight w)
		{
			std::vector<ArgDef> arg_defs(1,arg);
			Handle<Ctor> ctor(new TypedCtor_1<T,Creator,ArgPasser>(arg_defs));
			Handle<RegistrationCommand> command(new ConversionRegCommand(ctor,w));
			registration_scheduler().add_command(command);
		}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	// Return something to do with template paramters that don't appear in argument
	// to overcome VC++6 name mangling bug.
	template<class T, class Creator, class ArgPasser> 
		std::pair<T*,Creator*> param_weighted_creator(const ArgPasser& arg, ScalarConvWeight w)
		{
			param_weighted_creator(TypeTag<T>(), TypeTag<Creator>(), arg, w);
			return std::pair<T*,Creator*>();
		}
#endif


///////////////////////////////////////////////////////////////
// param_creator
///////////////////////////////////////////////////////////////

	template<class T, class Creator, class ArgPasser>
	void param_creator(TypeTag<T>, TypeTag<Creator>, const ArgPasser& arg) {
		param_weighted_creator(TypeTag<T>(), TypeTag<Creator>(), arg, CONV_USER);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class T, class Creator, class ArgPasser>
	std::pair<T*,Creator*> param_creator(const ArgPasser& arg) {
		param_creator(TypeTag<T>(), TypeTag<Creator>(), arg);
		return std::pair<T*,Creator*>();
	}
#endif

///////////////////////////////////////////////////////////////
// param_weighted_ctor
///////////////////////////////////////////////////////////////

	template<class T, class ArgPasser> 
		void param_weighted_ctor(TypeTag<T>, const ArgPasser& arg, ScalarConvWeight w)
		{
			typedef typename ArgPasser::passed_type PassedType;
			typedef CreateWithNew_1<T,PassedType> Creator;
			param_weighted_creator(TypeTag<T>(), TypeTag<Creator>(), arg,w);
		}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class T, class ArgPasser> 
		T* param_weighted_ctor(const ArgPasser& arg, ScalarConvWeight w)
		{
			param_weighted_ctor(TypeTag<T>(), arg, w);
			return 0;
		}
#endif


///////////////////////////////////////////////////////////////
// param_ctor
///////////////////////////////////////////////////////////////

	template<class T,class ArgPasser>
	void param_ctor(TypeTag<T>, const ArgPasser& arg) {
		param_weighted_ctor(TypeTag<T>(),arg,CONV_USER);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class T,class ArgPasser>
	T* param_ctor(const ArgPasser& arg) {
		param_ctor(TypeTag<T>(), arg);
		return 0;
	}
#endif

///////////////////////////////////////////////////////////////
// param_conversion_operator
///////////////////////////////////////////////////////////////

	template<class T> class SourceTag {};
	template<class T> class TargetTag {};

	template<class Source, class Target>	
		void param_conversion_operator(SourceTag<Source>, TargetTag<Target>, 
										ScalarConvWeight w = CONV_USER) 
		{
			param_weighted_ctor(TypeTag<Target>(), AsConvertedVal<Source, Target>("src"), w);
		}

} // namespace xParam_internal

#endif // XPARAM_REG_CONVERSION_H
