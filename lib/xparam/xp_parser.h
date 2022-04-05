#ifndef XPARAM_PARSER_H
#define XPARAM_PARSER_H

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
#include "xp_config.h"
#include "xp_value_source.h"
#include "xp_parsed_types.h"

namespace xParam_internal {

	class AssignmentListener {
		public:
			virtual ~AssignmentListener() {}
			virtual void notify(const std::string& key, 
						        Handle<ParsedValue> parsed_value) = 0;
	};

	// Deserialize a value from 'is' and returns parsed structure that
	// can be used to build the value.
	// Throws an xParam::Error if parsing fails.
	Handle<ParsedValue> parse_value(std::istream& is, 
		const std::vector<std::string>& redirection_context 
											= std::vector<std::string>() );

	// Read a list of "key=value" statements from 'is', and notify 'listener'
	// after each one.
	// Throws an xParam::Error if parsing fails.
	void parse_value_set(std::istream& is, AssignmentListener& listener,
				const std::vector<std::string>& redirection_context 
											= std::vector<std::string>() );

	inline char cmdline_glue_char() { return 1; }

} // namespace xParam_internal

#endif // XPARAM_PARSER_H
