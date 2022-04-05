#ifndef XPARAM_COPIER_IMP_H
#define XPARAM_COPIER_IMP_H

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
 * Copier implementations. 
 * CopyCtorCopier uses the copy constructor to copy an object.
 * ErrorCopier is a placeholder and should never be invoked (unless we have a bug).
 */

#include <typeinfo>
#include "xp_config.h"
#include "xp_value.h"
#include "xpv_copier.h"

namespace xParam_internal {

	template<class T>
		class CopyCtorCopier : public Copier {
		public:
			virtual const std::type_info& type() const { return typeid(T); }
			
			virtual void* copy(const Value& val) const 
			{ 
				assert(val.dynamic_type_info() == type());
				assert(val.static_type_info() == type());
				Handle<T> original = extract(val,TypeTag<T>());
				T* obj_copy = new T(*original);
				return reinterpret_cast<void*>(obj_copy);
			}
	};
	
	class ErrorCopier : public Copier {
		public:
			ErrorCopier(const std::type_info& type) : m_type(type) {}

			virtual const std::type_info& type() const { return m_type; }

			virtual void* copy(const Value& val) const 
			{ 
				assert(false); 
				return 0;
			}

		private:
			const std::type_info& m_type;
	};

} // namespace xParam_internal

#endif // XPARAM_COPIER_IMP_H
