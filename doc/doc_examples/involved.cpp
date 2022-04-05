/*	Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand */

/*
    This program draws a shape of your choice.
    It demonstrates a more involved usage of the program. This
  includes registration of user classes, dynamic loading,
  polymorphism, and other high-power features of XParam.
    Note that this program does not know, at initial linkage
  time, how to draw ANY shape.
*/

#pragma warning (disable: 4786)

#include <iostream>
#include <xparam.h>
#include "../include/shapes.h"

using namespace xParam;
using namespace std;

int main(int argc, char* argv[])
{
  xparam_init();

  Shape* shape;
  Point size;
  try {
    ParamSet ps("This program draws a shape of your choice");
    ps << iParamPtrVar(shape,"shape!The shape you want to draw")
       << iParamVar(size,"size!The resolution you want to draw in",
            Val(Point(30,30)));
    ps.input(argc,argv);
    shape->draw(size);
    delete shape;
  } catch (Error e) {
    cerr << "Got following error - " << endl << e.what() << endl;
  }
  return 0;
}
