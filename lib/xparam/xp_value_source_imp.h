#ifndef XPARAM_VALUE_SOURCE_IMP_H
#define XPARAM_VALUE_SOURCE_IMP_H

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
 * Implements the Val and PtrVal functions (and the helper classes they need)
 */

#include "xp_value_source.h"
#include "xp_value_management.h"

namespace xParam_internal {

	class ValSource : public ValueSource {
	public:
		ValSource(const Handle<Value>& val) : m_val(val) {}
		virtual Handle<Value> get_value(bool flexible) const { return m_val;}
		
	private:
		Handle<Value> m_val;
	};

	// make_source - returns a Handle<ValueSource> from a Handle<Value>
	inline Handle<ValueSource> make_source(const Handle<Value>& val) {
		return Handle<ValueSource>(new ValSource(val));
	}

	// Val function - returns a Handle<ValueSource> from an object
	template<class T>
		Handle<ValueSource> Val(const T& val) {
			return make_source(make_value_copy(val));
		}

	inline Handle<ValueSource> Val(const char* c_string) {
		return Val(std::string(c_string));		
	}

	/*
	typedef const char* ConstCString;

	inline Handle<ValueSource> Val(const ConstCString& c_string) {
		return Val(std::string(c_string));		
	}

	typedef char* NonConstCString;

	inline Handle<ValueSource> Val(const NonConstCString& c_string) {
		return Val(std::string(c_string));		
	}
	*/

	// PtrVal function - returns a Handle<ValueSource> from a pointer to an object
	template<class T>
	Handle<ValueSource> PtrVal(const T* val_ptr) 
	{
		return make_source(make_value_copy_ptr(val_ptr));
	}

	// ParseSource - parses a value from a given string
	class ParseSource : public ValueSource {
	public:
		ParseSource(const std::string& str) : m_str(str) {}
		virtual Handle<Value> get_value(bool flexible) const;
		
	private:
		std::string m_str;
	};

	inline Handle<ValueSource> xParse(const std::string& str) 
	{
		return Handle<ValueSource>(new ParseSource(str));
	}


} // namespace xParam_internal

#endif // XPARAM_VALUE_SOURCE_IMP_H
