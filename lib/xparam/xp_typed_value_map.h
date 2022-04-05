#ifndef XPARAM_TYPED_VALUE_MAP_H
#define XPARAM_TYPED_VALUE_MAP_H

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
 * a typed value map (used as the value of map types)
 */

#include <vector>
#include "xp_config.h"
#include "xp_handle.h"

namespace xParam_internal {

	template<class KEY, class VALUE>
	struct TypedValueMapItem {
		TypedValueMapItem(const Handle<KEY>& _key, const Handle<VALUE>& _value)
			: key(_key), value(_value)
		{}

		Handle<KEY> key;
		Handle<VALUE> value;
	};

	template<class KEY, class VALUE> 
	class TypedValueMap : public std::vector< TypedValueMapItem<KEY,VALUE> > {
	public:
		typedef TypedValueMapItem<KEY,VALUE> MapItem;

		// val_ptr may be 0
		void append_copy(const KEY& key, const VALUE* val_ptr) 
		{
			Handle<KEY> key_handle( get_copy_of(key) );

			Handle<VALUE> val_handle; // represents NULL
			if (val_ptr)
				val_handle = Handle<VALUE>( get_copy_of(*val_ptr) );

                       this->push_back( MapItem(key_handle,val_handle) );
		}
		
		// val_ptr may be 0
		void append_ref(const KEY& key, const VALUE* val_ptr) 
		{
			// use handles that don't own the data
			KEY* nc_key_ptr = const_cast<KEY*>(&key);
			Handle<KEY> ref_key_handle(nc_key_ptr,false);

			VALUE* nc_val_ptr = const_cast<VALUE*>(val_ptr);
			Handle<VALUE> ref_val_handle(nc_val_ptr,false);

                       this->push_back( MapItem(ref_key_handle,ref_val_handle) );
		}
	};

} // namespace xParam_internal

#endif // XPARAM_TYPED_VALUE_MAP_H
