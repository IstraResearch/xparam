#ifndef __test_reg_coordinate_h__
#define __test_reg_coordinate_h__

#pragma warning (disable: 4786)

#include <string>
#include <iostream>
#include <fstream>
#include <xparam_extend.h>


class coordinate {
  private:
    int x,y;
  public:
    coordinate(int a, int b) : x(a), y(b) {}
  friend class coordinate_output_functor;
};

class coordinate_output_functor {
  public:
    static xParam::ValueList sub_objects(const coordinate& c) {
      xParam::ValueList vl;
      return vl << xParam::Val(c.x) << xParam::Val(c.y);
    }
};

#endif
