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

  PARAM_CLASS(duckling);
  param_inheritance(DerivedTag<duckling>(),BaseTag<duck>());
  param_ctor(TypeTag<duckling>());
  param_ctor(TypeTag<duckling>(),ByVal<int>("val"));
  param_ctor(TypeTag<duckling>(),ConstRef<string>("val"));
  param_ctor(TypeTag<duckling>(),ByVal<int>("val1"),ByVal<int>("val2"));
  param_ctor(TypeTag<duckling>(),ByVal<double>("val1"),ByVal<double>("val2"));
  param_ctor(TypeTag<duckling>(),CallerConstPtr<marker>("my_const_marker"),
             ClassConstPtr<marker>("your_const_marker"),
             CallerPtr<marker>("my_marker"), ClassPtr<marker>("your_marker"));
  param_ctor(TypeTag<duckling>(),CallerConstPtr<static_marker>("my_const_marker"),
             ClassConstPtr<static_marker>("your_const_marker"),
             CallerPtr<static_marker>("my_marker"),
             ClassPtr<static_marker>("your_marker"));
  param_output<duckling,duckling_output_functor>();
  param_vector<duckling>();

PARAM_END_REG

