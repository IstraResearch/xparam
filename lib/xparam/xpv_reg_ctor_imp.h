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


/********************************************************
 * auto-generated file - do not edit
 ********************************************************/

#ifndef XPARAM_REG_CTOR_IMP_H
#define XPARAM_REG_CTOR_IMP_H

#include <vector>
#include "xp_handle.h"
#include "xpv_ctor_imp.h"
#include "xpv_scheduler.h"
#include "xpv_reg_ctor.h"

namespace xParam_internal {

	////////////////////// Template code for 0 arguments //////////////////////

	template<class TARGET, class CREATOR >
	void param_creator(TypeTag<TARGET>, TypeTag<CREATOR>  )
	{
		std::vector<ArgDef> arg_defs;
		
		Handle<Ctor> ctor(new TypedCtor_0<TARGET,CREATOR >(arg_defs));
		Handle<RegistrationCommand> command(new CtorRegCommand(ctor));
		registration_scheduler().add_command(command);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET, class CREATOR >
	std::pair<TARGET*,CREATOR*> param_creator()
	{
		param_creator(TypeTag<TARGET>(), TypeTag<CREATOR>()  );
		return std::pair<TARGET*,CREATOR*>();
	}
#endif


	template<class TARGET >
	inline void param_ctor(TypeTag<TARGET>  )
	{
		
		typedef CreateWithNew_0<TARGET > Creator;
		param_creator(TypeTag<TARGET>(), TypeTag<Creator>()  );
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET >
	inline TARGET* param_ctor()
	{
		param_ctor(TypeTag<TARGET>()  );
		return 0;
	}
#endif


	////////////////////// Template code for 1 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0>
	void param_explicit_creator(TypeTag<TARGET>, TypeTag<CREATOR> , const ARG_PASSER_0& arg_0)
	{
		std::vector<ArgDef> arg_defs;
		arg_defs.push_back(arg_0);
		Handle<Ctor> ctor(new TypedCtor_1<TARGET,CREATOR ,ARG_PASSER_0>(arg_defs));
		Handle<RegistrationCommand> command(new CtorRegCommand(ctor));
		registration_scheduler().add_command(command);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET, class CREATOR , class ARG_PASSER_0>
	std::pair<TARGET*,CREATOR*> param_explicit_creator(const ARG_PASSER_0& arg_0)
	{
		param_explicit_creator(TypeTag<TARGET>(), TypeTag<CREATOR>() , arg_0);
		return std::pair<TARGET*,CREATOR*>();
	}
#endif


	template<class TARGET , class ARG_PASSER_0>
	inline void param_explicit_ctor(TypeTag<TARGET> , const ARG_PASSER_0& arg_0)
	{
		typedef typename ARG_PASSER_0::passed_type PassedType_0;
		typedef CreateWithNew_1<TARGET ,PassedType_0> Creator;
		param_explicit_creator(TypeTag<TARGET>(), TypeTag<Creator>() , arg_0);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET , class ARG_PASSER_0>
	inline TARGET* param_explicit_ctor(const ARG_PASSER_0& arg_0)
	{
		param_explicit_ctor(TypeTag<TARGET>() , arg_0);
		return 0;
	}
#endif


	////////////////////// Template code for 2 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1>
	void param_creator(TypeTag<TARGET>, TypeTag<CREATOR> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1)
	{
		std::vector<ArgDef> arg_defs;
		arg_defs.push_back(arg_0);
		arg_defs.push_back(arg_1);
		Handle<Ctor> ctor(new TypedCtor_2<TARGET,CREATOR ,ARG_PASSER_0,ARG_PASSER_1>(arg_defs));
		Handle<RegistrationCommand> command(new CtorRegCommand(ctor));
		registration_scheduler().add_command(command);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1>
	std::pair<TARGET*,CREATOR*> param_creator(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1)
	{
		param_creator(TypeTag<TARGET>(), TypeTag<CREATOR>() , arg_0, arg_1);
		return std::pair<TARGET*,CREATOR*>();
	}
#endif


	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1>
	inline void param_ctor(TypeTag<TARGET> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1)
	{
		typedef typename ARG_PASSER_0::passed_type PassedType_0;
		typedef typename ARG_PASSER_1::passed_type PassedType_1;
		typedef CreateWithNew_2<TARGET ,PassedType_0,PassedType_1> Creator;
		param_creator(TypeTag<TARGET>(), TypeTag<Creator>() , arg_0, arg_1);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1>
	inline TARGET* param_ctor(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1)
	{
		param_ctor(TypeTag<TARGET>() , arg_0, arg_1);
		return 0;
	}
#endif


	////////////////////// Template code for 3 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2>
	void param_creator(TypeTag<TARGET>, TypeTag<CREATOR> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2)
	{
		std::vector<ArgDef> arg_defs;
		arg_defs.push_back(arg_0);
		arg_defs.push_back(arg_1);
		arg_defs.push_back(arg_2);
		Handle<Ctor> ctor(new TypedCtor_3<TARGET,CREATOR ,ARG_PASSER_0,ARG_PASSER_1,ARG_PASSER_2>(arg_defs));
		Handle<RegistrationCommand> command(new CtorRegCommand(ctor));
		registration_scheduler().add_command(command);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2>
	std::pair<TARGET*,CREATOR*> param_creator(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2)
	{
		param_creator(TypeTag<TARGET>(), TypeTag<CREATOR>() , arg_0, arg_1, arg_2);
		return std::pair<TARGET*,CREATOR*>();
	}
#endif


	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2>
	inline void param_ctor(TypeTag<TARGET> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2)
	{
		typedef typename ARG_PASSER_0::passed_type PassedType_0;
		typedef typename ARG_PASSER_1::passed_type PassedType_1;
		typedef typename ARG_PASSER_2::passed_type PassedType_2;
		typedef CreateWithNew_3<TARGET ,PassedType_0,PassedType_1,PassedType_2> Creator;
		param_creator(TypeTag<TARGET>(), TypeTag<Creator>() , arg_0, arg_1, arg_2);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2>
	inline TARGET* param_ctor(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2)
	{
		param_ctor(TypeTag<TARGET>() , arg_0, arg_1, arg_2);
		return 0;
	}
#endif


	////////////////////// Template code for 4 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3>
	void param_creator(TypeTag<TARGET>, TypeTag<CREATOR> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3)
	{
		std::vector<ArgDef> arg_defs;
		arg_defs.push_back(arg_0);
		arg_defs.push_back(arg_1);
		arg_defs.push_back(arg_2);
		arg_defs.push_back(arg_3);
		Handle<Ctor> ctor(new TypedCtor_4<TARGET,CREATOR ,ARG_PASSER_0,ARG_PASSER_1,ARG_PASSER_2,ARG_PASSER_3>(arg_defs));
		Handle<RegistrationCommand> command(new CtorRegCommand(ctor));
		registration_scheduler().add_command(command);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3>
	std::pair<TARGET*,CREATOR*> param_creator(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3)
	{
		param_creator(TypeTag<TARGET>(), TypeTag<CREATOR>() , arg_0, arg_1, arg_2, arg_3);
		return std::pair<TARGET*,CREATOR*>();
	}
#endif


	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3>
	inline void param_ctor(TypeTag<TARGET> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3)
	{
		typedef typename ARG_PASSER_0::passed_type PassedType_0;
		typedef typename ARG_PASSER_1::passed_type PassedType_1;
		typedef typename ARG_PASSER_2::passed_type PassedType_2;
		typedef typename ARG_PASSER_3::passed_type PassedType_3;
		typedef CreateWithNew_4<TARGET ,PassedType_0,PassedType_1,PassedType_2,PassedType_3> Creator;
		param_creator(TypeTag<TARGET>(), TypeTag<Creator>() , arg_0, arg_1, arg_2, arg_3);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3>
	inline TARGET* param_ctor(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3)
	{
		param_ctor(TypeTag<TARGET>() , arg_0, arg_1, arg_2, arg_3);
		return 0;
	}
#endif


	////////////////////// Template code for 5 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4>
	void param_creator(TypeTag<TARGET>, TypeTag<CREATOR> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4)
	{
		std::vector<ArgDef> arg_defs;
		arg_defs.push_back(arg_0);
		arg_defs.push_back(arg_1);
		arg_defs.push_back(arg_2);
		arg_defs.push_back(arg_3);
		arg_defs.push_back(arg_4);
		Handle<Ctor> ctor(new TypedCtor_5<TARGET,CREATOR ,ARG_PASSER_0,ARG_PASSER_1,ARG_PASSER_2,ARG_PASSER_3,ARG_PASSER_4>(arg_defs));
		Handle<RegistrationCommand> command(new CtorRegCommand(ctor));
		registration_scheduler().add_command(command);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4>
	std::pair<TARGET*,CREATOR*> param_creator(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4)
	{
		param_creator(TypeTag<TARGET>(), TypeTag<CREATOR>() , arg_0, arg_1, arg_2, arg_3, arg_4);
		return std::pair<TARGET*,CREATOR*>();
	}
#endif


	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4>
	inline void param_ctor(TypeTag<TARGET> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4)
	{
		typedef typename ARG_PASSER_0::passed_type PassedType_0;
		typedef typename ARG_PASSER_1::passed_type PassedType_1;
		typedef typename ARG_PASSER_2::passed_type PassedType_2;
		typedef typename ARG_PASSER_3::passed_type PassedType_3;
		typedef typename ARG_PASSER_4::passed_type PassedType_4;
		typedef CreateWithNew_5<TARGET ,PassedType_0,PassedType_1,PassedType_2,PassedType_3,PassedType_4> Creator;
		param_creator(TypeTag<TARGET>(), TypeTag<Creator>() , arg_0, arg_1, arg_2, arg_3, arg_4);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4>
	inline TARGET* param_ctor(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4)
	{
		param_ctor(TypeTag<TARGET>() , arg_0, arg_1, arg_2, arg_3, arg_4);
		return 0;
	}
#endif


	////////////////////// Template code for 6 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5>
	void param_creator(TypeTag<TARGET>, TypeTag<CREATOR> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5)
	{
		std::vector<ArgDef> arg_defs;
		arg_defs.push_back(arg_0);
		arg_defs.push_back(arg_1);
		arg_defs.push_back(arg_2);
		arg_defs.push_back(arg_3);
		arg_defs.push_back(arg_4);
		arg_defs.push_back(arg_5);
		Handle<Ctor> ctor(new TypedCtor_6<TARGET,CREATOR ,ARG_PASSER_0,ARG_PASSER_1,ARG_PASSER_2,ARG_PASSER_3,ARG_PASSER_4,ARG_PASSER_5>(arg_defs));
		Handle<RegistrationCommand> command(new CtorRegCommand(ctor));
		registration_scheduler().add_command(command);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5>
	std::pair<TARGET*,CREATOR*> param_creator(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5)
	{
		param_creator(TypeTag<TARGET>(), TypeTag<CREATOR>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5);
		return std::pair<TARGET*,CREATOR*>();
	}
#endif


	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5>
	inline void param_ctor(TypeTag<TARGET> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5)
	{
		typedef typename ARG_PASSER_0::passed_type PassedType_0;
		typedef typename ARG_PASSER_1::passed_type PassedType_1;
		typedef typename ARG_PASSER_2::passed_type PassedType_2;
		typedef typename ARG_PASSER_3::passed_type PassedType_3;
		typedef typename ARG_PASSER_4::passed_type PassedType_4;
		typedef typename ARG_PASSER_5::passed_type PassedType_5;
		typedef CreateWithNew_6<TARGET ,PassedType_0,PassedType_1,PassedType_2,PassedType_3,PassedType_4,PassedType_5> Creator;
		param_creator(TypeTag<TARGET>(), TypeTag<Creator>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5>
	inline TARGET* param_ctor(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5)
	{
		param_ctor(TypeTag<TARGET>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5);
		return 0;
	}
#endif


	////////////////////// Template code for 7 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6>
	void param_creator(TypeTag<TARGET>, TypeTag<CREATOR> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6)
	{
		std::vector<ArgDef> arg_defs;
		arg_defs.push_back(arg_0);
		arg_defs.push_back(arg_1);
		arg_defs.push_back(arg_2);
		arg_defs.push_back(arg_3);
		arg_defs.push_back(arg_4);
		arg_defs.push_back(arg_5);
		arg_defs.push_back(arg_6);
		Handle<Ctor> ctor(new TypedCtor_7<TARGET,CREATOR ,ARG_PASSER_0,ARG_PASSER_1,ARG_PASSER_2,ARG_PASSER_3,ARG_PASSER_4,ARG_PASSER_5,ARG_PASSER_6>(arg_defs));
		Handle<RegistrationCommand> command(new CtorRegCommand(ctor));
		registration_scheduler().add_command(command);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6>
	std::pair<TARGET*,CREATOR*> param_creator(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6)
	{
		param_creator(TypeTag<TARGET>(), TypeTag<CREATOR>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6);
		return std::pair<TARGET*,CREATOR*>();
	}
#endif


	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6>
	inline void param_ctor(TypeTag<TARGET> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6)
	{
		typedef typename ARG_PASSER_0::passed_type PassedType_0;
		typedef typename ARG_PASSER_1::passed_type PassedType_1;
		typedef typename ARG_PASSER_2::passed_type PassedType_2;
		typedef typename ARG_PASSER_3::passed_type PassedType_3;
		typedef typename ARG_PASSER_4::passed_type PassedType_4;
		typedef typename ARG_PASSER_5::passed_type PassedType_5;
		typedef typename ARG_PASSER_6::passed_type PassedType_6;
		typedef CreateWithNew_7<TARGET ,PassedType_0,PassedType_1,PassedType_2,PassedType_3,PassedType_4,PassedType_5,PassedType_6> Creator;
		param_creator(TypeTag<TARGET>(), TypeTag<Creator>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6>
	inline TARGET* param_ctor(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6)
	{
		param_ctor(TypeTag<TARGET>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6);
		return 0;
	}
#endif


	////////////////////// Template code for 8 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7>
	void param_creator(TypeTag<TARGET>, TypeTag<CREATOR> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7)
	{
		std::vector<ArgDef> arg_defs;
		arg_defs.push_back(arg_0);
		arg_defs.push_back(arg_1);
		arg_defs.push_back(arg_2);
		arg_defs.push_back(arg_3);
		arg_defs.push_back(arg_4);
		arg_defs.push_back(arg_5);
		arg_defs.push_back(arg_6);
		arg_defs.push_back(arg_7);
		Handle<Ctor> ctor(new TypedCtor_8<TARGET,CREATOR ,ARG_PASSER_0,ARG_PASSER_1,ARG_PASSER_2,ARG_PASSER_3,ARG_PASSER_4,ARG_PASSER_5,ARG_PASSER_6,ARG_PASSER_7>(arg_defs));
		Handle<RegistrationCommand> command(new CtorRegCommand(ctor));
		registration_scheduler().add_command(command);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7>
	std::pair<TARGET*,CREATOR*> param_creator(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7)
	{
		param_creator(TypeTag<TARGET>(), TypeTag<CREATOR>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7);
		return std::pair<TARGET*,CREATOR*>();
	}
#endif


	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7>
	inline void param_ctor(TypeTag<TARGET> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7)
	{
		typedef typename ARG_PASSER_0::passed_type PassedType_0;
		typedef typename ARG_PASSER_1::passed_type PassedType_1;
		typedef typename ARG_PASSER_2::passed_type PassedType_2;
		typedef typename ARG_PASSER_3::passed_type PassedType_3;
		typedef typename ARG_PASSER_4::passed_type PassedType_4;
		typedef typename ARG_PASSER_5::passed_type PassedType_5;
		typedef typename ARG_PASSER_6::passed_type PassedType_6;
		typedef typename ARG_PASSER_7::passed_type PassedType_7;
		typedef CreateWithNew_8<TARGET ,PassedType_0,PassedType_1,PassedType_2,PassedType_3,PassedType_4,PassedType_5,PassedType_6,PassedType_7> Creator;
		param_creator(TypeTag<TARGET>(), TypeTag<Creator>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7>
	inline TARGET* param_ctor(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7)
	{
		param_ctor(TypeTag<TARGET>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7);
		return 0;
	}
#endif


	////////////////////// Template code for 9 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8>
	void param_creator(TypeTag<TARGET>, TypeTag<CREATOR> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7, const ARG_PASSER_8& arg_8)
	{
		std::vector<ArgDef> arg_defs;
		arg_defs.push_back(arg_0);
		arg_defs.push_back(arg_1);
		arg_defs.push_back(arg_2);
		arg_defs.push_back(arg_3);
		arg_defs.push_back(arg_4);
		arg_defs.push_back(arg_5);
		arg_defs.push_back(arg_6);
		arg_defs.push_back(arg_7);
		arg_defs.push_back(arg_8);
		Handle<Ctor> ctor(new TypedCtor_9<TARGET,CREATOR ,ARG_PASSER_0,ARG_PASSER_1,ARG_PASSER_2,ARG_PASSER_3,ARG_PASSER_4,ARG_PASSER_5,ARG_PASSER_6,ARG_PASSER_7,ARG_PASSER_8>(arg_defs));
		Handle<RegistrationCommand> command(new CtorRegCommand(ctor));
		registration_scheduler().add_command(command);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8>
	std::pair<TARGET*,CREATOR*> param_creator(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7, const ARG_PASSER_8& arg_8)
	{
		param_creator(TypeTag<TARGET>(), TypeTag<CREATOR>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8);
		return std::pair<TARGET*,CREATOR*>();
	}
#endif


	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8>
	inline void param_ctor(TypeTag<TARGET> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7, const ARG_PASSER_8& arg_8)
	{
		typedef typename ARG_PASSER_0::passed_type PassedType_0;
		typedef typename ARG_PASSER_1::passed_type PassedType_1;
		typedef typename ARG_PASSER_2::passed_type PassedType_2;
		typedef typename ARG_PASSER_3::passed_type PassedType_3;
		typedef typename ARG_PASSER_4::passed_type PassedType_4;
		typedef typename ARG_PASSER_5::passed_type PassedType_5;
		typedef typename ARG_PASSER_6::passed_type PassedType_6;
		typedef typename ARG_PASSER_7::passed_type PassedType_7;
		typedef typename ARG_PASSER_8::passed_type PassedType_8;
		typedef CreateWithNew_9<TARGET ,PassedType_0,PassedType_1,PassedType_2,PassedType_3,PassedType_4,PassedType_5,PassedType_6,PassedType_7,PassedType_8> Creator;
		param_creator(TypeTag<TARGET>(), TypeTag<Creator>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8>
	inline TARGET* param_ctor(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7, const ARG_PASSER_8& arg_8)
	{
		param_ctor(TypeTag<TARGET>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8);
		return 0;
	}
#endif


	////////////////////// Template code for 10 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8, class ARG_PASSER_9>
	void param_creator(TypeTag<TARGET>, TypeTag<CREATOR> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7, const ARG_PASSER_8& arg_8, const ARG_PASSER_9& arg_9)
	{
		std::vector<ArgDef> arg_defs;
		arg_defs.push_back(arg_0);
		arg_defs.push_back(arg_1);
		arg_defs.push_back(arg_2);
		arg_defs.push_back(arg_3);
		arg_defs.push_back(arg_4);
		arg_defs.push_back(arg_5);
		arg_defs.push_back(arg_6);
		arg_defs.push_back(arg_7);
		arg_defs.push_back(arg_8);
		arg_defs.push_back(arg_9);
		Handle<Ctor> ctor(new TypedCtor_10<TARGET,CREATOR ,ARG_PASSER_0,ARG_PASSER_1,ARG_PASSER_2,ARG_PASSER_3,ARG_PASSER_4,ARG_PASSER_5,ARG_PASSER_6,ARG_PASSER_7,ARG_PASSER_8,ARG_PASSER_9>(arg_defs));
		Handle<RegistrationCommand> command(new CtorRegCommand(ctor));
		registration_scheduler().add_command(command);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8, class ARG_PASSER_9>
	std::pair<TARGET*,CREATOR*> param_creator(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7, const ARG_PASSER_8& arg_8, const ARG_PASSER_9& arg_9)
	{
		param_creator(TypeTag<TARGET>(), TypeTag<CREATOR>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9);
		return std::pair<TARGET*,CREATOR*>();
	}
#endif


	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8, class ARG_PASSER_9>
	inline void param_ctor(TypeTag<TARGET> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7, const ARG_PASSER_8& arg_8, const ARG_PASSER_9& arg_9)
	{
		typedef typename ARG_PASSER_0::passed_type PassedType_0;
		typedef typename ARG_PASSER_1::passed_type PassedType_1;
		typedef typename ARG_PASSER_2::passed_type PassedType_2;
		typedef typename ARG_PASSER_3::passed_type PassedType_3;
		typedef typename ARG_PASSER_4::passed_type PassedType_4;
		typedef typename ARG_PASSER_5::passed_type PassedType_5;
		typedef typename ARG_PASSER_6::passed_type PassedType_6;
		typedef typename ARG_PASSER_7::passed_type PassedType_7;
		typedef typename ARG_PASSER_8::passed_type PassedType_8;
		typedef typename ARG_PASSER_9::passed_type PassedType_9;
		typedef CreateWithNew_10<TARGET ,PassedType_0,PassedType_1,PassedType_2,PassedType_3,PassedType_4,PassedType_5,PassedType_6,PassedType_7,PassedType_8,PassedType_9> Creator;
		param_creator(TypeTag<TARGET>(), TypeTag<Creator>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8, class ARG_PASSER_9>
	inline TARGET* param_ctor(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7, const ARG_PASSER_8& arg_8, const ARG_PASSER_9& arg_9)
	{
		param_ctor(TypeTag<TARGET>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9);
		return 0;
	}
#endif


	////////////////////// Template code for 11 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8, class ARG_PASSER_9, class ARG_PASSER_10>
	void param_creator(TypeTag<TARGET>, TypeTag<CREATOR> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7, const ARG_PASSER_8& arg_8, const ARG_PASSER_9& arg_9, const ARG_PASSER_10& arg_10)
	{
		std::vector<ArgDef> arg_defs;
		arg_defs.push_back(arg_0);
		arg_defs.push_back(arg_1);
		arg_defs.push_back(arg_2);
		arg_defs.push_back(arg_3);
		arg_defs.push_back(arg_4);
		arg_defs.push_back(arg_5);
		arg_defs.push_back(arg_6);
		arg_defs.push_back(arg_7);
		arg_defs.push_back(arg_8);
		arg_defs.push_back(arg_9);
		arg_defs.push_back(arg_10);
		Handle<Ctor> ctor(new TypedCtor_11<TARGET,CREATOR ,ARG_PASSER_0,ARG_PASSER_1,ARG_PASSER_2,ARG_PASSER_3,ARG_PASSER_4,ARG_PASSER_5,ARG_PASSER_6,ARG_PASSER_7,ARG_PASSER_8,ARG_PASSER_9,ARG_PASSER_10>(arg_defs));
		Handle<RegistrationCommand> command(new CtorRegCommand(ctor));
		registration_scheduler().add_command(command);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8, class ARG_PASSER_9, class ARG_PASSER_10>
	std::pair<TARGET*,CREATOR*> param_creator(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7, const ARG_PASSER_8& arg_8, const ARG_PASSER_9& arg_9, const ARG_PASSER_10& arg_10)
	{
		param_creator(TypeTag<TARGET>(), TypeTag<CREATOR>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10);
		return std::pair<TARGET*,CREATOR*>();
	}
#endif


	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8, class ARG_PASSER_9, class ARG_PASSER_10>
	inline void param_ctor(TypeTag<TARGET> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7, const ARG_PASSER_8& arg_8, const ARG_PASSER_9& arg_9, const ARG_PASSER_10& arg_10)
	{
		typedef typename ARG_PASSER_0::passed_type PassedType_0;
		typedef typename ARG_PASSER_1::passed_type PassedType_1;
		typedef typename ARG_PASSER_2::passed_type PassedType_2;
		typedef typename ARG_PASSER_3::passed_type PassedType_3;
		typedef typename ARG_PASSER_4::passed_type PassedType_4;
		typedef typename ARG_PASSER_5::passed_type PassedType_5;
		typedef typename ARG_PASSER_6::passed_type PassedType_6;
		typedef typename ARG_PASSER_7::passed_type PassedType_7;
		typedef typename ARG_PASSER_8::passed_type PassedType_8;
		typedef typename ARG_PASSER_9::passed_type PassedType_9;
		typedef typename ARG_PASSER_10::passed_type PassedType_10;
		typedef CreateWithNew_11<TARGET ,PassedType_0,PassedType_1,PassedType_2,PassedType_3,PassedType_4,PassedType_5,PassedType_6,PassedType_7,PassedType_8,PassedType_9,PassedType_10> Creator;
		param_creator(TypeTag<TARGET>(), TypeTag<Creator>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8, class ARG_PASSER_9, class ARG_PASSER_10>
	inline TARGET* param_ctor(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7, const ARG_PASSER_8& arg_8, const ARG_PASSER_9& arg_9, const ARG_PASSER_10& arg_10)
	{
		param_ctor(TypeTag<TARGET>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10);
		return 0;
	}
#endif


	////////////////////// Template code for 12 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8, class ARG_PASSER_9, class ARG_PASSER_10, class ARG_PASSER_11>
	void param_creator(TypeTag<TARGET>, TypeTag<CREATOR> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7, const ARG_PASSER_8& arg_8, const ARG_PASSER_9& arg_9, const ARG_PASSER_10& arg_10, const ARG_PASSER_11& arg_11)
	{
		std::vector<ArgDef> arg_defs;
		arg_defs.push_back(arg_0);
		arg_defs.push_back(arg_1);
		arg_defs.push_back(arg_2);
		arg_defs.push_back(arg_3);
		arg_defs.push_back(arg_4);
		arg_defs.push_back(arg_5);
		arg_defs.push_back(arg_6);
		arg_defs.push_back(arg_7);
		arg_defs.push_back(arg_8);
		arg_defs.push_back(arg_9);
		arg_defs.push_back(arg_10);
		arg_defs.push_back(arg_11);
		Handle<Ctor> ctor(new TypedCtor_12<TARGET,CREATOR ,ARG_PASSER_0,ARG_PASSER_1,ARG_PASSER_2,ARG_PASSER_3,ARG_PASSER_4,ARG_PASSER_5,ARG_PASSER_6,ARG_PASSER_7,ARG_PASSER_8,ARG_PASSER_9,ARG_PASSER_10,ARG_PASSER_11>(arg_defs));
		Handle<RegistrationCommand> command(new CtorRegCommand(ctor));
		registration_scheduler().add_command(command);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8, class ARG_PASSER_9, class ARG_PASSER_10, class ARG_PASSER_11>
	std::pair<TARGET*,CREATOR*> param_creator(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7, const ARG_PASSER_8& arg_8, const ARG_PASSER_9& arg_9, const ARG_PASSER_10& arg_10, const ARG_PASSER_11& arg_11)
	{
		param_creator(TypeTag<TARGET>(), TypeTag<CREATOR>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, arg_11);
		return std::pair<TARGET*,CREATOR*>();
	}
#endif


	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8, class ARG_PASSER_9, class ARG_PASSER_10, class ARG_PASSER_11>
	inline void param_ctor(TypeTag<TARGET> , const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7, const ARG_PASSER_8& arg_8, const ARG_PASSER_9& arg_9, const ARG_PASSER_10& arg_10, const ARG_PASSER_11& arg_11)
	{
		typedef typename ARG_PASSER_0::passed_type PassedType_0;
		typedef typename ARG_PASSER_1::passed_type PassedType_1;
		typedef typename ARG_PASSER_2::passed_type PassedType_2;
		typedef typename ARG_PASSER_3::passed_type PassedType_3;
		typedef typename ARG_PASSER_4::passed_type PassedType_4;
		typedef typename ARG_PASSER_5::passed_type PassedType_5;
		typedef typename ARG_PASSER_6::passed_type PassedType_6;
		typedef typename ARG_PASSER_7::passed_type PassedType_7;
		typedef typename ARG_PASSER_8::passed_type PassedType_8;
		typedef typename ARG_PASSER_9::passed_type PassedType_9;
		typedef typename ARG_PASSER_10::passed_type PassedType_10;
		typedef typename ARG_PASSER_11::passed_type PassedType_11;
		typedef CreateWithNew_12<TARGET ,PassedType_0,PassedType_1,PassedType_2,PassedType_3,PassedType_4,PassedType_5,PassedType_6,PassedType_7,PassedType_8,PassedType_9,PassedType_10,PassedType_11> Creator;
		param_creator(TypeTag<TARGET>(), TypeTag<Creator>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, arg_11);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8, class ARG_PASSER_9, class ARG_PASSER_10, class ARG_PASSER_11>
	inline TARGET* param_ctor(const ARG_PASSER_0& arg_0, const ARG_PASSER_1& arg_1, const ARG_PASSER_2& arg_2, const ARG_PASSER_3& arg_3, const ARG_PASSER_4& arg_4, const ARG_PASSER_5& arg_5, const ARG_PASSER_6& arg_6, const ARG_PASSER_7& arg_7, const ARG_PASSER_8& arg_8, const ARG_PASSER_9& arg_9, const ARG_PASSER_10& arg_10, const ARG_PASSER_11& arg_11)
	{
		param_ctor(TypeTag<TARGET>() , arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, arg_11);
		return 0;
	}
#endif



} // namespace xParam_internal

#endif // XPARAM_REG_CTOR_IMP_H
