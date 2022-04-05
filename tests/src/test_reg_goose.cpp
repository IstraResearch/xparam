#pragma warning (disable: 4786)

#include <xparam_extend.h>
#include "../include/test_reg_goose.h"

using namespace xParam;

class GooseOutputFunctor {
  public:
    static ValueList sub_objects(const goose& g) {
      ValueList vl;
      return vl << Val(g.num());
    }
};

PARAM_BEGIN_REG

PARAM_CLASS(gooseberry);
  param_ctor(TypeTag<gooseberry>());
  param_ctor(TypeTag<gooseberry>(),ByVal<int>("i"));

param_const("duffy",gooseberry(314));

PARAM_CLASS(goose);
  param_ctor(TypeTag<goose>());
  param_ctor(TypeTag<goose>(),ByVal<int>("i"));
  param_ctor(TypeTag<goose>(),ConstRef<gooseberry>("d"));
  param_output<goose,GooseOutputFunctor>();

goose groucho=15;

PARAM_CONST(groucho);

PARAM_END_REG
