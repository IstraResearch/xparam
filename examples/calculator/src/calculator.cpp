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

#pragma warning (disable: 4786)

#include <xparam.h>
#include "../include/functions.h"

using namespace xParam;

int main(int argc,char* argv[])
{
  xparam_init();

  ParamSet ps;
  ps << "This program is a calculator."
     << "Usage:"
     << "The calculator receives its inputs as an XParam object stream from"
     << "stdin and outputs the results to stdout. Errors are printed on the"
     << "standard error."
     << "The commands 'add', 'sub', 'mul' and 'div' have been preprogrammed,"
     << "but the calculator is extensible, and can integrate new functions."
     << "The commands 'ln' and 'sqrt' have been added to demonstrate how"
     << "extensions can be added."
     << "The calculator works on doubles, and recognizes string literals"
     << "as variable names. Use the function 'def' to define a new variable."
     << "For example:"
     << "add(3,mul(2,4)) will return 3+2*4=11."
     << "def(tax,add(1,div(17,100))) will cause variable 'tax' to receive"
     << "                            the value 1+17/100=1.17."
     << "mul(tax,2.0) will then result in 2.34."
     << "[def(a,8),def(b,7)] can also be used for several consecutive"
     << "                    assignments."
     << "You can also load from file: use the command \"@data/constants.dat\","
     << "for example, to load the constants Pi and E."
     << "We have also imported constants from <math.h>, such as M_LOG2E.";

  ps.input(argc,argv);

  Loader loader(std::cin);
  Saver saver(std::cout);
  Expression* exp;
  ArithValue* val;
  while (!loader.eof()) {
    exp=NULL;
    try {
      loader >> PtrVar(exp);
      if (!exp)
        std::cerr << "Error: NULL is not a valid argument." << std::endl;
      val = dynamic_cast<ArithValue*>(exp);
      if (val) saver << Val((double)*val);
    } catch(Error e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
    delete exp;
  }
  return 0;
}
      
