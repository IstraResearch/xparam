#ifndef XPARAM_HVL_CREATOR_H
#define XPARAM_HVL_CREATOR_H

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
 * Base class for an object representing a constructor - The interface
 * provides information about the constructed type and the arguments.
 * It also provides a method to actually construct the new object given
 * actual arguments.
 */

#include <typeinfo>
#include "xp_config.h"
#include "xp_handle.h"
#include "xp_value.h"

namespace xParam_internal {

	class ValueList;

	class HVLCreator {
		public:
			virtual ~HVLCreator() {}

			virtual const std::type_info& created_type() const = 0;
			virtual const std::type_info& element_type() const = 0;

			// all elements of 'vl' must be convertible (using strict matching) to 
			// element_type(). 
			// This is asserted in the method implementation.
			virtual Handle<Value> create(const ValueList& vl) const = 0;
	};

} // namespace xParam_internal

#endif // XPARAM_HVL_CREATOR_H
