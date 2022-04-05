#ifndef XPARAM_TYPED_TUPLE_CREATOR_IMP_H
#define XPARAM_TYPED_TUPLE_CREATOR_IMP_H

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
 * Template implementation of HVLCreator
 */

#include <typeinfo>
#include "xpv_typed_tuple_creator.h"
#include "xp_value_tuple.h"
#include "xp_typed_tuple.h"

namespace xParam_internal {

	template<class T_K>
	Handle<T_K> extract_from_tuple(const ValueTuple& tuple, int k, TypeTag<T_K>, bool flexible) 
	{
		assert(k>=0);
		assert(k < (int)tuple.size());

		const Handle<Value>& val = tuple[k];

		Handle<Value> converted_val = val->convert_to(typeid(T_K),flexible);
		assert(!converted_val.empty());

		assert(converted_val->static_type_info() == typeid(T_K));
		Handle<T_K> t_k = extract(*converted_val,TypeTag<T_K>());

		return t_k;
	}

 	///////////////////////////////////////////////
	// (Regular) Creator from ValueTuple (size 2)
	///////////////////////////////////////////////

	template<class T0,class T1>
	class GeneralTyped_2_TupleCreator {
		public:
			typedef Typed_2_Tuple<T0,T1> TypedTuple;

			static TypedTuple* create(const ValueTuple& tuple) 
			{
				assert(tuple.size() == 2);

				// this code is only used from flexible conversion code
				// so we can continue to use flexible conversions here
				Handle<T0> t0 = extract_from_tuple(tuple,0,TypeTag<T0>(),true);
				Handle<T1> t1 = extract_from_tuple(tuple,1,TypeTag<T1>(),true);

				return new TypedTuple(t0,t1);
			}
	};

 	/////////////////////////////////////
	// TypedTupleCreator (size 2)
	/////////////////////////////////////

	template<class T0, class T1>
	class Typed_2_TupleCreator : public TypedTupleCreator {
		public:
			typedef Typed_2_Tuple<T0,T1> TypedTuple;

			virtual const std::type_info& typed_tuple_type() const {
				return typeid(TypedTuple);
			}

			virtual int tuple_size() const { return 2; }

			virtual const std::type_info& element_type(int i) const {
				switch(i) {
				case 0:
					return typeid(T0);
				case 1:
					return typeid(T1);
				}
				throw Error("Illegal index in TypedTupleCreator::element_type()");
			}

			virtual Handle<Value> create(const ValueTuple& tuple) const 
			{
				assert(((int)tuple.size()) == tuple_size());

				// this code is only used from strict conversion code
				// so we can continue to use strict conversions here
				Handle<T0> t0 = extract_from_tuple(tuple,0,TypeTag<T0>(),false);
				Handle<T1> t1 = extract_from_tuple(tuple,1,TypeTag<T1>(),false);

				Handle<TypedTuple> typed_tuple(new TypedTuple(t0,t1));

				return make_value(typed_tuple);
			}
	};


} // namespace xParam_internal

#endif // XPARAM_TYPED_TUPLE_CREATOR_IMP_H
