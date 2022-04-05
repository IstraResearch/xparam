#ifndef XPARAM_PARSED_TYPES_H
#define XPARAM_PARSED_TYPES_H

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
 * interface to the parser module
 */

#include <iosfwd>
#include <string>
#include <vector>
#include <map>
#include "xp_config.h"
#include "xp_value_source.h"
#include "xp_raw_bytes.h"

namespace xParam_internal {

	//////////////////////////////////////////////////////////////////////////
	// ParsedValue
	//////////////////////////////////////////////////////////////////////////

	class ParsedValue : public ValueSource {
	public:
		virtual Handle<Value> get_value(bool flexible) const = 0;
	};


	//////////////////////////////////////////////////////////////////////////
	// Typedefs
	//////////////////////////////////////////////////////////////////////////
	typedef std::vector< Handle<ParsedValue> > ParsedValueList;
	typedef std::pair< Handle<ParsedValue>, Handle<ParsedValue> > ParsedPair;
	typedef std::vector<ParsedPair> ParsedPairList;


	//////////////////////////////////////////////////////////////////////////
	// ParsedCompoundValue
	//////////////////////////////////////////////////////////////////////////
	class ParsedCompoundValue : public ParsedValue {
	public:
		ParsedCompoundValue(const std::string& type_name, 
				            const ParsedValueList& sub_values);
		virtual Handle<Value> get_value(bool flexible) const;
	private:
		std::string m_type_name;
		ParsedValueList m_sub_values;
	};


	//////////////////////////////////////////////////////////////////////////
	// ParsedListValue
	//////////////////////////////////////////////////////////////////////////
	class ParsedListValue : public ParsedValue {
	public:
		explicit ParsedListValue(const ParsedValueList& elements);
		virtual Handle<Value> get_value(bool flexible) const;
	private:
		ParsedValueList m_elements;
	};


	//////////////////////////////////////////////////////////////////////////
	// ParsedMapValue
	//////////////////////////////////////////////////////////////////////////
	class ParsedMapValue : public ParsedValue {
	public:
		explicit ParsedMapValue(const ParsedPairList& elements);
		virtual Handle<Value> get_value(bool flexible) const;
	private:
		ParsedPairList m_elements;
	};


	//////////////////////////////////////////////////////////////////////////
	// ParsedBoolValue
	//////////////////////////////////////////////////////////////////////////
	class ParsedBoolValue : public ParsedValue {
	public:
		explicit ParsedBoolValue(bool b);
		virtual Handle<Value> get_value(bool flexible) const;
	private:
		bool m_b;
	};


	//////////////////////////////////////////////////////////////////////////
	// ParsedCharValue
	//////////////////////////////////////////////////////////////////////////
	class ParsedCharValue : public ParsedValue {
	public:
		explicit ParsedCharValue(char c);
		virtual Handle<Value> get_value(bool flexible) const;
	private:
		char m_c;
	};


	//////////////////////////////////////////////////////////////////////////
	// ParsedStringValue
	//////////////////////////////////////////////////////////////////////////
	class ParsedStringValue : public ParsedValue {
	public:
		explicit ParsedStringValue(const std::string& str);
		virtual Handle<Value> get_value(bool flexible) const;
	private:
		std::string m_str;
	};


	//////////////////////////////////////////////////////////////////////////
	// ParsedTentativeValue
	//////////////////////////////////////////////////////////////////////////
	class ParsedTentativeValue : public ParsedValue {
	public:
		explicit ParsedTentativeValue(const std::string& encoded_str);
		virtual Handle<Value> get_value(bool flexible) const;
	private:
		std::string m_encoded_str;
	};

	//////////////////////////////////////////////////////////////////////////
	// ParsedRawBytesValue
	//////////////////////////////////////////////////////////////////////////
	class ParsedRawBytesValue : public ParsedValue {
	public:
		explicit ParsedRawBytesValue(const Handle<RawBytes>& raw_bytes);
		virtual Handle<Value> get_value(bool flexible) const;
	private:
		Handle<RawBytes> m_raw_bytes;
	};


} // namespace xParam_internal

#endif // XPARAM_PARSED_TYPES_H
