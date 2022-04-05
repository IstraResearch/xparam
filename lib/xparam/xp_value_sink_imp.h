#ifndef XPARAM_VALUE_SINK_IMP_H
#define XPARAM_VALUE_SINK_IMP_H

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
 * Implements the Var and PtrVar functions (and the helper classes they need)
 */

#include <assert.h>
#include "xp_config.h"
#include "xp_error.h"
#include "xp_value_sink.h"

namespace xParam_internal {

	template<class T>
	class VarSink : public ValueSink {
		public:
			VarSink(T& var, bool flexible) : m_var(var), m_flexible(flexible) {}

			virtual void set_value(Handle<Value> val)
			{
				// convert to type T
				Handle<Value> converted_val = val->convert_to(typeid(T),m_flexible);

				// get the actual T object
				Handle<T> obj = extract(*converted_val,TypeTag<T>());

				// check value isn't NULL (not allowed for Var sinks)
				if (obj.empty())
					throw Error("tried to assign NULL into variable of type " 
												+ std::string(typeid(T).name()));

				// assign the value into the referenced variable
				m_var = *obj;
			}

			virtual bool flexible_conversions_enabled() const 
			{
				return m_flexible;
			}

		private:
			T& m_var;
			bool m_flexible;
	};

	template<class T>
	Handle<ValueSink> innerVar(T& var, bool flexible = true) {
		return Handle<ValueSink>(new VarSink<T>(var,flexible));
	}

	// Var function - returns a ValueSink from a variable
	template<class T>
	Handle<ValueSink> Var(T& var) {
		return innerVar(var);
	}


	template<class T>
	class PtrVarSink : public ValueSink {
		public:
			PtrVarSink(T*& var_ptr, bool flexible) : m_var_ptr(var_ptr), m_flexible(flexible) {}

			virtual void set_value(Handle<Value> val)
			{
				// convert to type T
				Handle<Value> converted_val = val->convert_to(typeid(T),m_flexible);

				// get an owned copy of the object
				T* tptr = get_owned_copy(*converted_val,TypeTag<T>()); 

				// assign the pointer into the referenced variable
				m_var_ptr = tptr;
			}

			virtual bool flexible_conversions_enabled() const 
			{
				return m_flexible;
			}

		private:
			T*& m_var_ptr;
			bool m_flexible;
	};

	template<class T>
	Handle<ValueSink> innerPtrVar(T*& var_ptr, bool flexible = true) {
		return Handle<ValueSink>(new PtrVarSink<T>(var_ptr,flexible));
	}

	// PtrVar function - returns a ValueSink from a pointer variable
	template<class T>
	Handle<ValueSink> PtrVar(T*& var_ptr) {
		return innerPtrVar(var_ptr);;
	}

} // namespace xParam_internal

#endif // XPARAM_VALUE_SINK_IMP_H
