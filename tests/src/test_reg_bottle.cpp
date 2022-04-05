#pragma warning (disable: 4786)

#include <xparam_extend.h>
#include "../include/test_reg_goose.h"
#include "../include/test_bottle.h"

using namespace std;
using namespace xParam;

class bottle_output_functor {
  public:
    static ValueList sub_objects(const bottle& b) {
      ValueList vl;
      return vl << Val(b.msg());
    }
};

PARAM_BEGIN_REG
  param_map<goose,bottle>();
  param_ptr_map<goose,bottle>();
  param_const_ptr_map<goose,bottle>();

  PARAM_CLASS(bottle); // make sure that bottle is registered AFTER.
  param_ctor(TypeTag<bottle>());
  param_ctor(TypeTag<bottle>(),ConstRef<string>("message"));
  param_output<bottle,bottle_output_functor>();
PARAM_END_REG
