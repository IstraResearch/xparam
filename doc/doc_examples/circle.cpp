/*	Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand */

#pragma warning (disable: 4786)

#include "../include/circle.h"

bool Circle::in_point(const Point& p) const
{
  int dist=(p.x-center.x)*(p.x-center.x)+(p.y-center.y)*(p.y-center.y);
  return ((radius*radius)>=dist)&&((radius-1)*(radius-1)<dist);
}
