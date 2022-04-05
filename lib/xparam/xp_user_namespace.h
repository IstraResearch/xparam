#ifndef XPARAM_USER_NAMESPACE_H
#define XPARAM_USER_NAMESPACE_H

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
 * Names imported from xParam_internal into user's xParam
 */

#include "xparam.h"

namespace xParam {
	using xParam_internal::RawBytes;
	using xParam_internal::xParse;

	using xParam_internal::Error;
	using xParam_internal::MatchError;
	using xParam_internal::ParamSet;
	using xParam_internal::iParamVar;
	using xParam_internal::oParamVar;
	using xParam_internal::ioParamVar;
	using xParam_internal::iParamPtrVar;
	using xParam_internal::oParamPtrVar;
	using xParam_internal::ioParamPtrVar;
	using xParam_internal::Val;
	using xParam_internal::Var;
	using xParam_internal::PtrVal;
	using xParam_internal::PtrVar;
	using xParam_internal::Loader;
	using xParam_internal::Saver;

	using xParam_internal::xparam_init;
	using xParam_internal::xparam_name;
	using xParam_internal::xparam_or_cpp_name;
    using xParam_internal::xparam_help;

	using xParam_internal::FIRST_HOLDS;
	using xParam_internal::LAST_HOLDS;
	using xParam_internal::IS_ERROR;
	using xParam_internal::MultipleAssign;
 
	using xParam_internal::EXACT;
	using xParam_internal::PREFIX;
	using xParam_internal::Match;

} // end namespace xParam

#endif // XPARAM_USER_NAMESPACE_H
