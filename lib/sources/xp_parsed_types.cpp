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

#include <string>
#include "../xparam/xp_parsed_types.h"
#include "../xparam/xp_value_management.h"
#include "../src_include/xpv_tentative.h"
#include "../xparam/xpv_const_registry.h"

using namespace std;

namespace xParam_internal {

	//////////////////////////////////////////////////////////////////////////
	// ParsedCompoundValue
	//////////////////////////////////////////////////////////////////////////

	ParsedCompoundValue::ParsedCompoundValue(const std::string& type_name, 
											const ParsedValueList& sub_values) :
	m_type_name(type_name), m_sub_values(sub_values)
	{}
	
	Handle<Value> ParsedCompoundValue::get_value(bool flexible) const 
	{
		ValueList args;
		ParsedValueList::const_iterator i;
		for (i=m_sub_values.begin(); i!=m_sub_values.end(); ++i) {
			Handle<Value> val = (*i)->get_value(flexible);
			args.push_back(val);
		}

		return create_value(m_type_name,args,flexible);
	}

	//////////////////////////////////////////////////////////////////////////
	// ParsedListValue
	//////////////////////////////////////////////////////////////////////////
	ParsedListValue::ParsedListValue(const ParsedValueList& elements) :
	m_elements(elements)
	{}
		
	Handle<Value> ParsedListValue::get_value(bool flexible) const
	{
		Handle<ValueList> val_list(new ValueList);

		ParsedValueList::const_iterator i;
		for (i=m_elements.begin(); i!=m_elements.end(); ++i) {
			Handle<Value> val = (*i)->get_value(flexible);
			val_list->push_back(val);
		}

		return make_value(val_list);
	}


	//////////////////////////////////////////////////////////////////////////
	// ParsedMapValue
	//////////////////////////////////////////////////////////////////////////
	ParsedMapValue::ParsedMapValue(const ParsedPairList& elements) :
	m_elements(elements)
	{}
	
	Handle<Value> ParsedMapValue::get_value(bool flexible) const
	{
		Handle<ValueList> tuple_list(new ValueList);

		ParsedPairList::const_iterator i;
		for (i=m_elements.begin(); i!=m_elements.end(); ++i) {
			const ParsedPair& parsed_pair = *i;
			Handle<Value> key = parsed_pair.first->get_value(flexible);
			Handle<Value> value = parsed_pair.second->get_value(flexible);
			
			Handle<ValueTuple> tuple(new ValueTuple);
			tuple->push_back(key);
			tuple->push_back(value);
			Handle<Value> tuple_value = make_value(tuple);

			tuple_list->push_back(tuple_value);
		}

		return make_value(tuple_list);
	}


	//////////////////////////////////////////////////////////////////////////
	// ParsedBoolValue
	//////////////////////////////////////////////////////////////////////////
	ParsedBoolValue::ParsedBoolValue(bool b) : m_b(b) {}
		
	Handle<Value> ParsedBoolValue::get_value(bool flexible) const
	{
		return make_value_copy(m_b);
	}


	//////////////////////////////////////////////////////////////////////////
	// ParsedCharValue
	//////////////////////////////////////////////////////////////////////////
	ParsedCharValue::ParsedCharValue(char c) : m_c(c) {}

	Handle<Value> ParsedCharValue::get_value(bool flexible) const
	{
		return make_value_copy(m_c);
	}


	//////////////////////////////////////////////////////////////////////////
	// ParsedStringValue
	//////////////////////////////////////////////////////////////////////////
	ParsedStringValue::ParsedStringValue(const std::string& str) : m_str(str) {}
		
	Handle<Value> ParsedStringValue::get_value(bool flexible) const
	{
		return make_value_copy(m_str);
	}


	//////////////////////////////////////////////////////////////////////////
	// ParsedTentativeValue
	//////////////////////////////////////////////////////////////////////////
	ParsedTentativeValue::ParsedTentativeValue(const std::string& encoded_str)
		: m_encoded_str(encoded_str)
	{}
	
	Handle<Value> ParsedTentativeValue::get_value(bool flexible) const
	{
		// build TentativeValue
		TentativeValue tv(m_encoded_str);

		// check if this is a constant
		if (tv.type() == tentative_string) {
			std::string str = tv.string_value();
			if (const_registry().is_registered(str)) {
				return const_registry().value(str);
			}
		}

		// not a constant 
		if (flexible) {
			// return as tentative value
			return make_value_copy(tv);
		}
		else { // strict
			return tv.strictly_typed_value();
		}
	}


	//////////////////////////////////////////////////////////////////////////
	// ParsedRawBytesValue
	//////////////////////////////////////////////////////////////////////////
	ParsedRawBytesValue::ParsedRawBytesValue(const Handle<RawBytes>& raw_bytes)
		: m_raw_bytes(raw_bytes)
	{}	

	Handle<Value> ParsedRawBytesValue::get_value(bool flexible) const
	{
		return make_value(m_raw_bytes);
	}

} // namespace xParam_internal

