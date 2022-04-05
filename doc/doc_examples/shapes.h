#ifndef __SHAPES_H__
#define __SHAPES_H__

/*	Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand */

#include<vector>

struct Point {
  int x,y;
  Point(void) {}
  Point(int _x, int _y) : x(_x), y(_y) {}
};

class Shape {
  public:
    virtual bool in_point(const Point& p) const=0;
    void draw(const Point& p) const;
};

class Composite : public Shape {
  private:
    std::vector<Shape*> shapes;
  public:
    Composite(const std::vector<Shape*>& _shapes) : shapes(_shapes) {}
    virtual bool in_point(const Point& p) const;
    const std::vector<Shape*>& get_shapes(void) const { return shapes; }
};

#endif
