#ifndef XPARAM_OUTPUT_H
#define XPARAM_OUTPUT_H

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
 * Base class for an object representing an output function for 
 * a specific C++ type.
 * Each Type object must have an OutputFunction registered into
 * it, which is used to print the value.
 */

#include <typeinfo>
#include <iosfwd>
#include "xp_config.h"
#include "xp_handle.h"

namespace xParam_internal {

	class Value;

	class OutputFunction {
		public:
			virtual ~OutputFunction() {}

			const std::type_info& type() const {
				return m_type;
			}

			// framework ensures that val.dynamic_type_info() == type()
			virtual void output(std::ostream& os, const Value& val) const = 0;

		protected:
			OutputFunction(const std::type_info& type) : m_type(type) {}
			
		private:
			const std::type_info& m_type;
	};

} // namespace xParam_internal

#endif // XPARAM_OUTPUT_H
