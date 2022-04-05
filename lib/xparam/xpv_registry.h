#ifndef XPARAM_REGISTRY_H
#define XPARAM_REGISTRY_H

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
 * provides a mapping from names or type_info to the corresponding Type object
 * (at any time there should only be one Type object for each registered C++ type)
 */

#include <typeinfo>
#include <string>
#include <map>
#include "xp_config.h"
#include "xp_singleton.h"
#include "xp_error.h"
#include "xp_handle.h"
#include "xp_type_compare.h"
#include "xpv_type.h"

namespace xParam_internal {

	class TypeRegistry {
		public:
			TypeRegistry();

			// registration
			void register_type(Handle<Type> new_type);

			// queries
			bool is_registered(const std::string& name) const throw();
			bool is_registered(const std::type_info& ti) const throw();

			Type& type(const std::string& name);
			Type& type(const std::type_info& ti);

		private:
			std::map<std::string, Handle<Type> > m_name_map;
			std::map<const std::type_info*, Handle<Type>, TypeInfoCmp> m_typeinfo_map;
	};

	// NOTE:
	// All access to the TypeRegistry singleton should be done using one of 
	// the following functions.
	// Registrators should use type_registry_registration_access(), and
	// other code (which wants to query the registry) should use 
	// type_registry().

	// access to the singleton without side-effects
	inline TypeRegistry& type_registry_registration_access() {
		return Singleton<TypeRegistry>::get(); 
	}

	// provideds access to the singleton, and also executes all pending 
	// registration commmands that have their dependencies fulfilled.
	TypeRegistry& type_registry();

} // namespace xParam_internal

#endif // XPARAM_REGISTRY_H
