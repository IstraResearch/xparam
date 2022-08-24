#ifndef XPARAM_REG_LIST_H
#define XPARAM_REG_LIST_H

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
 * Defines the user's API for registering lists
 */

#include <iosfwd>
#include <list>
#include <memory>
#include "xp_config.h"
#include "xp_value_list.h"
#include "xpv_arg_passers.h"
#include "xpv_scheduler.h"
#include "xpv_common_regcom.h"
#include "xpv_reg_hvl.h"
#include "xpv_convweight.h"

#include "xpv_reg_class.h"
#include "xpv_reg_ctor.h"
#include "xpv_reg_output.h"
#include "xpv_reg_conversion.h"


namespace xParam_internal {

 	/////////////////////////////////////
	// List kinds
	/////////////////////////////////////

	template<class T>
	class ByValList {
		public:
			typedef T ElementType;
			typedef std::list<T> ListType;

			typedef ConstRef<T> ArgPasser;

			static const T* get_element_ptr(const T& t) {
				return &t;
			}

			static std::string list_name(const std::string& scalar_name) {
				return "list<" + scalar_name + ">";
			}
	};

	template<class T>
	class PtrList {
		public:
			typedef T ElementType;
			typedef std::list<T*> ListType;

			typedef ClassPtr<T> ArgPasser;

			static const T* get_element_ptr(T* t_ptr) {
				return t_ptr;
			}

			static std::string list_name(const std::string& scalar_name) {
				return "list<" + scalar_name + "*>";
			}
	};

	template<class T>
	class ConstPtrList {
		public:
			typedef T ElementType;
			typedef std::list<const T*> ListType;

			typedef ClassConstPtr<T> ArgPasser;

			static const T* get_element_ptr(const T* t_ptr) {
				return t_ptr;
			}

			static std::string list_name(const std::string& scalar_name) {
				return "list<const " + scalar_name + "*>";
			}
	};


 	/////////////////////////////////////
	// List Creator
	/////////////////////////////////////

	template<class ListKind>
	class ListCreator {
		public:
			typedef typename ListKind::ElementType T;
			typedef typename ListKind::ListType ListType;
			typedef typename ListKind::ArgPasser ArgPasser;

			static ListType* create(const HVL<T>& hvl) 
			{
				std::unique_ptr<ListType> list_obj = std::make_unique<ListType>();

				typename HVL<T>::const_iterator i;
				for (i=hvl.begin(); i!=hvl.end(); ++i) {
					list_obj->push_back( ArgPasser::typed_pass(*i) );
				}

				return list_obj.release();
			}
	};


	/////////////////////////////////////
	// List Output Function
	/////////////////////////////////////

	template<class ListKind>
		class ListOutput {
		public:
			typedef typename ListKind::ElementType ElementType;
			typedef typename ListKind::ListType ListType;

			static ValueList sub_objects(const ListType& l)
			{
				HVL<ElementType> hvl;
				typename ListType::const_iterator i;
				for (i=l.begin(); i!=l.end(); ++i) {
					const ElementType* t_ptr = ListKind::get_element_ptr(*i);
					hvl.append_copy(t_ptr);
				}

				ValueList vl;
				vl << Val(hvl);
				return vl;
			}
	};


	/////////////////////////////////////
	// RegistrationCommand
	/////////////////////////////////////

	template<class ListKind>
	class ListClassRegCommand : public ClassRegCommand<typename ListKind::ListType> {
		public:
			typedef typename ListKind::ElementType T;
			typedef typename ListKind::ListType ListType;

			ListClassRegCommand() 
				: ClassRegCommand<ListType>(typeid(T)) {}

			virtual std::string type_name() const {
				return ListKind::list_name(xparam_or_cpp_name(typeid(T)));
			}
	};


	template<class ListKind>
	class ListRegCommand : public CommonRegCommand {
		public:
			typedef typename ListKind::ElementType T;
			typedef typename ListKind::ListType ListType;
			typedef typename ListKind::ArgPasser ArgPasser;

			ListRegCommand() : CommonRegCommand(typeid(T)) {}

			virtual void do_registration() const 
			{
				// register HVL<T>
				register_hvl<T>();

				// register class
				param_class<ListType>(new ListClassRegCommand<ListKind>());

				// register empty ctor
				param_ctor(TypeTag<ListType>());

				// register ctor from single value and number of copies
				param_ctor(TypeTag<ListType>(), ByVal<long>("n"), ArgPasser("val"));

				// register ctor from HVL<T>
				typedef ListCreator<ListKind> Creator;
				param_weighted_creator(TypeTag<ListType>(),
					                   TypeTag<Creator>(),
								       ConstRef< HVL<T> >("hvl"),
									   CONV_STANDARD);

				// register output
				typedef ListOutput<ListKind> OutputFunc;
				param_output<ListType,OutputFunc>();
			}

			virtual std::string description() const {
				return "list type - " 
					+ ListKind::list_name(xparam_or_cpp_name(typeid(T)));
			}

	};

	/////////////////////////////////////
	// User registration API
	/////////////////////////////////////

	template<class ListKind>
		class RegList {
		public:
			RegList()
			{
				Handle<RegistrationCommand> command(new ListRegCommand<ListKind>);
				registration_scheduler().add_command(command);
			}
		};

	template<class T>
		class param_list : private RegList< ByValList<T> > {};

	template<class T>
		class param_ptr_list : private RegList< PtrList<T> > {};

	template<class T>
		class param_const_ptr_list : private RegList< ConstPtrList<T> > {};

} // namespace xParam_internal

#endif // XPARAM_REG_LIST_H
