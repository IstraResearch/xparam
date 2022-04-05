#ifndef XPARAM_HVL_CREATOR_IMP_H
#define XPARAM_HVL_CREATOR_IMP_H

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
#include <memory>
#include "xpv_hvl_creator.h"
#include "xp_value_list.h"
#include "xp_hvl.h"

namespace xParam_internal {

	template<class T>
	HVL<T>* create_HVL(const ValueList& vl, TypeTag<T>, bool flexible) 
	{
		std::auto_ptr< HVL<T> > hvl(new HVL<T>);
		
		ValueList::const_iterator i;
		for (i=vl.begin(); i!=vl.end(); ++i) {
			const Handle<Value>& val = *i;
			
			Handle<Value> tval = val->convert_to(typeid(T),flexible);
			assert(!tval.empty());
			
			assert(tval->static_type_info() == typeid(T));
			Handle<T> t = extract(*tval,TypeTag<T>());
			
			hvl->push_back(t);
		}

		return hvl.release();
	}


 	///////////////////////////////////////////////
	// (Regular) Creator from ValueList
	///////////////////////////////////////////////

	template<class T>
	class GeneralHVLCreator {
		public:
			static HVL<T>* create(const ValueList& vl) 
			{
				// this creator is only used from flexible conversion code
				// so we can continue to use flexible conversions here
				return create_HVL(vl, TypeTag<T>(), true);
			}
	};

 	///////////////////////////////////////////////
	// Typed HVL Creator
	///////////////////////////////////////////////

	template<class T>
	class TypedHVLCreator : public HVLCreator {
		public:
			virtual const std::type_info& created_type() const {
				return typeid(HVL<T>);
			}


			virtual const std::type_info& element_type() const {
				return typeid(T);
			}

			virtual Handle<Value> create(const ValueList& vl) const 
			{
				// this creator is only used from strict conversion code
				// so we can continue to use strict conversions here
				HVL<T>* hvl = create_HVL(vl, TypeTag<T>(), false);
				Handle< HVL<T> > hvl_handle(hvl);
				return make_value(hvl_handle);
			}
	};


} // namespace xParam_internal

#endif // XPARAM_HVL_CREATOR_IMP_H
