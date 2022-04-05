#ifndef __CIRCLE_H__
#define __CIRCLE_H__

/*	Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand */

#include "shapes.h"

class Circle : public Shape {
  private:
    Point center;
    int radius;
  public:
    Circle(const Point& _center, int _radius)
      : center(_center), radius(_radius) {}
    virtual bool in_point(const Point& p) const;
    const Point& get_center(void) const { return center; }
    const int get_radius(void) const { return radius; }
};

#endif
