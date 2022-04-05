#ifndef __XP_PARAM_IMP_H__
#define __XP_PARAM_IMP_H__

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

#include <typeinfo>
#include "xp_param.h"
#include "xp_value_source_imp.h"
#include "xp_value_sink_imp.h"

namespace xParam_internal {

	class ParamPartialImp : public Param {
	public:
		ParamPartialImp(const std::string& s, bool is_input, bool is_output)
			: m_is_input(is_input), m_is_output(is_output), 
			m_assigned(false)
		{
		  separate_name_and_description(s);
		}

		virtual bool is_input() const { return m_is_input; }
		virtual bool is_output() const { return m_is_output; }

		virtual bool was_assigned_to() const { return m_assigned; }

	protected:
		virtual Handle<Value> get_value() const = 0;
		virtual void set_value(const Handle<Value>& val, bool flexible) {
			inner_set_value(val,flexible);
			m_assigned = true;
		}

		virtual void inner_set_value(const Handle<Value>& val, bool flexible) = 0;

	public:
		virtual bool has_default() const { 
			return !m_default.empty(); 
		}

	protected:
		virtual Handle<Value> get_default() const { 
			return m_default; 
		}

		virtual void set_default(const Handle<Value>& val) { 
			m_default = val->convert_to(static_type_info(),true);
			inner_set_value(m_default,false);
		}

	public:
		virtual std::string name() const { return m_name; }

		virtual std::string description() const { return m_description; }

		virtual const std::type_info& static_type_info() const = 0;

		virtual bool has_given_value() const {
			return has_default() || was_assigned_to();
		}

	private:
		void separate_name_and_description(const std::string& s);
		static std::string trim(const std::string& s);
	private:
		std::string m_name;
		std::string m_description;
		bool m_is_input;
		bool m_is_output;
		bool m_assigned;
		Handle<Value> m_default;
	};

	template<class T> 
		class ParamVar : public ParamPartialImp {
	public:
		ParamVar(T& var, const std::string& name, bool is_input, bool is_output,
			const Handle<ValueSource>& default_value)
			: ParamPartialImp(name,is_input,is_output), m_var(var) 
		{
			if (!default_value.empty())
				set_default(default_value->get_value());
		}

	protected:
		virtual Handle<Value> get_value() const {
			return Val(m_var)->get_value();
		}

		virtual void inner_set_value(const Handle<Value>& val, bool flexible) {
			innerVar(m_var,flexible)->set_value(val);
		}

	public:
		virtual const std::type_info& static_type_info() const { return typeid(T); } 

	private:
		T& m_var;
	};

	template<class T>
	inline Handle<Param> iParamVar(T& var, const std::string& s, 
				const Handle<ValueSource>& default_value = Handle<ValueSource>()) 
	{
		return Handle<Param>(new ParamVar<T>(var,s,true,false,default_value));
	}

	template<class T>
	inline Handle<Param> oParamVar(const T& var, const std::string& s)
	{
		T& ncvar=const_cast<T&>(var);
		return Handle<Param>(new ParamVar<T>(ncvar,s,false,true,Handle<ValueSource>()));
	}

	template<class T>
	inline Handle<Param> ioParamVar(T& var, const std::string& s, 
				const Handle<ValueSource>& default_value = Handle<ValueSource>()) 
	{
		return Handle<Param>(new ParamVar<T>(var,s,true,true,default_value));
	}




	template <class T> class ParamPtrVar : public ParamPartialImp {
	public:
		ParamPtrVar(T*& ptr_var, const std::string& name, bool is_input, bool is_output,
			const Handle<ValueSource>& default_value)
			: ParamPartialImp(name,is_input,is_output), m_ptr_var(ptr_var)
		{
			if (!default_value.empty())
				set_default(default_value->get_value());
		}

	protected:
		virtual Handle<Value> get_value() const {
			return PtrVal(m_ptr_var)->get_value();
		}

		virtual void inner_set_value(const Handle<Value>& val, bool flexible) {
			if (was_assigned_to())
				delete m_ptr_var;
			innerPtrVar(m_ptr_var,flexible)->set_value(val);
		}

	public:
		virtual const std::type_info& static_type_info() const { return typeid(T); } 

	private:
		T*& m_ptr_var;
	};
    

	template<class T>
	inline Handle<Param> iParamPtrVar(T*& ptr_var, const std::string& s,
		const Handle<ValueSource>& default_value = Handle<ValueSource>()) 
	{
		return Handle<Param>(new ParamPtrVar<T>(ptr_var,s,true,false,default_value));
	}

	template<class T>
	inline Handle<Param> oParamPtrVar(const T* const& ptr_var, const std::string& s)
	{
		T*& ncptr_var=const_cast<T*&>(ptr_var);
		return Handle<Param>(new ParamPtrVar<T>(ncptr_var,s,false,true,Handle<ValueSource>()));
	}

	template<class T>
	inline Handle<Param> ioParamPtrVar(T*& ptr_var, const std::string& s,
		const Handle<ValueSource>& default_value = Handle<ValueSource>()) 
	{
		return Handle<Param>(new ParamPtrVar<T>(ptr_var,s,true,true,default_value));
	}

} // namespace xParam_internal

#endif // __XP_PARAM_IMP_H__

