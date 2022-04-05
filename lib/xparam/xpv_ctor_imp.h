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

#ifndef XPARAM_CTOR_IMP_H
#define XPARAM_CTOR_IMP_H

#include "xpv_ctor.h"

namespace xParam_internal {

	////////////////////// Template code for 0 arguments //////////////////////

	template<class TARGET, class CREATOR >
	class TypedCtor_0 : public Ctor {
		public:
			TypedCtor_0(const std::vector<ArgDef>& arg_defs) : Ctor(typeid(TARGET), arg_defs) {}

		protected:
			virtual Handle<Value> actual_create(const ValueList& args) const {
				Handle<TARGET> tval( CREATOR::create() );
				return Handle<Value>(new TypedValue<TARGET>(tval));
			}
	};

	template<class TARGET >
	class CreateWithNew_0 {
		public:
			static TARGET* create() {
				return new TARGET();
			}
	};

	////////////////////// Template code for 1 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0>
	class TypedCtor_1 : public Ctor {
		public:
			TypedCtor_1(const std::vector<ArgDef>& arg_defs) : Ctor(typeid(TARGET), arg_defs) {}

		protected:
			virtual Handle<Value> actual_create(const ValueList& args) const {
				Handle<TARGET> tval( CREATOR::create(ARG_PASSER_0::pass(args[0])) );
				return Handle<Value>(new TypedValue<TARGET>(tval));
			}
	};

	template<class TARGET , class ARG_0>
	class CreateWithNew_1 {
		public:
			static TARGET* create(ARG_0 arg_0) {
				return new TARGET((TARGET)arg_0);
			}
	};

	////////////////////// Template code for 2 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1>
	class TypedCtor_2 : public Ctor {
		public:
			TypedCtor_2(const std::vector<ArgDef>& arg_defs) : Ctor(typeid(TARGET), arg_defs) {}

		protected:
			virtual Handle<Value> actual_create(const ValueList& args) const {
				Handle<TARGET> tval( CREATOR::create(ARG_PASSER_0::pass(args[0]), ARG_PASSER_1::pass(args[1])) );
				return Handle<Value>(new TypedValue<TARGET>(tval));
			}
	};

	template<class TARGET , class ARG_0, class ARG_1>
	class CreateWithNew_2 {
		public:
			static TARGET* create(ARG_0 arg_0, ARG_1 arg_1) {
				return new TARGET(arg_0, arg_1);
			}
	};

	////////////////////// Template code for 3 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2>
	class TypedCtor_3 : public Ctor {
		public:
			TypedCtor_3(const std::vector<ArgDef>& arg_defs) : Ctor(typeid(TARGET), arg_defs) {}

		protected:
			virtual Handle<Value> actual_create(const ValueList& args) const {
				Handle<TARGET> tval( CREATOR::create(ARG_PASSER_0::pass(args[0]), ARG_PASSER_1::pass(args[1]), ARG_PASSER_2::pass(args[2])) );
				return Handle<Value>(new TypedValue<TARGET>(tval));
			}
	};

	template<class TARGET , class ARG_0, class ARG_1, class ARG_2>
	class CreateWithNew_3 {
		public:
			static TARGET* create(ARG_0 arg_0, ARG_1 arg_1, ARG_2 arg_2) {
				return new TARGET(arg_0, arg_1, arg_2);
			}
	};

	////////////////////// Template code for 4 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3>
	class TypedCtor_4 : public Ctor {
		public:
			TypedCtor_4(const std::vector<ArgDef>& arg_defs) : Ctor(typeid(TARGET), arg_defs) {}

		protected:
			virtual Handle<Value> actual_create(const ValueList& args) const {
				Handle<TARGET> tval( CREATOR::create(ARG_PASSER_0::pass(args[0]), ARG_PASSER_1::pass(args[1]), ARG_PASSER_2::pass(args[2]), ARG_PASSER_3::pass(args[3])) );
				return Handle<Value>(new TypedValue<TARGET>(tval));
			}
	};

	template<class TARGET , class ARG_0, class ARG_1, class ARG_2, class ARG_3>
	class CreateWithNew_4 {
		public:
			static TARGET* create(ARG_0 arg_0, ARG_1 arg_1, ARG_2 arg_2, ARG_3 arg_3) {
				return new TARGET(arg_0, arg_1, arg_2, arg_3);
			}
	};

	////////////////////// Template code for 5 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4>
	class TypedCtor_5 : public Ctor {
		public:
			TypedCtor_5(const std::vector<ArgDef>& arg_defs) : Ctor(typeid(TARGET), arg_defs) {}

		protected:
			virtual Handle<Value> actual_create(const ValueList& args) const {
				Handle<TARGET> tval( CREATOR::create(ARG_PASSER_0::pass(args[0]), ARG_PASSER_1::pass(args[1]), ARG_PASSER_2::pass(args[2]), ARG_PASSER_3::pass(args[3]), ARG_PASSER_4::pass(args[4])) );
				return Handle<Value>(new TypedValue<TARGET>(tval));
			}
	};

	template<class TARGET , class ARG_0, class ARG_1, class ARG_2, class ARG_3, class ARG_4>
	class CreateWithNew_5 {
		public:
			static TARGET* create(ARG_0 arg_0, ARG_1 arg_1, ARG_2 arg_2, ARG_3 arg_3, ARG_4 arg_4) {
				return new TARGET(arg_0, arg_1, arg_2, arg_3, arg_4);
			}
	};

	////////////////////// Template code for 6 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5>
	class TypedCtor_6 : public Ctor {
		public:
			TypedCtor_6(const std::vector<ArgDef>& arg_defs) : Ctor(typeid(TARGET), arg_defs) {}

		protected:
			virtual Handle<Value> actual_create(const ValueList& args) const {
				Handle<TARGET> tval( CREATOR::create(ARG_PASSER_0::pass(args[0]), ARG_PASSER_1::pass(args[1]), ARG_PASSER_2::pass(args[2]), ARG_PASSER_3::pass(args[3]), ARG_PASSER_4::pass(args[4]), ARG_PASSER_5::pass(args[5])) );
				return Handle<Value>(new TypedValue<TARGET>(tval));
			}
	};

	template<class TARGET , class ARG_0, class ARG_1, class ARG_2, class ARG_3, class ARG_4, class ARG_5>
	class CreateWithNew_6 {
		public:
			static TARGET* create(ARG_0 arg_0, ARG_1 arg_1, ARG_2 arg_2, ARG_3 arg_3, ARG_4 arg_4, ARG_5 arg_5) {
				return new TARGET(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5);
			}
	};

	////////////////////// Template code for 7 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6>
	class TypedCtor_7 : public Ctor {
		public:
			TypedCtor_7(const std::vector<ArgDef>& arg_defs) : Ctor(typeid(TARGET), arg_defs) {}

		protected:
			virtual Handle<Value> actual_create(const ValueList& args) const {
				Handle<TARGET> tval( CREATOR::create(ARG_PASSER_0::pass(args[0]), ARG_PASSER_1::pass(args[1]), ARG_PASSER_2::pass(args[2]), ARG_PASSER_3::pass(args[3]), ARG_PASSER_4::pass(args[4]), ARG_PASSER_5::pass(args[5]), ARG_PASSER_6::pass(args[6])) );
				return Handle<Value>(new TypedValue<TARGET>(tval));
			}
	};

	template<class TARGET , class ARG_0, class ARG_1, class ARG_2, class ARG_3, class ARG_4, class ARG_5, class ARG_6>
	class CreateWithNew_7 {
		public:
			static TARGET* create(ARG_0 arg_0, ARG_1 arg_1, ARG_2 arg_2, ARG_3 arg_3, ARG_4 arg_4, ARG_5 arg_5, ARG_6 arg_6) {
				return new TARGET(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6);
			}
	};

	////////////////////// Template code for 8 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7>
	class TypedCtor_8 : public Ctor {
		public:
			TypedCtor_8(const std::vector<ArgDef>& arg_defs) : Ctor(typeid(TARGET), arg_defs) {}

		protected:
			virtual Handle<Value> actual_create(const ValueList& args) const {
				Handle<TARGET> tval( CREATOR::create(ARG_PASSER_0::pass(args[0]), ARG_PASSER_1::pass(args[1]), ARG_PASSER_2::pass(args[2]), ARG_PASSER_3::pass(args[3]), ARG_PASSER_4::pass(args[4]), ARG_PASSER_5::pass(args[5]), ARG_PASSER_6::pass(args[6]), ARG_PASSER_7::pass(args[7])) );
				return Handle<Value>(new TypedValue<TARGET>(tval));
			}
	};

	template<class TARGET , class ARG_0, class ARG_1, class ARG_2, class ARG_3, class ARG_4, class ARG_5, class ARG_6, class ARG_7>
	class CreateWithNew_8 {
		public:
			static TARGET* create(ARG_0 arg_0, ARG_1 arg_1, ARG_2 arg_2, ARG_3 arg_3, ARG_4 arg_4, ARG_5 arg_5, ARG_6 arg_6, ARG_7 arg_7) {
				return new TARGET(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7);
			}
	};

	////////////////////// Template code for 9 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8>
	class TypedCtor_9 : public Ctor {
		public:
			TypedCtor_9(const std::vector<ArgDef>& arg_defs) : Ctor(typeid(TARGET), arg_defs) {}

		protected:
			virtual Handle<Value> actual_create(const ValueList& args) const {
				Handle<TARGET> tval( CREATOR::create(ARG_PASSER_0::pass(args[0]), ARG_PASSER_1::pass(args[1]), ARG_PASSER_2::pass(args[2]), ARG_PASSER_3::pass(args[3]), ARG_PASSER_4::pass(args[4]), ARG_PASSER_5::pass(args[5]), ARG_PASSER_6::pass(args[6]), ARG_PASSER_7::pass(args[7]), ARG_PASSER_8::pass(args[8])) );
				return Handle<Value>(new TypedValue<TARGET>(tval));
			}
	};

	template<class TARGET , class ARG_0, class ARG_1, class ARG_2, class ARG_3, class ARG_4, class ARG_5, class ARG_6, class ARG_7, class ARG_8>
	class CreateWithNew_9 {
		public:
			static TARGET* create(ARG_0 arg_0, ARG_1 arg_1, ARG_2 arg_2, ARG_3 arg_3, ARG_4 arg_4, ARG_5 arg_5, ARG_6 arg_6, ARG_7 arg_7, ARG_8 arg_8) {
				return new TARGET(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8);
			}
	};

	////////////////////// Template code for 10 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8, class ARG_PASSER_9>
	class TypedCtor_10 : public Ctor {
		public:
			TypedCtor_10(const std::vector<ArgDef>& arg_defs) : Ctor(typeid(TARGET), arg_defs) {}

		protected:
			virtual Handle<Value> actual_create(const ValueList& args) const {
				Handle<TARGET> tval( CREATOR::create(ARG_PASSER_0::pass(args[0]), ARG_PASSER_1::pass(args[1]), ARG_PASSER_2::pass(args[2]), ARG_PASSER_3::pass(args[3]), ARG_PASSER_4::pass(args[4]), ARG_PASSER_5::pass(args[5]), ARG_PASSER_6::pass(args[6]), ARG_PASSER_7::pass(args[7]), ARG_PASSER_8::pass(args[8]), ARG_PASSER_9::pass(args[9])) );
				return Handle<Value>(new TypedValue<TARGET>(tval));
			}
	};

	template<class TARGET , class ARG_0, class ARG_1, class ARG_2, class ARG_3, class ARG_4, class ARG_5, class ARG_6, class ARG_7, class ARG_8, class ARG_9>
	class CreateWithNew_10 {
		public:
			static TARGET* create(ARG_0 arg_0, ARG_1 arg_1, ARG_2 arg_2, ARG_3 arg_3, ARG_4 arg_4, ARG_5 arg_5, ARG_6 arg_6, ARG_7 arg_7, ARG_8 arg_8, ARG_9 arg_9) {
				return new TARGET(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9);
			}
	};

	////////////////////// Template code for 11 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8, class ARG_PASSER_9, class ARG_PASSER_10>
	class TypedCtor_11 : public Ctor {
		public:
			TypedCtor_11(const std::vector<ArgDef>& arg_defs) : Ctor(typeid(TARGET), arg_defs) {}

		protected:
			virtual Handle<Value> actual_create(const ValueList& args) const {
				Handle<TARGET> tval( CREATOR::create(ARG_PASSER_0::pass(args[0]), ARG_PASSER_1::pass(args[1]), ARG_PASSER_2::pass(args[2]), ARG_PASSER_3::pass(args[3]), ARG_PASSER_4::pass(args[4]), ARG_PASSER_5::pass(args[5]), ARG_PASSER_6::pass(args[6]), ARG_PASSER_7::pass(args[7]), ARG_PASSER_8::pass(args[8]), ARG_PASSER_9::pass(args[9]), ARG_PASSER_10::pass(args[10])) );
				return Handle<Value>(new TypedValue<TARGET>(tval));
			}
	};

	template<class TARGET , class ARG_0, class ARG_1, class ARG_2, class ARG_3, class ARG_4, class ARG_5, class ARG_6, class ARG_7, class ARG_8, class ARG_9, class ARG_10>
	class CreateWithNew_11 {
		public:
			static TARGET* create(ARG_0 arg_0, ARG_1 arg_1, ARG_2 arg_2, ARG_3 arg_3, ARG_4 arg_4, ARG_5 arg_5, ARG_6 arg_6, ARG_7 arg_7, ARG_8 arg_8, ARG_9 arg_9, ARG_10 arg_10) {
				return new TARGET(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10);
			}
	};

	////////////////////// Template code for 12 arguments //////////////////////

	template<class TARGET, class CREATOR , class ARG_PASSER_0, class ARG_PASSER_1, class ARG_PASSER_2, class ARG_PASSER_3, class ARG_PASSER_4, class ARG_PASSER_5, class ARG_PASSER_6, class ARG_PASSER_7, class ARG_PASSER_8, class ARG_PASSER_9, class ARG_PASSER_10, class ARG_PASSER_11>
	class TypedCtor_12 : public Ctor {
		public:
			TypedCtor_12(const std::vector<ArgDef>& arg_defs) : Ctor(typeid(TARGET), arg_defs) {}

		protected:
			virtual Handle<Value> actual_create(const ValueList& args) const {
				Handle<TARGET> tval( CREATOR::create(ARG_PASSER_0::pass(args[0]), ARG_PASSER_1::pass(args[1]), ARG_PASSER_2::pass(args[2]), ARG_PASSER_3::pass(args[3]), ARG_PASSER_4::pass(args[4]), ARG_PASSER_5::pass(args[5]), ARG_PASSER_6::pass(args[6]), ARG_PASSER_7::pass(args[7]), ARG_PASSER_8::pass(args[8]), ARG_PASSER_9::pass(args[9]), ARG_PASSER_10::pass(args[10]), ARG_PASSER_11::pass(args[11])) );
				return Handle<Value>(new TypedValue<TARGET>(tval));
			}
	};

	template<class TARGET , class ARG_0, class ARG_1, class ARG_2, class ARG_3, class ARG_4, class ARG_5, class ARG_6, class ARG_7, class ARG_8, class ARG_9, class ARG_10, class ARG_11>
	class CreateWithNew_12 {
		public:
			static TARGET* create(ARG_0 arg_0, ARG_1 arg_1, ARG_2 arg_2, ARG_3 arg_3, ARG_4 arg_4, ARG_5 arg_5, ARG_6 arg_6, ARG_7 arg_7, ARG_8 arg_8, ARG_9 arg_9, ARG_10 arg_10, ARG_11 arg_11) {
				return new TARGET(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, arg_11);
			}
	};


} // namespace xParam_internal

#endif // XPARAM_CTOR_IMP_H
