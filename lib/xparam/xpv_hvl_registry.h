#ifndef XPARAM_HVL_REGISTRY_H
#define XPARAM_HVL_REGISTRY_H

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
 * provides a mapping from ValueLists to matching HomogenousValueLists
 */

#include <typeinfo>
#include <string>
#include <map>
#include "xp_config.h"
#include "xp_singleton.h"
#include "xp_handle.h"
#include "xp_type_compare.h"

namespace xParam_internal {

	class Value;
	class ValueList;
	class HVLCreator;

	class HVLRegistry {
		public:
			HVLRegistry();

			// registration
			void reg_creator(const Handle<HVLCreator>& hvl_creator);

			// get creator (by type_info of HVL<T>, not T)
			bool is_registered(const std::type_info& hvl_class) const;
			Handle<HVLCreator> get_creator(const std::type_info& hvl_class) const;

		private:
			typedef std::map<const std::type_info*, Handle<HVLCreator>, TypeInfoCmp> CreatorMap;
			CreatorMap m_creator_map;
	};



	// nicer syntax for access to the singleton
	inline HVLRegistry& hvl_registry() { 
		return Singleton<HVLRegistry>::get(); 
	}

} // namespace xParam_internal

#endif // XPARAM_HVL_REGISTRY_H
