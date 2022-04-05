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
#include "../xparam/xp_value_management_facade.h"
#include "../xparam/xpv_registry.h"
#include "../xparam/xpv_scheduler.h"
#include "../xparam/xpv_const_registry.h"
#include "../xparam/xpv_type.h"

using namespace std;

namespace xParam_internal {

	void xparam_init()
	{
		registration_scheduler().mark_initialized();
		registration_scheduler().execute_registration();
	}

	string xparam_name(const type_info& type)
	{
		try {
			Type& t = type_registry().type(type);
			return t.name();
		}
		catch (const Error& err) {
			throw Error("in xparam_name() - " + string(err.what()));
		}
	}

	string xparam_or_cpp_name(const std::type_info& type)
	{
		TypeRegistry& registry = type_registry_registration_access();
		if (registry.is_registered(type))
			return xparam_name(type);
		else
			return type.name();
	}

	string xparam_help(const string& name)
	{
		try {
			// check for special string "PENDING"
			if (name == "PENDING") {
				return registration_scheduler().pending_commands_description();
			}

			// check if this is a constant
			if (const_registry().is_registered(name))
				return const_registry().type(name).help();

			// otherwise assume it's a typename
			return type_registry().type(name).help();
		}
		catch (const Error& err) {
			throw Error("in xparam_help() - " + string(err.what()));
		}
	}

	Handle<Value> create_value(const string& type_name, const ValueList& args, bool flexible)
	{
		try {
			Type& t = type_registry().type(type_name);
			return t.create(args,flexible);
		}
		catch(const Error& err) {
			throw Error("in create_value() - " + string(err.what()));
		}
	}

} // namespace xParam_internal

