#ifndef XPARAM_ARG_PASSERS_H
#define XPARAM_ARG_PASSERS_H

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
 * classes for extracting parameters out of Value objects, and returning
 * them with the correct passing mode
 */

#include <typeinfo>
#include <string>
#include "xp_config.h"
#include "xp_error.h"
#include "xp_handle.h"
#include "xp_value_management.h"
#include "xpv_arg_def.h"

namespace xParam_internal {

	/////////////////////////////////////////////////////////////////////////////
	// An ArgPasser must have the following interface (usable by templates code)
	//
	// ArgPasserX::matched_type - typedef for the type expected as input
	// ArgPasserX::passed_type - typedef for type & passing mode passed on
	// ArgPasserX::pass(Handle<Value>) returns a passed_type
	// ArgPasserX::typed_pass(Handle<matched_type>) same as Handle<Value>
	/////////////////////////////////////////////////////////////////////////////

	template<class T>
		class ByVal : public ArgDef {
		public:
			typedef T matched_type;
			typedef T passed_type;

			static passed_type typed_pass(const Handle<T>& obj) {
				return *obj;
			}

			static passed_type pass(const Handle<Value>& val) {
				Handle<T> obj = extract(*val,TypeTag<T>());
				if (obj.empty())
					throw Error("NULL passed where valid value of type " 
								+ std::string(typeid(T).name()) + " is required");
				return typed_pass(obj);
			}

			ByVal(const std::string& name) : ArgDef(typeid(matched_type),name) {}
	};


	template<class T>
		class ConstRef : public ArgDef {
		public:
			typedef T matched_type;
			typedef const T& passed_type;

			static passed_type typed_pass(const Handle<T>& obj) {
				return *obj;
			}

			static passed_type pass(const Handle<Value>& val) {
				Handle<T> obj = extract(*val,TypeTag<T>());
				if (obj.empty())
					throw Error("NULL passed where valid value of type " 
					+ std::string(typeid(T).name()) + " is required");
				return typed_pass(obj);
			}

			ConstRef(const std::string& name) : ArgDef(typeid(matched_type),name) {}
	};


	template<class T>
		class CallerPtr : public ArgDef {
		public:
			typedef T matched_type;
			typedef T* passed_type;

			static passed_type typed_pass(const Handle<T>& obj) {
				return obj.get();
			}

			static passed_type pass(const Handle<Value>& val) {
				Handle<T> obj = extract(*val,TypeTag<T>());
				return typed_pass(obj);
			}

			CallerPtr(const std::string& name) : ArgDef(typeid(matched_type),name) {}
	};

	template<class T>
		class CallerConstPtr : public ArgDef {
		public:
			typedef T matched_type;
			typedef const T* passed_type;

			static passed_type typed_pass(const Handle<T>& obj) {
				return obj.get();
			}

			static passed_type pass(const Handle<Value>& val) {
				Handle<T> obj = extract(*val,TypeTag<T>());
				return typed_pass(obj);
			}

			CallerConstPtr(const std::string& name) : ArgDef(typeid(matched_type),name) {}
	};


	template<class T>
		class ClassPtr : public ArgDef {
		public:
			typedef T matched_type;
			typedef T* passed_type;

			static passed_type typed_pass(const Handle<T>& obj) {
				return pass( make_value(obj) );
			}

			static passed_type pass(const Handle<Value>& val) {
				return get_owned_copy(*val,TypeTag<T>());
			}

			ClassPtr(const std::string& name) : ArgDef(typeid(matched_type),name) {}
	};

	template<class T>
		class ClassConstPtr : public ArgDef {
		public:
			typedef T matched_type;
			typedef const T* passed_type;

			static passed_type typed_pass(const Handle<T>& obj) {
				return pass( make_value(obj) );
			}

			static passed_type pass(const Handle<Value>& val) {
				return get_owned_copy(*val,TypeTag<T>());
			}

			ClassConstPtr(const std::string& name) : ArgDef(typeid(matched_type),name) {}
	};

	// converts to Trg and passes it by value
	template<class Src, class Trg>
		class AsConvertedVal : public ArgDef {
		public:
			typedef Src matched_type;
			typedef Trg passed_type;

			static passed_type typed_pass(const Handle<Src>& src) {
				return (Trg)(*src);
			}

			static passed_type pass(const Handle<Value>& val) {
				Handle<Src> src = extract(*val,TypeTag<Src>());
				if (src.empty())
					throw Error("NULL passed where valid value of type " 
					+ std::string(typeid(Src).name()) + " is required");
				return typed_pass(src);
			}

			AsConvertedVal(const std::string& name) : ArgDef(typeid(matched_type),name) {}
	};

	// matches string, passes const char*
	class AsCString : public ArgDef {
	public:
		typedef std::string matched_type;
		typedef const char* passed_type;

		static passed_type typed_pass(const Handle<std::string>& str) {
			return str->c_str();
		}
		
		static passed_type pass(const Handle<Value>& val) {
			Handle<std::string> str = extract(*val,TypeTag<std::string>());
			if (str.empty())
				throw Error("NULL passed where valid value of type string is required");
			return typed_pass(str);
		}

		AsCString(const std::string& name) : ArgDef(typeid(matched_type),name) {}
	};

} // namespace xParam_internal

#endif // XPARAM_ARG_PASSERS_H
