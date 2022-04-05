#ifndef XPARAM_HVL_H
#define XPARAM_HVL_H

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
 * a homogenous value list
 */

#include <vector>
#include "xp_config.h"
#include "xp_handle.h"
#include "xp_value_management_facade.h"

namespace xParam_internal {

	template<class T>
	class HVL : public std::vector< Handle<T> > {
		public:
			// t_ptr may be 0
			void append_copy(const T* t_ptr) {
				if (t_ptr)
					push_back( Handle<T>(get_copy_of(*t_ptr)) );
				else
					push_back( Handle<T>() );
			}

			// t_ptr may be 0
			void append_ref(const T* t_ptr) {
				T* nc_ptr = const_cast<T*>(t_ptr);
				Handle<T> ref_handle(nc_ptr,false); // create handle which doesn't own the data
				push_back(ref_handle);
			}
	};

} // namespace xParam_internal

#endif // XPARAM_HVL_H
