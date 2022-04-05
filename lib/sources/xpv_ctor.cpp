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
#include "../xparam/xpv_ctor.h"
#include "../xparam/xp_value_list.h"
#include "../xparam/xpv_registry.h"
#include "../src_include/xp_sstream.h"

using namespace std;

namespace xParam_internal {

	vector<const type_info*> Ctor::arg_types() const
	{
		const int n = n_args();
		vector<const type_info*> types(n);
		for (int i=0; i<n; ++i)
			types[i] = &arg_defs()[i].type();
		return types;
	}

	string Ctor::description() const
	{
		Oss oss;
		oss << type_registry().type(constructed_type()).name() << '(';
		for (int i=0; i<n_args(); ++i) {
			if (i>0)
				oss << ", ";
			oss << type_registry().type(arg_defs()[i].type()).name() << " ";
			oss << arg_defs()[i].name();
		}
		oss << ')';
		return oss.str();
	}

	bool Ctor::equivalent(const Handle<Ctor>& other) const
	{
		if (constructed_type() != other->constructed_type())
			return false;

		std::vector<const std::type_info*> args = arg_types();
		std::vector<const std::type_info*> other_args = other->arg_types();
		if (args.size() != other_args.size())
			return false;

		std::vector<const std::type_info*>::const_iterator i,j;
		for (i=args.begin(), j=other_args.begin(); i!=args.end(); ++i,++j) {
			if ((**i) != (**j))
				return false;
		}

		return true;
	}


	// returns true iff ctor can be used on 'args'.
	// if exact_match is true, then no conversions are allowed,
	// otherwise, flexible determines whether the conversions should be flexible or strict
	bool Ctor::can_create(const ValueList& args, bool exact_match, bool flexible) const
	{
		if (args.size() != m_arg_defs.size())
			return false;

		ValueList::const_iterator iArg;
		vector<ArgDef>::const_iterator iArgDef;

		if (exact_match) {
			for (iArg=args.begin(), iArgDef=m_arg_defs.begin();	iArg!=args.end(); ++iArg, ++iArgDef) {
				if ((*iArg)->static_type_info() != iArgDef->type())
					return false;
			}
		}
		else { // conversions are allowed
			for (iArg=args.begin(), iArgDef=m_arg_defs.begin();	iArg!=args.end(); ++iArg, ++iArgDef) {
				if (!(*iArg)->can_convert_to(iArgDef->type(),flexible))
					return false;
			}
		}

		return true;
	}

	Handle<Value> Ctor::create_with_conversions(const ValueList& args, bool flexible) const
	{
		if (args.size() != m_arg_defs.size())
			throw Error("Error in ctor - wrong number of arguments");

		ValueList converted_args;

		ValueList::const_iterator iArg;
		vector<ArgDef>::const_iterator iArgDef;
		for (iArg=args.begin(), iArgDef=m_arg_defs.begin();	iArg!=args.end(); ++iArg, ++iArgDef) {
			const Handle<Value>& arg = *iArg;
			const type_info& target_type = iArgDef->type();
			converted_args.push_back( arg->convert_to(target_type,flexible) );
		}

		return create(converted_args);
	}


	Handle<Value> Ctor::create(const ValueList& args) const 
	{
		Handle<Value> val;
		try {
			val = actual_create(args);
		}
		catch (std::exception& ex) {
			throw Error("Error in ctor " + description() + " - " + ex.what());
		}
		catch (...) {
			throw Error("Error in ctor " + description());
		}
		
		return val;
	}


} // namespace xParam_internal
