#ifndef XPARAM_REG_CONST_H
#define XPARAM_REG_CONST_H

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
 * Defines the user's API for registering a constant.
 */

#include <string>
#include "xp_config.h"
#include "xp_value_management_facade.h"
#include "xpv_const_registry.h"
#include "xpv_scheduler.h"
#include "xpv_const.h"
#include "xp_value.h"
#include "xp_handle.h"

namespace xParam_internal {

	template<class T>
	class ConstantRegCommand : public CommonRegCommand {
		public:
			ConstantRegCommand(Handle<Constant<T> > c) : CommonRegCommand(c->type()), m_c(c) {}

			virtual void do_registration() const {
				Handle<Value> value=m_c->value();
				std::string name=m_c->name();
				const_registry().register_const(value,name);
				type_registry_registration_access().type(typeid(T)).reg_constant_name(name);
			}

			virtual std::string description() const {
				return std::string("Constant called \"" + m_c->name() + "\"");
			}

		private:
			Handle<Constant<T> > m_c;
	};

	template<class T>	
		void param_const(const std::string& name, const T& t) {
			Handle<Constant<T> > c(new Constant<T>(t,name));
			Handle<RegistrationCommand> command(new ConstantRegCommand<T>(c));
			registration_scheduler().add_command(command);
		}

#define PARAM_CONST(T) param_const(#T,T)

} // namespace xParam_internal

#endif // XPARAM_REG_CONST_H
