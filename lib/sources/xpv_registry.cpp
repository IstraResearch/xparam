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

#pragma warning (disable: 4786)

#include <typeinfo>
#include <stdlib.h>
#include <string.h>
#include "../xparam/xpv_registry.h"
#include "../xparam/xpv_scheduler.h"
#include "../src_include/xpv_dynamic_loader.h"

#include "../src_include/xpv_link_patch.h"

using namespace std;

namespace xParam_internal {

	TypeRegistry::TypeRegistry()
	{
#ifdef XPARAM_STATIC_LIB
		link_in_regtype_bool();
		link_in_regtype_char();
		link_in_regtype_double();
		link_in_regtype_float();
		link_in_regtype_long_double();
		link_in_regtype_short();
		link_in_regtype_int();
		link_in_regtype_long();
		link_in_regtype_longlong();
		link_in_regtype_null();
		link_in_regtype_string();
		link_in_regtype_tentative();
		link_in_regtype_uchar();
		link_in_regtype_ushort();
		link_in_regtype_uint();
		link_in_regtype_ulong();
		link_in_regtype_ulonglong();
		link_in_regtype_value_list();
		link_in_regtype_value_tuple();
		link_in_regtype_raw_bytes();
#endif
	}

	void TypeRegistry::register_type(Handle<Type> new_type)
	{
		// ignore double registration (but check for 
		// incompatible information)
		if (is_registered(new_type->type_info())) {
			Type& current_type = type(new_type->type_info());
			if (current_type.name() != new_type->name())
				throw Error("Registration conflict: type '" + new_type->name() 
							+ "' is already registered under the name '" 
							+ current_type.name() + "'");
			return;
		}

		m_name_map[new_type->name()] = new_type;
		m_typeinfo_map[&new_type->type_info()] = new_type;

		registration_scheduler().execute_registration();
	}
	
	bool TypeRegistry::is_registered(const string& name) const throw()
	{
		return m_name_map.find(name) != m_name_map.end();
	}

	bool TypeRegistry::is_registered(const type_info& ti) const throw()
	{
		return m_typeinfo_map.find(&ti) != m_typeinfo_map.end();
	}

	Type& TypeRegistry::type(const string& name)
	{
		if (!is_registered(name))
			dynamic_load(name);

		// load() should only return if it was successful
		assert(is_registered(name));
		return *m_name_map[name];
	}

	Type& TypeRegistry::type(const type_info& ti)
	{
		if (!is_registered(ti))
			throw Error(string("tried to access unregistered type ") + ti.name());
		return *m_typeinfo_map[&ti];
	}

	TypeRegistry& type_registry() { 
		static bool first_time = true;

		if (first_time) {
			registration_scheduler().execute_registration();
			first_time = false;
		}

		return Singleton<TypeRegistry>::get(); 
	}

} // namespace xParam_internal
