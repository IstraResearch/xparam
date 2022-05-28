#ifndef XPARAM_REG_SET_H
#define XPARAM_REG_SET_H

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
 * Defines the user's API for registering sets
 */

#include <iosfwd>
#include <set>
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
  // Set kinds
  /////////////////////////////////////

  template<class T>
  class ByValSet {
  public:
    typedef T ElementType;
    typedef std::set<T> SetType;

    typedef ConstRef<T> ArgPasser;

    static const T* get_element_ptr(const T& t) {
      return &t;
    }

    static std::string set_name(const std::string& scalar_name) {
      return "set<" + scalar_name + ">";
    }
  };

  /////////////////////////////////////
  // Set Creator
  /////////////////////////////////////

  template<class SetKind>
	  class SetCreator {
  public:
	  typedef typename SetKind::ElementType T;
	  typedef typename SetKind::SetType SetType;
	  typedef typename SetKind::ArgPasser ArgPasser;
	  
	  static SetType* create(const HVL<T>& hvl) 
	  {
		  SetType* set = new SetType;
		  
		  typename HVL<T>::const_iterator i;
		  for (i=hvl.begin(); i!=hvl.end(); ++i) {
			  bool bInserted = set->insert( ArgPasser::typed_pass(*i) ).second;

			  // check duplicate values
			  if (!bInserted) {
				  throw Error("While constructing set - the value "
					  + make_value(*i)->to_string() 
					  + " appears more than once");
			  }
			  
		  }
		  
		  return set;
	  }
  };


  /////////////////////////////////////
  // Set Output Function
  /////////////////////////////////////

  template<class SetKind>
  class SetOutput {
  public:
    typedef typename SetKind::ElementType ElementType;
    typedef typename SetKind::SetType SetType;

    static ValueList sub_objects(const SetType& set)
    {
      HVL<ElementType> hvl;
      typename SetType::const_iterator i;
      for (i=set.begin(); i!=set.end(); ++i) {
	const ElementType* t_ptr = SetKind::get_element_ptr(*i);
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

  template<class SetKind>
  class SetClassRegCommand : public ClassRegCommand<typename SetKind::SetType> {
  public:
    typedef typename SetKind::ElementType T;
    typedef typename SetKind::SetType SetType;

    SetClassRegCommand() 
      : ClassRegCommand<SetType>(typeid(T)) {}

    virtual std::string type_name() const {
      return SetKind::set_name(xparam_or_cpp_name(typeid(T)));
    }
  };


  template<class SetKind>
  class SetRegCommand : public CommonRegCommand {
  public:
    typedef typename SetKind::ElementType T;
    typedef typename SetKind::SetType SetType;
    typedef typename SetKind::ArgPasser ArgPasser;

    SetRegCommand() : CommonRegCommand(typeid(T)) {}
			
    virtual void do_registration() const 
    {
      // register HVL<T>
      register_hvl<T>();

      // register class
      param_class<SetType>(new SetClassRegCommand<SetKind>());

      // register empty ctor
      param_ctor(TypeTag<SetType>());

      // register ctor from HVL<T>
      typedef SetCreator<SetKind> Creator;
      param_weighted_creator(TypeTag<SetType>(),
			     TypeTag<Creator>(),
			     ConstRef< HVL<T> >("hvl"),
			     CONV_STANDARD);

      // register output
      typedef SetOutput<SetKind> OutputFunc;
      param_output<SetType,OutputFunc>();
    }

    virtual std::string description() const {
      return "set type - " 
	+ SetKind::set_name(xparam_or_cpp_name(typeid(T)));
    }

  };

  /////////////////////////////////////
  // User registration API
  /////////////////////////////////////

  template<class SetKind>
  class RegSet {
  public:
    RegSet()
    {
      Handle<RegistrationCommand> command(new SetRegCommand<SetKind>);
      registration_scheduler().add_command(command);
    }
  };

  template<class T>
  class param_set : private RegSet< ByValSet<T> > {};

} // namespace xParam_internal

#endif // XPARAM_REG_SET_H
