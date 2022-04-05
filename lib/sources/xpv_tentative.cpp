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
#include "../xparam/xp_error.h"
#include "../src_include/xpv_tentative.h"
#include "../xparam/xp_value_management.h"
#include "../xparam/xpv_type.h"
#include "../src_include/xp_sstream.h"

using namespace std;

namespace xParam_internal {

	TentativeValue::TentativeValue(const string& encoded_value) 
	{
		const int n = encoded_value.size();
		assert(n >= 1);
		switch (encoded_value[0]) {
			case 'I': 
				assert(encoded_value.size() > 4);
				m_type = tentative_int; 
				m_str = encoded_value.substr(4,n-4);
				switch (encoded_value[1]) {
					case 'D': m_base = 10; break;
					case 'H': m_base = 16; break;
					case 'O': m_base = 8; break;
					case 'B': m_base = 2; break;
					default: assert(false);
				}
				m_unsigned = (encoded_value[2] == 'U');
				m_long = (encoded_value[3] == 'L');
				break;
			case 'R': 
				m_type = tentative_real; 
				m_str = encoded_value.substr(1,n-1);
				{
					assert(!m_str.empty());
					char c = m_str[m_str.size()-1];
					switch(c) {
					case 'f':
					case 'F':
						m_real_length = trl_float;
						break;
					case 'l':
					case 'L':
						m_real_length = trl_long_double;
						break;
					default:
						m_real_length = trl_double;
					}
				}
				break;
			case 'S': 
				m_str = encoded_value.substr(1,n-1);
				m_type = tentative_string;
				break;
			default: 
				assert(false);
		}

		// Check for strings that have the syntax of integers, but 
		// are too large to fit in any integral type.
		// These values are treated as tentative strings.
		if (m_type == tentative_int) {
			try {
				parse_abs_value();
			}
			catch(...) {
				m_type = tentative_string;
			}
		}
	}

	ScalarConvWeight TentativeValue::conversion_weight(const type_info& target) const
	{
		if (target == typeid(char)) {
			if (m_str.size() > 1)
				return CONV_IMPOSSIBLE;
			else // single character
				return ScalarConvWeight(CONV_TENTATIVE)*2;
		}
		
		if (target == typeid(string))
			return ScalarConvWeight(CONV_TENTATIVE)*3;

		switch (m_type) {
		case tentative_int:
			return int_conversion_weight(target);
		case tentative_real:
			return real_conversion_weight(target);
		default:
			return CONV_IMPOSSIBLE;
		}
	}

	int TentativeValue::as_int() const
	{
		assert(conversion_weight(typeid(int)) != CONV_IMPOSSIBLE);
		bool negative = parse_sign();
		unsigned long abs_value = parse_abs_value();
		return negative ? -abs_value : abs_value;
	}

	unsigned int TentativeValue::as_uint() const
	{
		assert(conversion_weight(typeid(unsigned int)) != CONV_IMPOSSIBLE);
		return parse_abs_value();
	}

	long TentativeValue::as_long() const
	{
		assert(conversion_weight(typeid(long)) != CONV_IMPOSSIBLE);
		bool negative = parse_sign();
		unsigned long abs_value = parse_abs_value();		
		return negative ? -abs_value : abs_value;
	}

	unsigned long TentativeValue::as_ulong() const
	{
		assert(conversion_weight(typeid(unsigned long)) != CONV_IMPOSSIBLE);
		return parse_abs_value();
	}

	LONG_LONG TentativeValue::as_longlong() const
	{
		assert(conversion_weight(typeid(LONG_LONG)) != CONV_IMPOSSIBLE);
		bool negative = parse_sign();
		ULONG_LONG abs_value = parse_abs_value();		
		return negative ? -abs_value : abs_value;
	}

	ULONG_LONG TentativeValue::as_ulonglong() const
	{
		assert(conversion_weight(typeid(ULONG_LONG)) != CONV_IMPOSSIBLE);
		return parse_abs_value();
	}

	double TentativeValue::as_double() const
	{
		assert(conversion_weight(typeid(double)) != CONV_IMPOSSIBLE);
		return atof(m_str.c_str());
	}

	float TentativeValue::as_float() const
	{
		assert(conversion_weight(typeid(float)) != CONV_IMPOSSIBLE);
		return atof(m_str.c_str()); // atof will stop before trailing 'f'
	}

	LONG_DOUBLE TentativeValue::as_long_double() const
	{
		assert(conversion_weight(typeid(LONG_DOUBLE)) != CONV_IMPOSSIBLE);
		Iss iss(m_str.c_str());
		LONG_DOUBLE ld;
		iss >> ld; // input will stop before trailing 'L'
		return ld;
	}

	char TentativeValue::as_char() const
	{
		assert(conversion_weight(typeid(char)) != CONV_IMPOSSIBLE);
		return m_str[0];
	}

	string TentativeValue::as_string() const
	{
		return m_str;
	}

	Handle<Value> TentativeValue::convert_to(const std::type_info& target) const 
	{
		if (target == typeid(int))
			return make_value(Handle<int>(new int(as_int())));

		if (target == typeid(unsigned int))
			return make_value(Handle<unsigned int>(new unsigned int(as_uint())));

		if (target == typeid(long))
			return make_value(Handle<long>(new long(as_long())));

		if (target == typeid(unsigned long))
			return make_value(Handle<unsigned long>(new unsigned long(as_ulong())));

		if (target == typeid(LONG_LONG))
			return make_value(Handle<LONG_LONG>(new LONG_LONG(as_longlong())));

		if (target == typeid(ULONG_LONG))
			return make_value(Handle<ULONG_LONG>(new ULONG_LONG(as_ulonglong())));

		if (target == typeid(double))
			return make_value(Handle<double>(new double(as_double())));

		if (target == typeid(float))
			return make_value(Handle<float>(new float(as_float())));

		if (target == typeid(LONG_DOUBLE))
			return make_value(Handle<LONG_DOUBLE>(new LONG_DOUBLE(as_long_double())));

		if (target == typeid(char))
			return make_value(Handle<char>(new char(as_char())));

		if (target == typeid(string))
			return make_value(Handle<string>(new string(as_string())));

		assert(false);
		return Handle<Value>(); // silence compiler warnings
	}

	const type_info& TentativeValue::strict_type() const
	{
		switch(m_type) {
		case tentative_int:
			return *best_integral_match();

		case tentative_real:
			switch(m_real_length) {
			case trl_float:
				return typeid(float);
			case trl_double:
				return typeid(double);
			case trl_long_double:
				return typeid(LONG_DOUBLE);
			}
			assert(false);

		case tentative_string:
			return typeid(string);
		}
		assert(false);
		return typeid(void); // silence compiler warnings
	}


	Handle<Value> TentativeValue::strictly_typed_value() const
	{
		return convert_to(strict_type());
	}


	ScalarConvWeight TentativeValue::real_conversion_weight(const type_info& target) const
	{
		if ((target == typeid(LONG_DOUBLE)) && (m_real_length == trl_long_double))
			return CONV_TENTATIVE;

		if ((target == typeid(double)) && (m_real_length == trl_double))
			return CONV_TENTATIVE;

		if ((target == typeid(float)) && (m_real_length == trl_float))
			return CONV_TENTATIVE;

		return CONV_IMPOSSIBLE;
	}


	// here we check conversions to int,uint,long,ulong, LONG_LONG, ULONG_LONG.
	// Conversions to the integral type which is the best match for 
	// our value get CONV_TENTATIVE weight. Anything else gets
	// a weight of impossible.
	ScalarConvWeight TentativeValue::int_conversion_weight(const type_info& target) const
	{
		if (target == *best_integral_match())
			return CONV_TENTATIVE;
		return CONV_IMPOSSIBLE;
	}

	// Returns the first type from the list int,uint,long,ulong
	// ,LONG_LONG, ULONG_LONG
	// which is consistent with the given qualifiers, and 
	// can hold the integer's value.
	// Throws an exception if the integer can't fit into any of 
	// the above types.
	const type_info* TentativeValue::best_integral_match() const
	{
		assert(m_type == tentative_int);

		bool negative = parse_sign();
		ULONG_LONG abs_value = parse_abs_value();

		// check if value can match type int
		if (!m_unsigned && !m_long) {
			if (!negative && (abs_value <= max_int()))
				return &typeid(int);
			if (negative && (abs_value <= max_int()+1))
				return &typeid(int);
		}

		// check if value can match type uint
		if (!m_long) {
			if (!negative && (abs_value <= max_uint()))
				return &typeid(unsigned int);
		}
		
		// check if value can match type long
		if (!m_unsigned) {
			if (!negative && (abs_value <= max_long()))
				return &typeid(long);
			if (negative && (abs_value <= max_long()+1))
				return &typeid(long);
		}
		
		// check if value can match type ulong
		if (!negative && (abs_value <= max_ulong()))
			return &typeid(unsigned long);

		// check if value can match type LONG_LONG
		if (!m_unsigned) {
			if (!negative && (abs_value <= max_longlong()))
				return &typeid(LONG_LONG);
			if (negative && (abs_value <= max_longlong()+1))
				return &typeid(LONG_LONG);
		}
		
		// check if value can match type ULONG_LONG
		if (!negative && (abs_value <= max_ulonglong()))
			return &typeid(ULONG_LONG);

		// can't match any of above type throw exception
		throw Error("Received negative integer too big to fit in a long");
	}


	// returns true iff 'm_str' encodes a negative value
	bool TentativeValue::parse_sign() const 
	{
		assert(!m_str.empty());
		return m_str[0] == '-';
	}
		
	// Returns the absolute value of the integer encoded in 'm_str'.
	// The encoding may contain a sign, and may be decimal, hex (0x or 0X prefix)
	// or binary (0b or 0B prefix).
	// Throws error if encoded integer can't fit in an unsigned long
	ULONG_LONG TentativeValue::parse_abs_value() const
	{
		int n_suffix = 0;
		if (m_long) n_suffix++;
		if (m_unsigned) n_suffix++;

		const int n = m_str.size() - n_suffix;
		char c;
		int pos = 0;

		// skip sign
		assert(n>pos);
		c = m_str[pos];
		if ( (c=='-') || (c=='+') )
			pos++;

		// skip base prefix where relevant
		int prefix_chars = 0;
		switch (m_base) {
			case 8:
			case 10: prefix_chars=0; break;
			case 2:
			case 16: prefix_chars=2; break;
			default: 
				assert(false);
		}
		pos += prefix_chars;

		ULONG_LONG result = 0;
		assert(n>pos);
		while (n>pos) {
			c = m_str[pos++];

			int digit = translate_digit(c);
			assert((digit>=0) && (digit<m_base));

			// check for overflow
			if (result > (max_ulonglong() - digit)/m_base)
				throw Error("Received integer too big to fit in an integral type");

			result = result*m_base + digit;
		}

		return result;
	}

	int TentativeValue::translate_digit(char c)
	{
		if (c>='0' && c<='9')
			return c - '0';
		if (c>='a' && c<='z')
			return 10 + c - 'a';
		if (c>='A' && c<='Z')
			return 10 + c - 'A';
		assert(false);
		return 0; // silence compiler warning
	}

	ULONG_LONG TentativeValue::max_int()
	{
		return (~0U>>1);
	}
		
	ULONG_LONG TentativeValue::max_uint()
	{
		return ~0U;
	}
			
	ULONG_LONG TentativeValue::max_long()
	{
		return (~0UL>>1);
	}
			
	ULONG_LONG TentativeValue::max_ulong()
	{
		return ~0UL;
	}

	ULONG_LONG TentativeValue::max_longlong()
	{
		return max_ulonglong() >> 1;
	}
			
	ULONG_LONG TentativeValue::max_ulonglong()
	{
		ULONG_LONG ull = 0;
		return ~ull;
	}

} // namespace xParam_internal

