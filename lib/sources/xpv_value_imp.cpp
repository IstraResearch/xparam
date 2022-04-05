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

#pragma warning (disable: 4786)

#include <typeinfo>
#include "../xparam/xpv_value_imp.h"
#include "../xparam/xpv_registry.h"
#include "../src_include/xpv_conversions.h"
#include "../src_include/xp_sstream.h"
#include "../src_include/xpv_tentative.h"
#include "../xparam/xp_value_list.h"
#include "../xparam/xpv_hvl_registry.h"
#include "../xparam/xpv_hvl_creator.h"
#include "../xparam/xp_value_tuple.h"
#include "../xparam/xpv_typed_tuple_registry.h"
#include "../xparam/xpv_typed_tuple_creator.h"

using namespace std;

namespace xParam_internal {

	const Type& ValuePartialImp::static_type() const {
		return type_registry().type(static_type_info());
	}
	
	const Type& ValuePartialImp::dynamic_type() const {
		return type_registry().type(dynamic_type_info());
	}
	
	void ValuePartialImp::output(ostream& os) const {
		dynamic_type().output(os,*this);
	}

	string ValuePartialImp::to_string() const {
		Oss oss;
		output(oss);
		return oss.str();
	}

	bool ValuePartialImp::isa(const std::type_info& t) const
	{
		if (t == static_type_info())
			return true;

		if (type_registry().is_registered(t)) {
			const Type& type = type_registry().type(t);
			return type.is_ancestor_of(static_type_info());
		}

		return false;
	}


	bool ValuePartialImp::can_convert_to(const type_info& target, bool flexible) const
	{
		// check exact match
		if (static_type_info() == target)
			return true;

		if (flexible) {
			return find_best_paths(get_handle(),target).size() == 1;
		}
		else { // strict conversions
			// TentativeValue -> strict type
			if (static_type_info() == typeid(TentativeValue)) {
				Handle<TentativeValue> tv = extract(*this,TypeTag<TentativeValue>());
				assert(!tv.empty());

				// operator == of type_info returns int on VC++, so...
				return (tv->strict_type() == target) ? true : false;
			}
			
			// ValueList -> HomogenousValueList
			if (static_type_info() == typeid(ValueList)) {
				Handle<ValueList> vl = extract(*this,TypeTag<ValueList>());
				assert(!vl.empty());

				Handle<HVLCreator> creator = hvl_registry().get_creator(target);
				if (creator.empty())
					return false;

				// check elements recursively
				const type_info& required_type = creator->element_type();
				ValueList::const_iterator i;
				for (i=vl->begin(); i!=vl->end(); ++i) {
					if (!(*i)->can_convert_to(required_type,false))
						return false;
				}
				return true;
			}
			
			// ValueTuple -> Typed_K_Tuple
			if (static_type_info() == typeid(ValueTuple)) {
				Handle<ValueTuple> tuple = extract(*this,TypeTag<ValueTuple>());
				assert(!tuple.empty());

				Handle<TypedTupleCreator> creator = typed_tuple_registry().get_creator(target);
				if (creator.empty())
					return false;

				// check that size matches
				if (tuple->size() != creator->tuple_size())
					return false;

				// check elements recursively
				ValueTuple::const_iterator iVal;
				int k;
				for (iVal=tuple->begin(), k=0; iVal!=tuple->end(); ++iVal, ++k) {
					if (!(*iVal)->can_convert_to(creator->element_type(k),false))
						return false;
				}
				return true;
			}
			
			// Derived -> Base
			if (type_registry().is_registered(target)) {
				const Type& target_type = type_registry().type(target);
				return target_type.is_ancestor_of(static_type_info());
			}

			// no strict conversion found
			return false;
		}
	}
	
	Handle<Value> ValuePartialImp::convert_to(const type_info& target, bool flexible) const 
	{
		if (flexible)
			return convert_flexible(target);
		else
			return convert_strict(target);
	}

	Handle<Value> ValuePartialImp::convert_flexible(const std::type_info& target) const
	{
		if (static_type_info() == target)
			return get_handle();

		Handle<Value> val = get_handle();
		vector<ConvPath> best_paths = find_best_paths(val,target);

		if (best_paths.size() != 1) 
		{
			string source_type_name = static_type().name();
			string target_type_name = type_registry().type(target).name();

			Oss base_oss;
			base_oss << "from " << source_type_name;
			base_oss << " ( ";
			output(base_oss);
			base_oss << " ) "	<< " to " << target_type_name;
			string msg = base_oss.str();

			if (best_paths.empty())
				throw Error ("no conversion path found " + msg);
			if (best_paths.size() > 1) {
				Oss oss2;
				oss2 << "More than one conversion path found " << msg << ":" << endl;

				vector<ConvPath>::const_iterator i;
				for (i=best_paths.begin(); i!=best_paths.end(); ++i) {
					const ConvPath& path = *i;
					oss2 << "\t" << source_type_name;

					ConvPath::const_iterator j;
					for (j=path.begin(); j!=path.end(); ++j)
						oss2 << " -> " << type_registry().type(**j).name();
					oss2 << endl;
				}
				throw Error(oss2.str());
			}
		}
		
		const ConvPath& path = best_paths.front();
		assert(path.empty() || (*path.back() == target));
		
		return convert_along_path(val,path);
	}

	Handle<Value> ValuePartialImp::convert_strict(const std::type_info& target) const
	{
		try {
			// exact match
			if (static_type_info() == target)
				return get_handle();
			
			// TentativeValue -> strict type
			if (static_type_info() == typeid(TentativeValue)) {
				Handle<TentativeValue> tv = extract(*this,TypeTag<TentativeValue>());
				assert(!tv.empty());
				
				if (tv->strict_type() == target)
					return tv->strictly_typed_value();
				else
					throw Error("TentativeValue type mismatch");
			}
			
			// ValueList -> HomogenousValueList
			if (static_type_info() == typeid(ValueList)) {
				Handle<ValueList> vl = extract(*this,TypeTag<ValueList>());
				assert(!vl.empty());
				
				Handle<HVLCreator> creator = hvl_registry().get_creator(target);
				if (creator.empty())
					throw Error("No HVL Creator registered for type");
				return creator->create(*vl);
			}
			
			// ValueTuple -> Typed_K_Tuple
			if (static_type_info() == typeid(ValueTuple)) {
				Handle<ValueTuple> tuple = extract(*this,TypeTag<ValueTuple>());
				assert(!tuple.empty());
				
				Handle<TypedTupleCreator> creator = typed_tuple_registry().get_creator(target);
				if (creator.empty())
					throw Error("No Typed Tuple Creator registered for type");
				return creator->create(*tuple);
			}
			
			// other type - try inheritance conversion
			if (type_registry().is_registered(target)) {
				const Type& target_type = type_registry().type(target);
				if (target_type.is_ancestor_of(static_type_info())) {
					return target_type.create_from_descendant(get_handle());
				}
			}

			throw Error("");

		}
		catch (Error& ex) {
			string source_type_name = static_type().name();
			string target_type_name = type_registry().type(target).name();

			Oss oss;
			oss << "no strict conversion found from " << source_type_name;
			oss << " ( ";
			output(oss);
			oss << " ) " << " to " << target_type_name;

			string reason = ex.what();
			if (!reason.empty())
				oss << ":" << endl << reason;

			string msg = oss.str();

			throw Error(msg);
		}
	}

} // namespace xParam_internal

