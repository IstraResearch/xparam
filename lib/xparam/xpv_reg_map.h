#ifndef XPARAM_REG_MAP_H
#define XPARAM_REG_MAP_H

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
 * Defines the user's API for registering maps
 */

#include <iosfwd>
#include <map>
#include <memory>
#include "xp_config.h"
#include "xp_value_list.h"
#include "xp_value_tuple.h"
#include "xpv_arg_passers.h"
#include "xpv_scheduler.h"
#include "xpv_common_regcom.h"
#include "xpv_convweight.h"

#include "xpv_reg_class.h"
#include "xpv_reg_ctor.h"
#include "xpv_reg_output.h"
#include "xpv_reg_conversion.h"
#include "xpv_reg_typed_value_map.h"

namespace xParam_internal {

 	/////////////////////////////////////
	// Map Kinds
	/////////////////////////////////////

	template<class KEY, class VALUE>
	class ByValMap {
		public:
			typedef std::map<KEY,VALUE> MapType;
			typedef KEY KeyType;
			typedef VALUE ValueType;
			typedef ConstRef<VALUE> ValuePasser;

			static const VALUE* get_value_ptr(const VALUE& val) {
				return &val;
			}

			static std::string map_name(const std::string& key_name,
				                        const std::string& value_name) {
				return "map<" + key_name + "," + value_name + ">";
			}
	};

	template<class KEY, class VALUE>
	class PtrMap {
		public:
			typedef std::map<KEY,VALUE*> MapType;
			typedef KEY KeyType;
			typedef VALUE ValueType;
			typedef ClassPtr<VALUE> ValuePasser;

			static const VALUE* get_value_ptr(VALUE* val_ptr) {
				return val_ptr;
			}

			static std::string map_name(const std::string& key_name,
				                        const std::string& value_name) {
				return "map<" + key_name + "," + value_name + "*>";
			}
	};


	template<class KEY, class VALUE>
	class ConstPtrMap {
		public:
			typedef std::map<KEY,const VALUE*> MapType;
			typedef KEY KeyType;
			typedef VALUE ValueType;
			typedef ClassConstPtr<VALUE> ValuePasser;

			static const VALUE* get_value_ptr(const VALUE* val_ptr) {
				return val_ptr;
			}

			static std::string map_name(const std::string& key_name,
				                        const std::string& value_name) {
				return "map<" + key_name + ",const " + value_name + "*>";
			}
	};


 	/////////////////////////////////////
	// Map Creator
	/////////////////////////////////////

	template<class MapKind>
	class MapCreator {
		public:
			typedef typename MapKind::KeyType KeyType;
			typedef typename MapKind::ValueType ValueType;
			typedef typename MapKind::MapType MapType;
			typedef typename MapKind::ValuePasser ValuePasser;

			typedef TypedValueMap<KeyType,ValueType> ValueMap;
			typedef typename ValueMap::MapItem MapItem;

			static MapType* create(const ValueMap& pair_list) 
			{
				std::unique_ptr<MapType> m = std::make_unique<MapType>();

				typename ValueMap::const_iterator i;
				for (i=pair_list.begin(); i!=pair_list.end(); ++i) {
					const MapItem& item = *i;

					// check for duplicate keys
					if (m->find(*item.key) != m->end()) {
						throw Error("While constructing map - the key "
							+ make_value(item.key)->to_string() 
							+ " appears more than once");
					}

					(*m)[*item.key] = ValuePasser::typed_pass(item.value);
				}

				return m.release();
			}
	};


	/////////////////////////////////////
	// Map Output Function
	/////////////////////////////////////

	template<class MapKind>
	class MapOutput {
		public:
			typedef typename MapKind::KeyType KeyType;
			typedef typename MapKind::ValueType ValueType;
			typedef typename MapKind::MapType MapType;

			typedef TypedValueMap<KeyType,ValueType> ValueMap;
			typedef typename ValueMap::MapItem MapItem;

			static ValueList sub_objects(const MapType& map)
			{
				ValueMap val_map;
				typename MapType::const_iterator i;
				for (i=map.begin(); i!=map.end(); ++i) {
					const KeyType& key = i->first;
					const ValueType* val_ptr = MapKind::get_value_ptr(i->second);
					val_map.append_copy(key,val_ptr);
				}

				ValueList vl;
				vl << Val(val_map);
				return vl;
			}
	};


	/////////////////////////////////////
	// RegistrationCommand
	/////////////////////////////////////

	template<class MapKind>
	class MapClassRegCommand : public ClassRegCommand<typename MapKind::MapType> {
		public:
			typedef typename MapKind::KeyType KeyType;
			typedef typename MapKind::ValueType ValueType;
			typedef typename MapKind::MapType MapType;

			MapClassRegCommand() 
				: ClassRegCommand<MapType>(typeid(KeyType),typeid(ValueType)) {}

			virtual std::string type_name() const {
				return MapKind::map_name(xparam_or_cpp_name(typeid(KeyType)),
										 xparam_or_cpp_name(typeid(ValueType)));
			}
	};


	template<class MapKind>
	class MapRegCommand : public CommonRegCommand {
		public:
			typedef typename MapKind::KeyType KeyType;
			typedef typename MapKind::ValueType ValueType;
			typedef typename MapKind::MapType MapType;

			MapRegCommand() : CommonRegCommand(typeid(KeyType),typeid(ValueType)) {}
			
			virtual void do_registration() const 
			{
				// register TypedValueMap
				register_typed_value_map<KeyType,ValueType>();

				// register class
				param_class<MapType>(new MapClassRegCommand<MapKind>());

				// register empty ctor
				param_ctor(TypeTag<MapType>());

				// register creator from TypedValueMap<KeyType,ValueType>
				typedef MapCreator<MapKind> Creator;
				param_weighted_creator(TypeTag<MapType>(),
					                   TypeTag<Creator>(),
							           ConstRef< TypedValueMap<KeyType,ValueType> >("pair_list"),
									   CONV_STANDARD);

				// register output
				typedef MapOutput<MapKind> OutputFunc;
				param_output<MapType,OutputFunc>();
			}

			virtual std::string description() const {
				return "map type - " 
					   + MapKind::map_name(xparam_or_cpp_name(typeid(KeyType)),
					                       xparam_or_cpp_name(typeid(ValueType)));
			}
	};

	/////////////////////////////////////
	// User registration API
	/////////////////////////////////////

	template<class MapKind>
		class RegMap {
		public:
			RegMap()
			{
				Handle<RegistrationCommand> command(new MapRegCommand<MapKind>);
				registration_scheduler().add_command(command);
			}
		};

	template<class KEY, class VALUE>	
		class param_map : private RegMap< ByValMap<KEY,VALUE> > {};

	template<class KEY, class VALUE>	
		class param_ptr_map : private RegMap< PtrMap<KEY,VALUE> > {};

	template<class KEY, class VALUE>	
		class param_const_ptr_map : private RegMap< ConstPtrMap<KEY,VALUE> > {};

} // namespace xParam_internal

#endif // XPARAM_REG_MAP_H
