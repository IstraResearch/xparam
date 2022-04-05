/*	Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand */

#pragma warning (disable: 4786)

#include <xparam_extend.h>
#include "../include/shapes.h"

using namespace xParam;

class Point_output {
  public:
    static ValueList sub_objects(const Point& p) {
      ValueList vl;
      return vl << Val(p.x) << Val(p.y);
    }
};

class Composite_output {
  public:
    static ValueList sub_objects(const Composite& c) {
      ValueList vl;
      return vl << Val(c.get_shapes());
    }
};

PARAM_BEGIN_REG

  PARAM_CLASS(Point);
    param_ctor(TypeTag<Point>(),ByVal<int>("x"),ByVal<int>("y"));
    param_output<Point,Point_output>();

  PARAM_ABSTRACT_CLASS(Shape);
    param_ptr_vector<Shape>();
	param_const_ptr_vector<Shape>();

  PARAM_CLASS(Composite);
    param_inheritance(DerivedTag<Composite>(),BaseTag<Shape>());
    param_ctor(TypeTag<Composite>(),ConstRef<std::vector<Shape*> >("shapes"));
    param_output<Composite,Composite_output>();

PARAM_END_REG
