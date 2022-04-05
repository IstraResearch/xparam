/*	Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * As a special exception, the copyright holders give permission
 * for additional uses of the text contained in its release of XPARAM.
 *
 * The exception is that, if you link the XPARAM library with other files
 * to produce an executable, this does not by itself cause the
 * resulting executable to be covered by the GNU General Public License.
 * Your use of that executable is in no way restricted on account of
 * linking the XPARAM library code into it.
 *
 * This exception does not however invalidate any other reasons why
 * the executable file might be covered by the GNU General Public License.
 *
 * If you write modifications of your own for XPARAM, it is your choice
 * whether to permit this exception to apply to your modifications.
 * If you do not wish that, delete this exception notice.  
 */

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
