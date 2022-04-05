/*	Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand */

#pragma warning (disable: 4786)

#include <xparam_extend.h>
#include "../include/circle.h"

using namespace xParam;

class Circle_output {
  public:
    static ValueList sub_objects(const Circle& c) {
      ValueList vl;
      return vl << Val(c.get_center()) << Val(c.get_radius());
    }
};

PARAM_BEGIN_REG

  PARAM_CLASS(Circle);
    param_inheritance(DerivedTag<Circle>(),BaseTag<Shape>());
    param_ctor(TypeTag<Circle>(),ConstRef<Point>("center"),
      ByVal<int>("radius"));
    param_output<Circle,Circle_output>();

PARAM_END_REG
