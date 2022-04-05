#pragma warning (disable: 4786)

#include <string>
#include <iostream>
#include <fstream>

#include <xparam_extend.h>
#include "../include/test_reg_coordinate.h"

using namespace std;
using namespace xParam;

PARAM_BEGIN_REG
// should also have a version for not NO_EXPLICIT_TEMPLATE_FUNC_ARGS

  PARAM_CLASS(coordinate);
  param_ctor(TypeTag<coordinate>(),ByVal<int>("x"),ByVal<int>("y"));
  param_output<coordinate,coordinate_output_functor>();

PARAM_END_REG

