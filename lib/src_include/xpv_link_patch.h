#ifndef XPARAM_LINK_PATCH_H
#define XPARAM_LINK_PATCH_H

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
 * Declares functions that are implemented in the registration files
 * of the basic types, and are called from which the XParam core, which
 * forces the linker to take the corresponding objects from the .lib
 */

#include "../xparam/xp_config.h"

#ifdef XPARAM_STATIC_LIB
namespace xParam_internal {

	void link_in_regtype_bool();
	void link_in_regtype_char();
	void link_in_regtype_double();
	void link_in_regtype_long_double();
	void link_in_regtype_float();
	void link_in_regtype_short();
	void link_in_regtype_int();
	void link_in_regtype_long();
	void link_in_regtype_longlong();
	void link_in_regtype_null();
	void link_in_regtype_string();
	void link_in_regtype_tentative();
	void link_in_regtype_uchar();
	void link_in_regtype_ushort();
	void link_in_regtype_uint();
	void link_in_regtype_ulong();
	void link_in_regtype_ulonglong();
	void link_in_regtype_value_list();
	void link_in_regtype_value_tuple();
	void link_in_regtype_raw_bytes();

} // namespace xParam_internal
#endif // XPARAM_STATIC_LIB

#endif // XPARAM_LINK_PATCH_H
