#	Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2, or (at your option)
#  any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this software; see the file COPYING.  If not, write to
#  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
# 
#  As a special exception, the copyright holders give permission
#  for additional uses of the text contained in its release of XPARAM.
# 
#  The exception is that, if you link the XPARAM library with other files
#  to produce an executable, this does not by itself cause the
#  resulting executable to be covered by the GNU General Public License.
#  Your use of that executable is in no way restricted on account of
#  linking the XPARAM library code into it.
# 
#  This exception does not however invalidate any other reasons why
#  the executable file might be covered by the GNU General Public License.
# 
#  If you write modifications of your own for XPARAM, it is your choice
#  whether to permit this exception to apply to your modifications.
#  If you do not wish that, delete this exception notice.  


#########################################################
# generates template code for constructor classes with
# up to a specified number of arguments.
#
# usage: 
# ctor_code_gen.pl max_args
#
# the definitions of TypedCtor_k are written to "xpv_ctor_imp.h"
#
# the definitions of param_ctor() and param_creator() are
# written to "xpv_reg_ctor_imp.h"
#########################################################

use strict;

my $max_args = shift;

######################################## 
# work on "xpv_ctor_imp.h"
########################################

my $license_file = "LICENSE";
open(LICENSE,"<$license_file") || die("Can't open $license_file\n");
my @license_lines = <LICENSE>;
my $license = join("",@license_lines);
close(LICENSE);

my $filename = "xpv_ctor_imp.h";
open(FILE,">$filename") || die("Can't open $filename\n");

print FILE <<END;
$license
/********************************************************
 * auto-generated file - do not edit
 ********************************************************/

#ifndef XPARAM_CTOR_IMP_H
#define XPARAM_CTOR_IMP_H

#include "xpv_ctor.h"

namespace xParam_internal {

END


######################## Template code for K arguments ########################
#
#	template<class TARGET, class CREATOR, class ARG_PASSER_0, ..., class ARG_PASSER_(K-1)>
#	class TypedCtor_K : pubilc Ctor { 
#		public:
#			TypedCtor_K(const std::vector<ArgDef>& arg_defs) : Ctor(typeid(TARGET),arg_defs) {}
#
#		protected:
#			virtual Handle<Value> actual_create(const std::vector< Handle<Value> >& args) const {
#				Handle<TARGET> tval( 
#					CREATOR::create(ARG_PASSER_0::pass(args[0]),
#											...,
#											ARG_PASSER_(K-1)::pass(args[K-1])));
#
#				return Handle<Value>(new TypedValue<TARGET>(tval));
#			}
#	};
#
#	template<class TARGET, class ARG_0, ..., class ARG_(K-1)>
#	class CreateWithNew_K {
#		public:
#			static TARGET* create(ARG_0 arg_0, ..., ARG_(K-1) arg_(K-1)) {
#				return new TARGET(arg_0,...,arg_(K-1));
#			}
#	};
###############################################################################

my ($n,$i);
for ($n=0; $n<$max_args; $n++) {

	my $ctor_template_decl_list = "";
	for ($i=0; $i<$n; $i++) {
		$ctor_template_decl_list .= ", class ARG_PASSER_$i";
	}

	my $ctor_call_list = "";
	for ($i=0; $i<$n; $i++) {
		$ctor_call_list .= ", " if ($i>0);
		$ctor_call_list .= "ARG_PASSER_${i}::pass(args[$i])";
	}

	my $new_creator_template_decl_list = "";
		for ($i=0; $i<$n; $i++) {
		$new_creator_template_decl_list .= ", class ARG_$i";
	}

	my $new_creator_method_decl_list = "";
	for ($i=0; $i<$n; $i++) {
		$new_creator_method_decl_list .= ", " if ($i>0);
		$new_creator_method_decl_list .= "ARG_$i arg_$i";
	}

	my $new_creator_call_list = "";
	$new_creator_call_list .= "(TARGET)" if ($n == 1);
	for ($i=0; $i<$n; $i++) {
		$new_creator_call_list .= ", " if ($i>0);
		$new_creator_call_list .= "arg_$i";
	}

print FILE <<END;	
	////////////////////// Template code for $n arguments //////////////////////

	template<class TARGET, class CREATOR $ctor_template_decl_list>
	class TypedCtor_$n : public Ctor {
		public:
			TypedCtor_$n(const std::vector<ArgDef>& arg_defs) : Ctor(typeid(TARGET), arg_defs) {}

		protected:
			virtual Handle<Value> actual_create(const ValueList& args) const {
				Handle<TARGET> tval( CREATOR::create($ctor_call_list) );
				return Handle<Value>(new TypedValue<TARGET>(tval));
			}
	};

	template<class TARGET $new_creator_template_decl_list>
	class CreateWithNew_$n {
		public:
			static TARGET* create($new_creator_method_decl_list) {
				return new TARGET($new_creator_call_list);
			}
	};

END

} # loop over $n

	
print FILE <<END;

} // namespace xParam_internal

#endif // XPARAM_CTOR_IMP_H
END

close(FILE); # close "xpv_ctor_imp.h"


######################################## 
# work on "xpv_reg_ctor_imp.h"
########################################

$filename = "xpv_reg_ctor_imp.h";
open(FILE,">$filename") || die("Can't open $filename\n");

print FILE <<END;
$license
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

END


######################## Template code for K arguments ########################
#
#	template<class TARGET, class CREATOR, class ARG_PASSER_0, ..., class ARG_PASSER_(K-1)>
#	void param_creator(TypeTag<TARGET>, TypeTag<CREATOR>, 
#                        const ARG_PASSER_0& arg_0, ..., const ARG_PASSER_(K-1)& arg_(K-1))
#	{ 
#		std::vector<ArgDef> arg_defs;
#		arg_defs.push_back(arg_0);
#		...
#		arg_defs.push_back(arg(K-1));
#		Handle<Ctor> ctor(new TypedCtor_K<TARGET,CREATOR,ARG_PASSER_0,...,ARG_PASSER_(K-1)>(arg_defs));
#		Handle<RegistrationCommand> command(new CtorRegCommand(ctor));
#		registration_scheduler().add_command(command);
#	}
#
##ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
#	template<class TARGET, class CREATOR, class ARG_PASSER_0, ..., class ARG_PASSER_(K-1)>
#	std::pair<TARGET*,CREATOR*> param_creator(const ARG_PASSER_0& arg_0, ..., const ARG_PASSER_(K-1)& arg_(K-1))
#	{ 
#		param_creator(TypeTag<TARGET>(), TypeTag<CREATOR>(), arg_0, ..., arg(K-1));
#		return std::pair<TARGET*,CREATOR*>();
#	}
##endif
#
#
#	template<class TARGET, class ARG_PASSER_0, ..., class ARG_PASSER_(K-1)>
#	inline void param_ctor(TypeTag<TARGET>, const ARG_PASSER_0& arg_0, ..., const ARG_PASSER_(K-1)& arg_(K-1))
#	{ 
#		typedef typename ARG_PASSER_0::passed_type PassedType_0;
#		...
#		typedef typename ARG_PASSER(K-1)::passed_type PassedType_(K-1);
#		typedef CreateWithNew_K<TARGET,PassedType_0,...,PassedType(K-1)> Creator;
#		param_creator(TypeTag<TARGET>(), TypeTag<Creator>(), arg_0,...,arg(K-1));
#	}
#
##ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
#	template<class TARGET, class ARG_PASSER_0, ..., class ARG_PASSER_(K-1)>
#	inline TARGET* param_ctor(const ARG_PASSER_0& arg_0, ..., const ARG_PASSER_(K-1)& arg_(K-1))
#	{ 
#		param_ctor(TypeTag<TARGET>(), arg_0, ..., arg_(K-1));
#		return 0;
#	}
##endif
#
###############################################################################

for ($n=0; $n<$max_args; $n++) {

	my $template_decl_list = "";
	for ($i=0; $i<$n; $i++) {
		$template_decl_list .= ", class ARG_PASSER_$i";
	}

	my $template_instantiation_list = "";
	for ($i=0; $i<$n; $i++) {
		$template_instantiation_list .= ",ARG_PASSER_$i";
	}

	my $arg_def_list = "";
	for ($i=0; $i<$n; $i++) {
		$arg_def_list .= ", " if ($i>0);
		$arg_def_list .= "const ARG_PASSER_$i& arg_$i";
	}

	my $push_arg_defs = "";
	for ($i=0; $i<$n; $i++) {
		$push_arg_defs .= "\n\t\t" if ($i>0);
		$push_arg_defs .= "arg_defs.push_back(arg_$i);";
	}

	my $passer_typedefs = "";
	for ($i=0; $i<$n; $i++) {
		$passer_typedefs .= "\n\t\t" if ($i>0);
		$passer_typedefs .= "typedef typename ARG_PASSER_${i}::passed_type PassedType_$i;";
	}

	my $passed_type_list = "";
	for ($i=0; $i<$n; $i++) {
		$passed_type_list .= ",PassedType_$i";
	}

	my $arg_call_list = "";
	for ($i=0; $i<$n; $i++) {
		$arg_call_list .= ", " if ($i>0);
		$arg_call_list .= "arg_$i";
	}

	my $explicit = ($i==1) ? "explicit_" : "";
	my $comma_before_list = ($i>0) ? "," : "";

print FILE <<END;	
	////////////////////// Template code for $n arguments //////////////////////

	template<class TARGET, class CREATOR $template_decl_list>
	void param_${explicit}creator(TypeTag<TARGET>, TypeTag<CREATOR> $comma_before_list $arg_def_list)
	{
		std::vector<ArgDef> arg_defs;
		$push_arg_defs
		Handle<Ctor> ctor(new TypedCtor_$i<TARGET,CREATOR $template_instantiation_list>(arg_defs));
		Handle<RegistrationCommand> command(new CtorRegCommand(ctor));
		registration_scheduler().add_command(command);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET, class CREATOR $template_decl_list>
	std::pair<TARGET*,CREATOR*> param_${explicit}creator($arg_def_list)
	{
		param_${explicit}creator(TypeTag<TARGET>(), TypeTag<CREATOR>() $comma_before_list $arg_call_list);
		return std::pair<TARGET*,CREATOR*>();
	}
#endif


	template<class TARGET $template_decl_list>
	inline void param_${explicit}ctor(TypeTag<TARGET> $comma_before_list $arg_def_list)
	{
		$passer_typedefs
		typedef CreateWithNew_$i<TARGET $passed_type_list> Creator;
		param_${explicit}creator(TypeTag<TARGET>(), TypeTag<Creator>() $comma_before_list $arg_call_list);
	}

#ifndef NO_EXPLICIT_TEMPLATE_FUNC_ARGS
	template<class TARGET $template_decl_list>
	inline TARGET* param_${explicit}ctor($arg_def_list)
	{
		param_${explicit}ctor(TypeTag<TARGET>() $comma_before_list $arg_call_list);
		return 0;
	}
#endif


END

} # loop over $n

	
print FILE <<END;

} // namespace xParam_internal

#endif // XPARAM_REG_CTOR_IMP_H
END

close(FILE); # close "xpv_reg_ctor_imp.h"
