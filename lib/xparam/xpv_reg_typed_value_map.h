#ifndef XPARAM_REG_TYPED_VALUE_MAP_H
#define XPARAM_REG_TYPED_VALUE_MAP_H

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
 * Defines the user's API for registering a TypedValueMap
 */

#include <typeinfo>
#include <memory>
#include "xp_config.h"
#include "xpv_reg_hvl.h"
#include "xpv_reg_typed_tuple.h"
#include "xp_typed_value_map.h"

namespace xParam_internal {

	/////////////////////////////////////
	// Normal Creator (from HVL<Typed_2_Tuple>)
	/////////////////////////////////////

	template<class KEY, class VALUE>
	class TypedValueMapCreatorFromHVL {
		public:
			typedef TypedValueMap<KEY,VALUE> ValueMap;
			typedef typename ValueMap::MapItem MapItem;

			typedef Typed_2_Tuple<KEY,VALUE> TupleType;
			typedef HVL<TupleType> HVLType;

			static ValueMap* create(const HVLType& hvl) 
			{
				std::unique_ptr<ValueMap> val_map = std::make_unique<ValueMap>();

				typename HVLType::const_iterator i;
				for (i=hvl.begin(); i!=hvl.end(); ++i) {
					const Handle<TupleType>& tuple = *i;
					val_map->push_back( MapItem(tuple->val_0, tuple->val_1) );
				}

				return val_map.release();
			}
	};

	/////////////////////////////////////
	// Fake HVLCreator
	/////////////////////////////////////

	template<class KEY, class VALUE>
	class TypedValueMapCreator : public HVLCreator {
		public:
			typedef TypedValueMap<KEY,VALUE> ValueMap;
			typedef typename ValueMap::MapItem MapItem;

			typedef Typed_2_Tuple<KEY,VALUE> TupleType;
			typedef HVL<TupleType> HVLType;

			virtual const std::type_info& created_type() const {
				return typeid(ValueMap);
			}

			virtual const std::type_info& element_type() const {
				return typeid(TupleType);
			}

			virtual Handle<Value> create(const ValueList& vl) const 
			{
				// create hvl same way normal HVLCreator would
				HVLType* hvl = create_HVL(vl, TypeTag<TupleType>(), false);
				Handle<HVLType> hvl_handle(hvl);

				// use conversion creator to get ValueMap
				typedef TypedValueMapCreatorFromHVL<KEY,VALUE> ConversionCreator;
				Handle<ValueMap> val_map(ConversionCreator::create(*hvl_handle));

				return make_value(val_map);
			}
	};


	/////////////////////////////////////
	// TypedValueMap Output Function
	/////////////////////////////////////

	template<class KEY, class VALUE>
		class TypedValueMap_output {
		public:
			typedef TypedValueMap<KEY,VALUE> ValueMap;
			typedef typename ValueMap::MapItem Item;

			static void output(std::ostream& os, const ValueMap& m) 
			{
				os << "{";

				typename ValueMap::const_iterator i;
				for (i=m.begin(); i!=m.end(); ++i) {
					if (i!=m.begin())
						os << ", ";

					const Item& item = *i;

					Handle<Value> key_value = make_value(item.key);
					key_value->output(os);

					os << " => ";

					Handle<Value> val_value = make_value(item.value);
					val_value->output(os);
				}

				os << "}";
			}
	};

	/////////////////////////////////////
	// RegistrationCommand
	/////////////////////////////////////

	template<class KEY, class VALUE>
	class TypedValueMapClassRegCommand : public ClassRegCommand< TypedValueMap<KEY,VALUE> > {
		public:
			TypedValueMapClassRegCommand() 
				: ClassRegCommand< TypedValueMap<KEY,VALUE> >(typeid(KEY),typeid(VALUE)) {}

			virtual std::string type_name() const {
				return "xParam::TypedValueMap<"
						+ xparam_or_cpp_name(typeid(KEY)) 
						+ ","
						+ xparam_or_cpp_name(typeid(VALUE)) 
						+ ">";
			}
	};

	
	template<class KEY, class VALUE>
	class TypedValueMapRegCommand : public CommonRegCommand {
		public:
			typedef TypedValueMap<KEY,VALUE> ValueMap;
			typedef typename ValueMap::MapItem MapItem;

			typedef Typed_2_Tuple<KEY,VALUE> TupleType;
			typedef HVL<TupleType> HVLType;

			TypedValueMapRegCommand() : CommonRegCommand(typeid(KEY),typeid(VALUE)) {}

			virtual void do_registration() const 
			{
				// register TypedTuple
				register_typed_2_tuple<KEY,VALUE>();

				// register HVL
				register_hvl<TupleType>();

				// register fake HVLCreator, which actually creates the TypedValueMap
				Handle<HVLCreator> creator(new TypedValueMapCreator<KEY,VALUE>);
				hvl_registry().reg_creator(creator);

				// register class
				param_class<ValueMap>(new TypedValueMapClassRegCommand<KEY,VALUE>());

				// register conversion creator from HVLType
				typedef TypedValueMapCreatorFromHVL<KEY,VALUE> Creator;
				param_weighted_creator(TypeTag<ValueMap>(), TypeTag<Creator>(),
									   ConstRef<HVLType>("hvl"), CONV_STANDARD);					

				// register output
				typedef TypedValueMap_output<KEY,VALUE> OutputFunc;
				param_direct_output<ValueMap,OutputFunc>();
			}

			virtual std::string description() const {
				return "TypedValueMap for types " + xparam_or_cpp_name(typeid(KEY))
					+ " and " + xparam_or_cpp_name(typeid(VALUE));
			}
	};


	/////////////////////////////////////
	// registration API
	/////////////////////////////////////

	template<class KEY, class VALUE>	
		class register_typed_value_map {
		public:
			register_typed_value_map()
			{
				Handle<RegistrationCommand> command(new TypedValueMapRegCommand<KEY,VALUE>);
				registration_scheduler().add_command(command);
			}
		};

} // namespace xParam_internal

#endif // XPARAM_REG_TYPED_VALUE_MAP_H
