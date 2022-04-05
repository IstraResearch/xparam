#pragma warning (disable: 4786)

#include <string>
#include <xparam_extend.h>
#include "../include/test_reg_reader.h"

using namespace std;
using namespace xParam;

PARAM_BEGIN_REG
// should also have a version for not NO_EXPLICIT_TEMPLATE_FUNC_ARGS

  PARAM_CLASS(reader);
  param_ctor(TypeTag<reader>(),ByVal<char>("val"));
  param_ctor(TypeTag<reader>(),ByVal<unsigned char>("val"));
  param_ctor(TypeTag<reader>(),ByVal<int>("val"));
  param_ctor(TypeTag<reader>(),ByVal<unsigned int>("val"));
  param_ctor(TypeTag<reader>(),ByVal<long>("val"));
  param_ctor(TypeTag<reader>(),ByVal<unsigned long>("val"));
  param_ctor(TypeTag<reader>(),ByVal<float>("val"));
  param_ctor(TypeTag<reader>(),ByVal<double>("val"));
  param_ctor(TypeTag<reader>(),ConstRef<string>("val"));

PARAM_END_REG

