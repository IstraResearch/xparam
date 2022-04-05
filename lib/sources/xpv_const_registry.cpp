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

#include <stdlib.h>
#include <string.h>
#include "../xparam/xp_handle.h"
#include "../xparam/xpv_type.h"
#include "../xparam/xpv_const_registry.h"

using namespace std;

namespace xParam_internal {

	ConstRegistry::ConstRegistry()
	{
#ifdef XPARAM_STATIC_LIB
// in future this will be used to register statically pre-defined
// consts such as "true" and "false".
#endif
	}

	void ConstRegistry::register_const(Handle<Value> new_val, const string& name)
	{
		// ignore double registration (no check for 
		// incompatible information yet ...)
		if (is_registered(name))
			return;

		m_name_map[name] = new_val;

	}
	
	bool ConstRegistry::is_registered(const string& name) const throw()
	{
		return m_name_map.find(name) != m_name_map.end();
	}

	const Type& ConstRegistry::type(const string& name)
	{
		return value(name)->static_type();
	}

	Handle<Value> ConstRegistry::value(const string& name)
	{
		assert(is_registered(name));
// No dynamic loading of constants, yet.
		return m_name_map[name];
	}


} // namespace xParam_internal
