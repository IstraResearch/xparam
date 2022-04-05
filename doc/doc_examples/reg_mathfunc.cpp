/*	Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand */

#pragma warning (disable: 4786)

#include <xparam_extend.h>
#include "../include/mathfunc.h"

using namespace xParam;

PARAM_BEGIN_REG

  PARAM_CLASS(ln);
    param_inheritance(DerivedTag<ln>(),BaseTag<ArithValue>());
    param_ctor(TypeTag<ln>(),ConstRef<ArithValue>("val"));

  param_class<root>("sqrt");
    param_inheritance(DerivedTag<root>(),BaseTag<ArithValue>());
    param_ctor(TypeTag<root>(),ConstRef<ArithValue>("val"));

PARAM_END_REG
