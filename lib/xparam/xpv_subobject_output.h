#ifndef XPARAM_SUBOBJECT_OUTPUT_H
#define XPARAM_SUBOBJECT_OUTPUT_H

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
 * Output Function implementation which wraps a functor that
 * can describe the object in terms of its sub-objects.
 * These sub-objects are then printed recursively.
 * 
 * The wrapped functor class F for type T should support the call 
 * F::sub_objects(obj), where 'obj' is an object of type T. This method
 * should return a ValueList of the sub-objects.
 */

#include "xp_config.h"
#include "xpv_output.h"
#include "xpv_registry.h"
#include "xp_value_list.h"

namespace xParam_internal {

	template<class T, class F>
	class SubObjectOutput : public OutputFunction {
		public:
			SubObjectOutput() : OutputFunction(typeid(T)) {}
			
			virtual void output(std::ostream& os, const Value& val) const 
			{
				Handle<T> obj;
				try {
					obj = extract(val,TypeTag<T>());
				}
				catch(...) {
					assert(false);
				}

				ValueList sub_objects = F::sub_objects(*obj);

				os << type_registry().type(typeid(T)).name();
				os << "(";

				ValueList::iterator i;
				for (i=sub_objects.begin(); i!=sub_objects.end(); ++i) {
					if (i!=sub_objects.begin())
						os << ",";
					(*i)->output(os);
				}
				os << ")";
			}
	};

} // namespace xParam_internal

#endif // XPARAM_SUBOBJECT_OUTPUT_H
