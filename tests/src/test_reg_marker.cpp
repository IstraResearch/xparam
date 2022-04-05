#pragma warning (disable: 4786)

#include <string>
#include <iostream>
#include <fstream>

#include <xparam_extend.h>
#include "../include/test_reg_marker.h"

using namespace std;
using namespace xParam;

PARAM_BEGIN_REG
// should also have a version for not NO_EXPLICIT_TEMPLATE_FUNC_ARGS

  PARAM_CLASS(marker);
  param_ctor(TypeTag<marker>(),ByVal<int>("val"));

  PARAM_CLASS(static_marker);
  param_ctor(TypeTag<static_marker>());

PARAM_END_REG

