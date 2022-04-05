/*	Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand */

#include <iostream>
#include "../include/shapes.h"

using namespace std;

void Shape::draw(const Point& p) const
{
  Point curr;
  for(curr.y=0;curr.y!=p.y;++curr.y) {
    for(curr.x=0;curr.x!=p.x;++curr.x) {
      if (in_point(curr)) {
        cout << '#';
      } else {
        cout << ' ';
      }
    }
    cout << endl;
  }
}

bool Composite::in_point(const Point& p) const
{
  bool rc=false;
  for(std::vector<Shape*>::const_iterator i=shapes.begin();i!=shapes.end();++i)
  {
    rc|=(*i)->in_point(p);
  }
  return rc;
}

