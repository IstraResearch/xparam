#pragma warning (disable: 4786)

#include <xparam_extend.h>
#include "../include/test_reg_goose.h"

using namespace std;
using namespace xParam;

PARAM_BEGIN_REG
  param_vector<goose>();
  param_ptr_vector<goose>();
  param_const_ptr_vector<goose>();

  param_list<goose>();
  param_ptr_list<goose>();
  param_const_ptr_list<goose>();

  param_set<goose>();
  
PARAM_END_REG
