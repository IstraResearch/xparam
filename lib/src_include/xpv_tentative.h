#ifndef XPARAM_TENTATIVE_H
#define XPARAM_TENTATIVE_H

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
 * TentativeValue class. Represents a lexical token which can be 
 * either an integer (possibly unsigned or long), 
 * real number (double or float), or string.
 */

#include <assert.h>
#include <typeinfo>
#include <string>
#include "../xparam/xp_config.h"
#include "../xparam/xpv_convweight.h"

namespace xParam_internal {
	
	enum tentative_type { tentative_int, tentative_real, tentative_string };

	enum tentative_real_length { trl_float, trl_double, trl_long_double };

#ifndef NO_LONG_DOUBLE
	typedef long double LONG_DOUBLE;
#else
	typedef double LONG_DOUBLE;
#endif

#ifndef NO_LONG_LONG
	typedef long long LONG_LONG;
	typedef unsigned long long ULONG_LONG;
#else
	typedef long LONG_LONG;
	typedef unsigned long ULONG_LONG;
#endif

	class TentativeValue {
		public:
			TentativeValue(const std::string& encoded_value);

			tentative_type type() const { return m_type; }
			const std::string& string_value() const { return m_str; }

			ScalarConvWeight conversion_weight(const std::type_info& target) const;

			int as_int() const;
			unsigned int as_uint() const;
			long as_long() const;
			unsigned long as_ulong() const;
			LONG_LONG as_longlong() const;
			ULONG_LONG as_ulonglong() const;
			double as_double() const;
			float as_float() const;
			LONG_DOUBLE as_long_double() const;
			char as_char() const;
			std::string as_string() const;

			Handle<Value> convert_to(const std::type_info& target) const;

			const std::type_info& strict_type() const;
			Handle<Value> strictly_typed_value() const;

		private:
			ScalarConvWeight real_conversion_weight(const std::type_info& target) const;
			ScalarConvWeight int_conversion_weight(const std::type_info& target) const;
			const std::type_info* best_integral_match() const;
			bool parse_sign() const;
			ULONG_LONG parse_abs_value() const;

			static int translate_digit(char c);
			static ULONG_LONG max_int();
			static ULONG_LONG max_uint();
			static ULONG_LONG max_long();
			static ULONG_LONG max_ulong();
			static ULONG_LONG max_longlong();
			static ULONG_LONG max_ulonglong();

			std::string m_str;
			tentative_type m_type;

			// following fields are used only for integer values
			bool m_long;
			bool m_unsigned;
			int m_base;

			// following fields are used only for real values
			tentative_real_length m_real_length;
	};

} // namespace xParam_internal

#endif // XPARAM_TENTATIVE_H
