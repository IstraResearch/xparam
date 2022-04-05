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
#include <assert.h>
#include <iostream>
#include "../xparam/xp_error.h"
#include "../xparam/xp_value_list.h"
#include "../xparam/xpv_type.h"
#include "../xparam/xpv_ctor.h"
#include "../xparam/xpv_iconv_imp.h"
#include "../src_include/xpv_conversions.h"
#include "../xparam/xpv_registry.h"
#include "../xparam/xpv_const_registry.h"
#include "../xparam/xp_value_management.h"
#include "../xparam/xp_parser.h"
#include "../xparam/xpv_untyped_null.h"
#include "../src_include/xp_sstream.h"
#include "../src_include/TypeNameLexer.hpp"
#include "../src_include/TypeNameParser.hpp"

using namespace std;

namespace xParam_internal {

	Type::Type(const std::type_info& ti, const string& name, bool is_abstract) 
		: m_type_info(ti), m_name(canonical_form(name)), m_is_abstract(is_abstract)
	{
	}

	const std::type_info& Type::type_info() const 
	{ 
		return m_type_info; 
	}

	string Type::name() const 
	{ 
		return m_name; 
	}

	std::vector<WeightedConvSource> Type::get_conversion_sources() const
	{
		return m_conversion_sources;
	}

	bool Type::is_ancestor_of(const std::type_info& t) const
	{
		return (m_descendants.find(&t) != m_descendants.end());
	}

	string Type::help() const
	{
		Oss oss;
		oss << "Help for " 
			<< (m_is_abstract ? "abstract" : "concrete")
			<< " type " 
			<< name()
			<< ":" << endl;

		if (!m_is_abstract && m_output_function.empty()) {
			oss << "* No output function" << endl;
		}

		if (!m_iconv_map.empty()) {
			oss << endl << "* Base Types:" << endl;
			IConvMap::const_iterator i;
			for (i=m_iconv_map.begin(); i!=m_iconv_map.end(); ++i) {
				if (i->second->is_atomic())
					oss << '\t' << xparam_name(*i->first) << endl;
			}
		}

		if (!m_descendants.empty()) {
			oss << endl << "* Derived Types:" << endl;

			DescendantSet::const_iterator i;
			for (i=m_descendants.begin(); i!=m_descendants.end(); ++i)
				oss << '\t' << xparam_name(**i) << endl;
		}

		CtorList ctors;
		CtorList::const_iterator iCtor;
		for (iCtor=m_ctors.begin(); iCtor!=m_ctors.end(); ++iCtor) {
			const Handle<Ctor>& ctor = *iCtor;
			
			if (ctor->n_args() == 1) {
				const std::type_info* arg_type = ctor->arg_types().front();

				// don't output copy ctor
				if (*arg_type == type_info())
					continue;
				
				// don't output constructors that are also conversions
				bool is_conversion = false;
				vector<WeightedConvSource>::const_iterator i;
				for (i=m_conversion_sources.begin(); i!=m_conversion_sources.end(); ++i) {
					const std::type_info* source = i->first;
					if (*source == *arg_type) {
						is_conversion = true;
						break;
					}
				}
				if (is_conversion)
					continue;
			}

			ctors.push_back(ctor);
		}

		if (!ctors.empty()) {
			oss << endl << "* Constructors:" << endl;
			CtorList::const_iterator i;
			for (i=ctors.begin(); i!=ctors.end(); ++i) {
				oss << '\t' << (*i)->description() << endl;
			}
		}

		vector<WeightedConvSource> conversion_sources;
		vector<WeightedConvSource>::const_iterator iConv;
		for (iConv=m_conversion_sources.begin(); iConv!=m_conversion_sources.end(); ++iConv) {
			const WeightedConvSource& conv = *iConv;
			const std::type_info* source = conv.first;

			// don't show conversion from untyped null
			if (*source == typeid(UntypedNull))
				continue;

			// don't show conversions from derived types
			if (is_ancestor_of(*source))
				continue;

			conversion_sources.push_back(conv);
		}

		if (!conversion_sources.empty()) {
			oss << endl << "* Conversions from: " << endl;
			vector<WeightedConvSource>::const_iterator i;
			for (i=conversion_sources.begin(); i!=conversion_sources.end(); ++i)
				oss << '\t' << (*i) << endl;
		}

		if (!m_constant_names.empty()) {
			oss << endl << "* Constants: " << endl;
			oss << '\t';
			vector<string>::const_iterator i;
			for (i=m_constant_names.begin(); i!=m_constant_names.end(); ++i) {
				if (i!=m_constant_names.begin())
					oss << ", ";
				oss << (*i);
			}
			oss << endl;
		}

		return oss.str();
	}

	Handle<Value> Type::create(const ValueList& args, bool flexible) const 
	{
		if (flexible)
			return create_flexible(args);
		else
			return create_strict(args);
	}


	Handle<Value> Type::create_atomically_from(const Handle<Value>& val) const
	{
		CtorList::const_iterator i;
		for (i=m_ctors.begin(); i!=m_ctors.end(); ++i) {
			if ((*i)->n_args() == 1) {
				const std::type_info& arg_type = (*i)->arg_defs().front().type();
				if (arg_type == val->static_type_info())
					break;
			}
		}
		assert(i!=m_ctors.end()); // we should have found a suitable conversion ctor

		ValueList args;
		args.push_back(val);
		return (*i)->create(args);
	}


	Handle<Value> Type::create_from_descendant(const Handle<Value> val) const
	{
		assert(is_ancestor_of(val->static_type_info()));
		return create_atomically_from(val);
	}


	void Type::output(std::ostream& os, const Value& val) const 
	{
		assert(type_info() == val.dynamic_type_info());
		if (val.empty()) {
			os << name() << "(NULL)";
			return;
		}

		if (m_output_function.empty()) {
			os << name() << "(NO OUTPUT FUNCTION)";
			return;
		}

		Handle<Value> downcast_value = downcast(val.get_handle());

		try {
			m_output_function->output(os,*downcast_value);
		}
		catch (std::exception& ex) {
			throw Error("Error while printing value of type " 
				+ xparam_name(downcast_value->static_type_info())
				+ " - " + ex.what());
		}
		catch (...) {
			throw Error("Error while printing value of type " 
				+ xparam_name(downcast_value->static_type_info()));
		}
	}

	void* Type::get_owned_copy(const Value& val) const
	{
		assert(!m_copier.empty());
		assert(type_info() == val.dynamic_type_info());

		if (type_info() == val.static_type_info()) {
			return m_copier->copy(val);
		}
		else {
			Handle<Value> downcast_value = downcast(val.get_handle());
			void *copy_ptr = m_copier->copy(*downcast_value);

			// upcast
			const std::type_info* t = &(val.static_type_info());
			IConvMap::const_iterator iconv_iter = m_iconv_map.find(t);
			assert(iconv_iter != m_iconv_map.end());
			Handle<IConv> iconv = iconv_iter->second;
			assert(!iconv.empty());
			return iconv->upcast(copy_ptr);
		}
	}

	void Type::destroy(const Handle<Value>& val) const
	{
		assert(!m_dtor.empty());
		assert(type_info() == val->dynamic_type_info());
		Handle<Value> downcast_value = downcast(val->get_handle());
		m_dtor->destroy(downcast_value);
	}

	
	void Type::reg_ctor(const Handle<Ctor>& ctor) 
	{
		assert(ctor->constructed_type() == type_info());

		// ignore registration if an equivalent ctor is already registered
		CtorList::const_iterator i;
		for (i=m_ctors.begin(); i!=m_ctors.end(); ++i) {
			if (ctor->equivalent(*i))
				return;
		}

		m_ctors.push_back(ctor);
	}
				
	void Type::reg_output_function(const Handle<OutputFunction>& output_function) 
	{
		assert(output_function->type() == type_info());

		// ignore double registration (we don't check it's the same function)
		if (m_output_function.empty())
			m_output_function = output_function;
	}
	
	void Type::reg_copier(const Handle<Copier>& copier) 
	{
		assert(copier->type() == type_info());

		// ignore double registration (we don't check it's the same function)
		if (m_copier.empty())
			m_copier = copier;
	}

	void Type::reg_dtor(const Handle<Dtor>& dtor)
	{
		assert(dtor->destructed_type() == type_info());

		// ignore double registration (we don't check it's the same function)
		if (m_dtor.empty())
			m_dtor = dtor;
	}

	void Type::reg_constant_name(const string& constant_name)
	{
		assert(const_registry().is_registered(constant_name));
		assert(const_registry().type(constant_name).type_info() == type_info());

		// ignore double registration (we don't check it's the same value)
		if (find(m_constant_names.begin(),m_constant_names.end(),constant_name)
			== m_constant_names.end()) {
			m_constant_names.push_back(constant_name);
		}
	}
			
				
	// update all inheritance information in different Type objects that
	// is affected by the addition of the direct relationship in 'iconv'
	void Type::reg_iconv(const Handle<IConv>& iconv) 
	{
		assert(iconv->descendant() == type_info());

		try {
			TypeRegistry& registry = type_registry_registration_access();

			// ignore double registration
			Type& a_type = registry.type(iconv->ancestor());
			if (a_type.m_descendants.find(&iconv->descendant()) 
				!= a_type.m_descendants.end()) {
				return;
			}

			// A <-> D (A=iconv.ancestor(), D=iconv.descendant())
			reg_inheritance_connection(iconv);

			// A <-> descendants(D)
			DescendantSet::const_iterator iD;
			for (iD=m_descendants.begin(); iD!=m_descendants.end(); ++iD) {
				Type& d_type = registry.type(**iD);
				Handle<IConv> bottom_iconv = d_type.m_iconv_map[&type_info()];
				assert(!bottom_iconv.empty());

				vector< Handle<IConv> > conv_list;
				conv_list.push_back(iconv);
				conv_list.push_back(bottom_iconv);
				Handle<IConv> composite_iconv( new CompositeIConv(conv_list) );

				reg_inheritance_connection(composite_iconv);
			}

			// ancestors(A) <-> D
			IConvMap::const_iterator iA;
			for (iA=a_type.m_iconv_map.begin(); iA!=a_type.m_iconv_map.end(); ++iA) {
				vector< Handle<IConv> > conv_list;
				conv_list.push_back(iA->second);
				conv_list.push_back(iconv);
				Handle<IConv> composite_iconv( new CompositeIConv(conv_list) );

				reg_inheritance_connection(composite_iconv);
			}

			// ancestors(A) <-> descendants(D)
			for (iD=m_descendants.begin(); iD!=m_descendants.end(); ++iD) {
				Type& d_type = registry.type(**iD);
				Handle<IConv> bottom_iconv = d_type.m_iconv_map[&type_info()];
				assert(!bottom_iconv.empty());

				for (iA=a_type.m_iconv_map.begin(); iA!=a_type.m_iconv_map.end(); ++iA) {
					vector< Handle<IConv> > conv_list;
					conv_list.push_back(iA->second);
					conv_list.push_back(iconv);
					conv_list.push_back(bottom_iconv);
					Handle<IConv> composite_iconv( new CompositeIConv(conv_list) );
					
					reg_inheritance_connection(composite_iconv);
				}
			}
		}
		catch (Error) {
			assert(false);
		}
	}

	void Type::reg_conversion_source(const std::type_info& source, ScalarConvWeight w)
	{
		// ignore double registration (but check for conflicting weights)
		std::vector<WeightedConvSource>::const_iterator i;
		for (i=m_conversion_sources.begin(); i!=m_conversion_sources.end(); ++i) {
			const WeightedConvSource& wcs = *i;
			if (*wcs.first == source) {
				if (wcs.second != w) {
					assert(type_registry_registration_access().is_registered(source));
					Oss oss;
					oss << "Registration conflict: Tried to register conversion " 
						<< xparam_name(source) << " -> " << name() 
						<< " with weight " << w 
						<< ". It is already registered with weight " 
						<< wcs.second;
					throw Error(oss.str());
				}
				return;
			}
		}

		m_conversion_sources.push_back( WeightedConvSource(&source,w) );
	}

	Handle<Value> Type::create_flexible(const ValueList& args) const 
	{
		vector< pair< Handle<Ctor>,vector<ConvPath> > > best_matches 
			= find_best_matches(args,m_ctors);

		if (best_matches.empty())
			throw Error("no ctor found for " + err_ctor_call(args));
		if (best_matches.size() > 1) {
			Oss oss;
			oss << "More than one ctor found for " << err_ctor_call(args) 
				<< ". Possible ctors are:" << endl;

			vector< pair< Handle<Ctor>,vector<ConvPath> > >::const_iterator i;
			for (i=best_matches.begin(); i!=best_matches.end(); ++i)
				oss << '\t' << (*i).first->description() << endl;
			throw Error(oss.str());
		}

		Handle<Ctor> ctor = best_matches.front().first;
		vector<ConvPath> conversion_paths = best_matches.front().second;
		assert(conversion_paths.size() == args.size());

		ValueList converted_args;
		ValueList::const_iterator iArg;
		vector<ConvPath>::const_iterator iConvPath;
		for (iArg=args.begin(), iConvPath=conversion_paths.begin(); 
			 iArg!=args.end(); 
			 ++iArg, ++iConvPath) 
			converted_args.push_back( convert_along_path(*iArg,*iConvPath) );

		return ctor->create(converted_args);
	}


	// use first match (ignore ambiguities for now)
	Handle<Value> Type::create_strict(const ValueList& args) const 
	{
		CtorList::const_iterator iCtor;
		for (iCtor=m_ctors.begin(); iCtor!=m_ctors.end(); ++iCtor) {
			const Handle<Ctor>& ctor = *iCtor;

			if (ctor->can_create(args,false,false))
				return ctor->create_with_conversions(args,false);
		}

		throw Error("no ctor found (strict conversions) for " + err_ctor_call(args));
	}


	// Adjusts whitespace in type_name to a canonical form, which
	// can later be used when matching user's input.
	// For example: 
	//		vector< int, const		B*> 
	// becomes 
	//		vector<int,const B*>
	// 
	// Throws an exception if type_name cannot be parsed as a type name.
	string Type::canonical_form(const string& type_name)
	{
		Iss iss(type_name);
		TypeNameLexer lexer(iss);
		TypeNameParser parser(lexer);
		string tn;
		try {
			tn = parser.type_name();
		}
		catch(...) {
			throw Error("Tried to register illegal type-name: " 
						+ type_name);
		}
		return tn;
	}

	// update only the two Type objects referenced in 'iconv' to show 
	// an inheritance relationship between them (with iconv as the converter).
	void Type::reg_inheritance_connection(const Handle<IConv>& iconv)
	{
		const std::type_info& A = iconv->ancestor();
		const std::type_info& D = iconv->descendant();

		TypeRegistry& registry = type_registry_registration_access();

		// update A
		Type& a_type = registry.type(A);
		a_type.m_descendants.insert(&D);

		// update D
		Type& d_type = registry.type(D);
		d_type.m_iconv_map[&A] = iconv;
	}

	string Type::err_ctor_call(const ValueList& args) const
	{
		Oss oss;
		oss << name() << "(";
		ValueList::const_iterator i;
		for (i=args.begin(); i!=args.end(); ++i) {
			if (i!=args.begin())
				oss << ", ";
			oss << (*i)->static_type().name() << " ";
			(*i)->output(oss);
		}
		oss << ")";
		return oss.str();
	}

	Handle<Value> Type::downcast(const Handle<Value>& val) const
	{
		if (type_info() == val->static_type_info())
			return val;

		const std::type_info* t = &val->static_type_info();
		IConvMap::const_iterator iconv_iter = m_iconv_map.find(t);
		assert(iconv_iter != m_iconv_map.end());
		Handle<IConv> iconv = iconv_iter->second;
		assert(!iconv.empty());
		return iconv->downcast(*val);
	}

} // namespace xParam_internal

