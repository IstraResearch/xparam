/*	Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand */

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
      
