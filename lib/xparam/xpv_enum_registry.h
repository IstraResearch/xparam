#ifndef XPARAM_ENUM_REGISTRY_H
#define XPARAM_ENUM_REGISTRY_H

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
 * provides a mapping from names to the corresponding Value object
 */

#include <string>
#include <map>
#include "xp_config.h"
#include "xp_type_tag.h"
#include "xp_singleton.h"

namespace xParam_internal {

	template<class T>
	class EnumRegistry {
		public:
			EnumRegistry();

			// registration
			void register_enum(const std::string& name, T value);

			// queries
			bool is_registered(T value) const throw();

			const std::string& name(T value);

		private:
			std::map<T, std::string> m_name_map;
	};

	// nicer syntax for access to the singleton
	template<class T>
	inline EnumRegistry<T>& enum_registry(TypeTag<T>) { 
		return Singleton<EnumRegistry<T> >::get(); 
	}


	template<class T>
	EnumRegistry<T>::EnumRegistry()
	{
#ifdef XPARAM_STATIC_LIB
// in future this will be used to register statically pre-defined
// enums.
#endif
	}

	template<class T>
	void EnumRegistry<T>::register_enum(const std::string& name, T value)
	{
		// ignore double registration (two names for same value are allowed
		// in the input, but only the first one registered will be used for
		// output).
		if (is_registered(value)) {
			return;
		}

		m_name_map[value] = name;
	}
	
	template<class T>
	bool EnumRegistry<T>::is_registered(T value) const throw()
	{
		return m_name_map.find(value) != m_name_map.end();
	}

	template<class T>
	const std::string& EnumRegistry<T>::name(T value)
	{
		assert(is_registered(value));
		return m_name_map[value];
	}

} // namespace xParam_internal

#endif // XPARAM_ENUM_REGISTRY_H
