#pragma warning (disable: 4786)

#include <xparam_extend.h>
#include "../include/test_reg_goose.h"

using namespace std;
using namespace xParam;

PARAM_BEGIN_REG
  param_pair<goose,double>();
  param_map<goose,string>();
PARAM_END_REG
