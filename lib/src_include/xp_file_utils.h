#ifndef XPARAM_FILE_UTILS_H
#define XPARAM_FILE_UTILS_H

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
 * Routines for parsing file names.
 * Provides abstractions usefull for both windows and unix
 */

#include <string>
#include "../xparam/xp_config.h"

namespace xParam_internal {

namespace FileUtils {
	// return canonical form of path (on windows turns / to \)
	std::string canonical_form(const std::string& path);
	
	// the character used to separate directories in a path string
	char path_separator();

	// the character used to separate directory names in a path
	char path_slash_char();

	// returns true iff 'filename' represents a relative path
	// (relative to some current directory) as opposed to an 
	// absolute path (relative to the root of the file system)
	bool is_relative(const std::string& filename);

	// return prefix of 'path' up to last path_slash_char(), including
	// last slash.
	// If 'path' doesn't contain any slashes, returns empty string
	std::string dir_part(const std::string& path);

} // namespace FileUtils

} // namespace xParam_internal

#endif // XPARAM_FILE_UTILS_H
