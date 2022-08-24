#ifndef XPARAM_REG_VECTOR_H
#define XPARAM_REG_VECTOR_H

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
 * Defines the user's API for registering vectors
 */

#include <iosfwd>
#include <vector>
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
	// Vector kinds
	/////////////////////////////////////

	template<class T>
	class ByValVector {
		public:
			typedef T ElementType;
			typedef std::vector<T> VecType;

			typedef ConstRef<T> ArgPasser;

			static const T* get_element_ptr(const T& t) {
				return &t;
			}

			static std::string vec_name(const std::string& scalar_name) {
				return "vector<" + scalar_name + ">";
			}
	};

	template<class T>
	class PtrVector {
		public:
			typedef T ElementType;
			typedef std::vector<T*> VecType;

			typedef ClassPtr<T> ArgPasser;

			static const T* get_element_ptr(T* t_ptr) {
				return t_ptr;
			}

			static std::string vec_name(const std::string& scalar_name) {
				return "vector<" + scalar_name + "*>";
			}
	};

	template<class T>
	class ConstPtrVector {
		public:
			typedef T ElementType;
			typedef std::vector<const T*> VecType;

			typedef ClassConstPtr<T> ArgPasser;

			static const T* get_element_ptr(const T* t_ptr) {
				return t_ptr;
			}

			static std::string vec_name(const std::string& scalar_name) {
				return "vector<const " + scalar_name + "*>";
			}
	};


 	/////////////////////////////////////
	// Vector Creator
	/////////////////////////////////////

	template<class VectorKind>
	class VectorCreator {
		public:
			typedef typename VectorKind::ElementType T;
			typedef typename VectorKind::VecType VecType;
			typedef typename VectorKind::ArgPasser ArgPasser;

			static VecType* create(const HVL<T>& hvl) 
			{
				std::unique_ptr<VecType> vec = std::make_unique<VecType>();

				typename HVL<T>::const_iterator i;
				for (i=hvl.begin(); i!=hvl.end(); ++i) {
					vec->push_back( ArgPasser::typed_pass(*i) );
				}

				return vec.release();
			}
	};


	/////////////////////////////////////
	// Vector Output Function
	/////////////////////////////////////

	template<class VectorKind>
		class VectorOutput {
		public:
			typedef typename VectorKind::ElementType ElementType;
			typedef typename VectorKind::VecType VecType;

			static ValueList sub_objects(const VecType& vec)
			{
				HVL<ElementType> hvl;
				typename VecType::const_iterator i;
				for (i=vec.begin(); i!=vec.end(); ++i) {
					const ElementType* t_ptr = VectorKind::get_element_ptr(*i);
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

	template<class VectorKind>
	class VectorClassRegCommand : public ClassRegCommand<typename VectorKind::VecType> {
		public:
			typedef typename VectorKind::ElementType T;
			typedef typename VectorKind::VecType VecType;

			VectorClassRegCommand() 
				: ClassRegCommand<VecType>(typeid(T)) {}

			virtual std::string type_name() const {
				return VectorKind::vec_name(xparam_or_cpp_name(typeid(T)));
			}
	};


	template<class VectorKind>
	class VectorRegCommand : public CommonRegCommand {
		public:
			typedef typename VectorKind::ElementType T;
			typedef typename VectorKind::VecType VecType;
			typedef typename VectorKind::ArgPasser ArgPasser;

			VectorRegCommand() : CommonRegCommand(typeid(T)) {}
			
			virtual void do_registration() const 
			{
				// register HVL<T>
				register_hvl<T>();

				// register class
				param_class<VecType>(new VectorClassRegCommand<VectorKind>());

				// register empty ctor
				param_ctor(TypeTag<VecType>());

				// register ctor from single value and number of copies
				param_ctor(TypeTag<VecType>(), ByVal<long>("n"), ArgPasser("val"));

				// register ctor from HVL<T>
				typedef VectorCreator<VectorKind> Creator;
				param_weighted_creator(TypeTag<VecType>(),
					                   TypeTag<Creator>(),
								       ConstRef< HVL<T> >("hvl"),
									   CONV_STANDARD);

				// register output
				typedef VectorOutput<VectorKind> OutputFunc;
				param_output<VecType,OutputFunc>();
			}

			virtual std::string description() const {
				return "vector type - " 
					+ VectorKind::vec_name(xparam_or_cpp_name(typeid(T)));
			}

	};

	/////////////////////////////////////
	// User registration API
	/////////////////////////////////////

	template<class VectorKind>
		class RegVector {
		public:
			RegVector()
			{
				Handle<RegistrationCommand> command(new VectorRegCommand<VectorKind>);
				registration_scheduler().add_command(command);
			}
		};

	template<class T>
		class param_vector : private RegVector< ByValVector<T> > {};

	template<class T>
		class param_ptr_vector : private RegVector< PtrVector<T> > {};

	template<class T>
		class param_const_ptr_vector : private RegVector< ConstPtrVector<T> > {};

} // namespace xParam_internal

#endif // XPARAM_REG_VECTOR_H
