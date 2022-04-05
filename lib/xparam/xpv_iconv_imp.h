#ifndef XPARAM_ICONV_IMP_H
#define XPARAM_ICONV_IMP_H

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
 * Implementations of the IConv interface. 
 * We have one implementation for a direct inheritance relationship, and
 * another which forwards requests to sub IConv objects.
 */

#include <typeinfo>
#include <vector>
#include <assert.h>
#include "xp_config.h"
#include "xpv_iconv.h"

namespace xParam_internal {

	template<class Base, class Derived>
		class DirectIConv : public IConv {
		public:
			virtual const std::type_info& ancestor() const { return typeid(Base); }
			virtual const std::type_info& descendant() const { return typeid(Derived); }
			
			// whether this corresponds to a direct inheritance,
			// or goes through intermediate classes.
			// DirectIConv is only used for registering direct inheritance
			virtual bool is_atomic() const {return true;}

			// 'val' must satisfy 
			//      val->static_type_info() == ancestor()
			// the return value 'ret' will satisfy 
			//      ret->static_type_info() == descendant()
			virtual Handle<Value> downcast(const Value& val) const 
			{
				assert(val.static_type_info() == ancestor());
				Handle<Base> base = extract(val,TypeTag<Base>());
				Handle<Derived> derived = dynamic_handle_cast(base,TypeTag<Derived>());
				assert(!derived.empty());
				return make_value(derived);
			}
			
			// 'obj' must satisfy 
			//       reinterpret_cast<B*>(obj) is a legal B* (where typeid(B)==descendant())
			// the return value 'ret' will statify
			//       reinterpret_cast<A*>(obj) is a legal A* (where typeid(A)==ancestor())
			virtual void* upcast(void *obj) const 
			{
				Derived* derived = reinterpret_cast<Derived*>(obj);
				Base* base = derived;
				return reinterpret_cast<void*>(base);
			}
		};


		class CompositeIConv : public IConv {
		public:
			// sub_conversions should be ordered from ancestor to descendant
			CompositeIConv(const std::vector< Handle<IConv> >& sub_conversions)
				: m_sub_conversions(sub_conversions) {
				assert(!sub_conversions.empty());

				std::vector< Handle<IConv> >::const_iterator i;
				for (i = sub_conversions.begin();
					 i+1 != sub_conversions.end(); 
					 ++i) {
					assert((*i)->descendant() == (*(i+1))->ancestor());
				}
			}

			virtual const std::type_info& ancestor() const { 
				assert(!m_sub_conversions.empty());
				return m_sub_conversions[0]->ancestor();
			}

			virtual const std::type_info& descendant() const { 
				return m_sub_conversions.back()->descendant();
			}

			virtual bool is_atomic() const {return false;}

			// 'val' must satisfy 
			//      val.static_type_info() == ancestor()
			// the return value 'ret' will satisfy 
			//      ret->static_type_info() == descendant()
			virtual Handle<Value> downcast(const Value& val) const 
			{
				Handle<Value> tmp_val = m_sub_conversions[0]->downcast(val);

				std::vector< Handle<IConv> >::const_iterator i;
				for (i = m_sub_conversions.begin()+1;
					 i != m_sub_conversions.end();
					 ++i) {
					tmp_val = (*i)->downcast(*tmp_val);
				}
				return tmp_val;
			}
			
			// 'obj' must satisfy 
			//       reinterpret_cast<B*>(obj) is a legal B* (where typeid(B)==descendant())
			// the return value 'ret' will statify
			//       reinterpret_cast<A*>(obj) is a legal A* (where typeid(A)==ancestor())
			virtual void* upcast(void *obj) const 
			{
				std::vector< Handle<IConv> >::const_reverse_iterator i;
				for (i = m_sub_conversions.rbegin();
					 i != m_sub_conversions.rend();
					 ++i) {
					obj = (*i)->upcast(obj);
				}
				return obj;
			}

		private:
			std::vector< Handle<IConv> > m_sub_conversions; // ancestor first
		};

} // namespace xParam_internal

#endif // XPARAM_ICONV_IMP_H
