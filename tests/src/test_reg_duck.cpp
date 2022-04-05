#pragma warning (disable: 4786)

#include <string>
#include <iostream>
#include <fstream>
#include <xparam_extend.h>
#include "../include/test_reg_duck.h"

using namespace std;
using namespace xParam;

PARAM_BEGIN_REG
// should also have a version for not NO_EXPLICIT_TEMPLATE_FUNC_ARGS

  PARAM_ABSTRACT_CLASS(archduck);

  PARAM_CLASS(duck);
  param_inheritance(DerivedTag<duck>(),BaseTag<archduck>());
  param_ctor(TypeTag<duck>());
  param_ctor(TypeTag<duck>(),ByVal<int>("val"));
  param_ctor(TypeTag<duck>(),ConstRef<string>("val"));
  param_conversion_operator(SourceTag<duck>(),TargetTag<unsigned int>());
  param_conversion_operator(SourceTag<duck>(),TargetTag<long>());
  param_vector<duck>();

  PARAM_CLASS(ducky);
  param_inheritance(DerivedTag<ducky>(),BaseTag<duckling>());
  param_explicit_ctor(TypeTag<ducky>(),ConstRef<int>("val"));
  param_ctor(TypeTag<ducky>(),ConstRef<string>("val"));
  param_creator(TypeTag<ducky>(),TypeTag<ducky_creator>());
  param_explicit_creator(TypeTag<ducky>(),TypeTag<ducky_explicit_creator>(),ByVal<double>("val"));
  param_output<ducky,ducky_output_functor>();
  param_vector<ducky>();
PARAM_END_REG

