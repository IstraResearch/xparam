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
#include "../xparam/xpv_common_regcom.h"
#include "../xparam/xpv_registry.h"

using namespace std;

namespace xParam_internal {

	CommonRegCommand::CommonRegCommand(const DependencyVector& deps)
		: m_dependencies(deps)
	{
	}

	CommonRegCommand::CommonRegCommand(const type_info& dep) 
	{
		add_dependency(dep);
	}

	CommonRegCommand::CommonRegCommand(const type_info& dep1, const type_info& dep2)
	{
		add_dependency(dep1);
		add_dependency(dep2);
	}

	void CommonRegCommand::add_dependency(const std::type_info& dep) 
	{
		m_dependencies.push_back(&dep);
	}

	bool CommonRegCommand::can_register() const
	{
		const TypeRegistry& registry = type_registry_registration_access();

		vector<const type_info*>::const_iterator i;
		for (i=m_dependencies.begin(); i!=m_dependencies.end(); ++i) {
			if (!registry.is_registered(**i))
				return false;
		}
		return true;
	}

	string CommonRegCommand::description() const
	{
		return string("Registration command object - ") + typeid(*this).name();
	}

	string CommonRegCommand::unfulfilled_dependencies() const
	{
		string description;
		const TypeRegistry& registry = type_registry_registration_access();

		vector<const type_info*>::const_iterator i;
		for (i=m_dependencies.begin(); i!=m_dependencies.end(); ++i) {
			if (!registry.is_registered(**i)) {
				if (!description.empty())
					description += ", ";
				description += string("type ") + (*i)->name();
			}
		}
		return description;
	}

} // namespace xParam_internal

