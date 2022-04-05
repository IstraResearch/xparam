#ifndef XPARAM_TYPE_H
#define XPARAM_TYPE_H

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
 * class Type provides information about a registered type and 
 * can manipulate on objects of that type (creation, output, copying)
 */

#include <iosfwd>
#include <typeinfo>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <assert.h>
#include "xp_config.h"
#include "xp_handle.h"
#include "xp_type_compare.h"
#include "xpv_convweight.h"
#include "xpv_iconv.h"
#include "xpv_output.h"
#include "xpv_copier.h"
#include "xpv_dtor.h"

namespace xParam_internal {

	class Value;
	class ValueList;
	class Ctor;

	typedef std::map<const std::type_info*, Handle<IConv>, TypeInfoCmp> IConvMap;
	typedef std::set<const std::type_info*, TypeInfoCmp> DescendantSet;

	class Type {
		public:
			Type(const std::type_info& ti, const std::string& name, bool is_abstract);
			
			////////////////////////
			// queries
			////////////////////////
			const std::type_info& type_info() const;
			std::string name() const;
		
			std::vector<WeightedConvSource> get_conversion_sources() const;

			bool is_ancestor_of(const std::type_info& t) const;

			////////////////////////
			// help
			////////////////////////
			std::string help() const;

			////////////////////////
			// value manipulation
			////////////////////////
			
			Handle<Value> create(const ValueList& args, bool flexible) const;

			// use a ctor to create a value from val without any conversions
			// if there isn't one, we assert().
			Handle<Value> create_atomically_from(const Handle<Value>& val) const;

			// use an inheritance conversion (IConv) to create a value from val.
			// asserts that val is a descendant of this type.
			Handle<Value> create_from_descendant(const Handle<Value> val) const;
			
			// when this method is called we should have 
			// this->type_info() == val.dynamic_type_info()
			void output(std::ostream& os, const Value& val) const;
			
			// when this method is called we should have 
			// this->type_info() == val.dynamic_type_info()
			// 
			// The returned void* can be reinterpret_cast back to T*
			// where T is the static type of 'val'.
			void* get_owned_copy(const Value& val) const;
			
			// when this method is called we should have 
			// this->type_info() == val.dynamic_type_info()
			void destroy(const Handle<Value>& val) const;

			////////////////////////
			// registration
			////////////////////////
			
			void reg_ctor(const Handle<Ctor>& ctor);
			void reg_output_function(const Handle<OutputFunction>& output_function);
			void reg_copier(const Handle<Copier>& copier);
			void reg_dtor(const Handle<Dtor>& dtor);
			void reg_constant_name(const std::string& constant_name);

			// iconv must satisfy:
			// iconv->descendant() == type_info()
			void reg_iconv(const Handle<IConv>& iconv);
			
			void reg_conversion_source(const std::type_info& source, ScalarConvWeight w);

		private:
			Handle<Value> create_flexible(const ValueList& args) const;
			Handle<Value> create_strict(const ValueList& args) const;

			static std::string canonical_form(const std::string& type_name);
			static void reg_inheritance_connection(const Handle<IConv>& iconv);
			std::string err_ctor_call(const ValueList& args) const;
			Handle<Value> downcast(const Handle<Value>& val) const;

			const std::type_info& m_type_info;
			std::string m_name;
			bool m_is_abstract;
			
			CtorList m_ctors;
			Handle<OutputFunction> m_output_function;
			Handle<Copier> m_copier;
			Handle<Dtor> m_dtor;

			// a map from ALL known ancestors to an IConv between them and this type
			IConvMap m_iconv_map;
			
			// a set of ALL known descendants
			DescendantSet m_descendants;

			std::vector<WeightedConvSource> m_conversion_sources;

			// names of all registered constants of this type
			std::vector<std::string> m_constant_names;
	};
	

} // namespace xParam_internal

#endif // XPARAM_TYPE_H
