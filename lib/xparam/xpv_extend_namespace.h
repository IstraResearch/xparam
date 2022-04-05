#ifndef XPARAM_EXTEND_NAMESPACE_H
#define XPARAM_EXTEND_NAMESPACE_H

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
 * Names imported from xParam_internal into extender's xParam
 */

#include "xparam_extend.h"

namespace xParam {

	using xParam_internal::TypeTag;
	using xParam_internal::ValueList;
	using xParam_internal::HVL;
	using xParam_internal::ValueTuple;
	using xParam_internal::Typed_2_Tuple;
	using xParam_internal::Typed_3_Tuple;

	using xParam_internal::ClassRegCommand;
	using xParam_internal::ConcreteClassKind;
	using xParam_internal::AbstractClassKind;
	using xParam_internal::param_class;
	using xParam_internal::param_abstract_class;

	using xParam_internal::param_ctor;
	using xParam_internal::param_creator;
	using xParam_internal::param_explicit_ctor;
	using xParam_internal::param_explicit_creator;

	using xParam_internal::ByVal;
	using xParam_internal::ConstRef;
	using xParam_internal::CallerPtr;
	using xParam_internal::ClassPtr;
	using xParam_internal::CallerConstPtr;
	using xParam_internal::ClassConstPtr;
	using xParam_internal::AsConvertedVal;
	using xParam_internal::AsCString;

	using xParam_internal::param_output;
	using xParam_internal::param_direct_output;

	using xParam_internal::DerivedTag;
	using xParam_internal::BaseTag;
	using xParam_internal::param_inheritance;

	using xParam_internal::param_vector;
	using xParam_internal::param_ptr_vector;
	using xParam_internal::param_const_ptr_vector;

	using xParam_internal::param_list;
	using xParam_internal::param_ptr_list;
	using xParam_internal::param_const_ptr_list;

	using xParam_internal::param_set;

	using xParam_internal::param_map;
	using xParam_internal::param_ptr_map;
	using xParam_internal::param_const_ptr_map;

	using xParam_internal::param_pair;

	using xParam_internal::SourceTag;
	using xParam_internal::TargetTag;
	using xParam_internal::param_conversion_operator;
	using xParam_internal::param_weighted_ctor;
	using xParam_internal::param_weighted_creator;

	using xParam_internal::CONV_USER;
	using xParam_internal::CONV_TENTATIVE;
	using xParam_internal::CONV_TO_PARENT;
	using xParam_internal::CONV_STANDARD;
	using xParam_internal::CONV_PROMOTION;

	using xParam_internal::param_const;

	using xParam_internal::param_enum;
	using xParam_internal::param_enum_val;

} // end namespace xParam

#endif // XPARAM_EXTEND_NAMESPACE_H
