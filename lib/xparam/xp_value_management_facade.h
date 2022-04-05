#ifndef XPARAM_VALUE_MANAGEMENT_FACADE_H
#define XPARAM_VALUE_MANAGEMENT_FACADE_H

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
 * interface to value management functions from outside the value management
 * module.
 * Hides most of the details of value management module.
 */

#include <typeinfo>
#include <string>
#include "xp_handle.h"

namespace xParam_internal {

	class Value;
	class ValueList;

	// Should be called after main() starts to indicate it's safe to 
	// perform the registration.
	// This command only has effect if the library was compiled with 
	// the define XPARAM_EXPLICIT_INIT.
	void xparam_init();

	std::string xparam_name(const std::type_info& type);
	std::string xparam_or_cpp_name(const std::type_info& type);
	std::string xparam_help(const std::string& name);

	Handle<Value> create_value(const std::string& type_name, 
								const ValueList& args, 
								bool flexible = true);

	// The following template functions are implemented in xpv_facade_imp.h
	// and will be instantiatiated by forced implicit instantiation
	// for each registered type.

	template<class T> Handle<Value> make_value(Handle<T> obj);
	template<class T> Handle<Value> make_value_copy(const T& obj);
	template<class T> Handle<Value> make_value_copy_ptr(const T* obj_ptr);

	template<class T> Handle<T> extract(const Value& val, TypeTag<T>);
	template<class T> T* get_owned_copy(const Value& val, TypeTag<T>);
	template<class T> T* get_copy_of(const T& obj);

} // namespace xParam_internal

#endif // XPARAM_VALUE_MANAGEMENT_FACADE_H
