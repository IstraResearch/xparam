#ifndef XPARAM_VALUE_MANAGEMENT_FACADE_IMP_H
#define XPARAM_VALUE_MANAGEMENT_FACADE_IMP_H

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
 * Implementation of value functions defined in xp_value_management_facade.h
 * These functions will be instantiated by forced implicit instantiation for
 * each registered type.
 */

#include <typeinfo>
#include "xp_value_management_facade.h"
#include "xpv_registry.h"
#include "xpv_value_imp.h"
#include "xp_error.h"

namespace xParam_internal {

	template<class T>	
		Handle<Value> make_value(Handle<T> obj) 
		{
			return Handle<Value>(new TypedValue<T>(obj));
		}

	template<class T>
		Handle<Value> make_value_copy(const T& obj) 
		{
			return make_value(Handle<T>(get_copy_of(obj)));
		}	
	
	template<class T>	
		Handle<Value> make_value_copy_ptr(const T* obj_ptr) 
		{
			if (obj_ptr != 0)
				return make_value_copy(*obj_ptr);
			else
				return make_value(Handle<T>());
		}
	
	template<class T>	
		Handle<T> extract(const Value& val, TypeTag<T>) 
		{
			if (val.static_type_info() != typeid(T))
				throw Error("extract<" + xparam_name(typeid(T)) 
							+ ">() called on value of type " 
							+ xparam_name(val.static_type_info()));
			
			try {
				const TypedValue<T>& tval = dynamic_cast<const TypedValue<T>&>(val);
				return tval.member();
			}
			catch(...) {
				assert(false);
			}
			return Handle<T>(); // just to silence the compiler (never actually happens)
		}

	template<class T> 
		T* get_owned_copy(const Value& val, TypeTag<T>) 
		{
			if (val.static_type_info() != typeid(T))
				throw Error("get_owned_copy<" + xparam_name(typeid(T)) 
							+ ">() called on value of type " 
							+ xparam_name(val.static_type_info()));

			if (val.empty())
				return 0; // we can handle NULL here

			Type& type = type_registry().type(val.dynamic_type_info());
			void *void_ptr_copy = type.get_owned_copy(val);
			return reinterpret_cast<T*>(void_ptr_copy);
		}

		template<class T> T* get_copy_of(const T& obj)
		{
			T& non_const_ref = const_cast<T&>(obj);
			Handle<T> ref_handle(&non_const_ref,false); // create handle which doesn't own the data
			Handle<Value> ref_value = make_value(ref_handle);
			return get_owned_copy(*ref_value,TypeTag<T>());
		}

} // namespace xParam_internal

#endif // XPARAM_VALUE_MANAGEMENT_FACADE_IMP_H
