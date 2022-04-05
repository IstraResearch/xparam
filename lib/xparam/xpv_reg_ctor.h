#ifndef XPARAM_REG_CTOR_H
#define XPARAM_REG_CTOR_H

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
 * Defines the user's API for registering a constructor for a class
 */

#include <typeinfo>
#include "xp_config.h"
#include "xp_handle.h"
#include "xpv_ctor.h"
#include "xpv_common_regcom.h"
#include "xpv_type.h"
#include "xpv_registry.h"

namespace xParam_internal {

	class CtorRegCommand : public CommonRegCommand {
		public:
			CtorRegCommand(Handle<Ctor> ctor) 
				: CommonRegCommand(get_deps_from(ctor)), m_ctor(ctor) {}
			
			virtual void do_registration() const {
				Type& t = type_registry_registration_access().type(m_ctor->constructed_type());
				t.reg_ctor(m_ctor);
			}

			virtual std::string description() const { 
				return std::string("Constructor for ") + m_ctor->constructed_type().name();
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
	};

} // namespace xParam_internal

#include "xpv_reg_ctor_imp.h"
#include "xpv_arg_passers.h"

#endif // XPARAM_REG_CTOR_H
