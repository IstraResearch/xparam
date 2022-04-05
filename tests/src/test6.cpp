#pragma warning (disable: 4786)

#include <string>
#include <iostream>
#include <fstream>
#include <xparam.h>
#include "../include/test_reg_duck.h"

using namespace std;
using namespace xParam;

int main(int argc, char* argv[])
{
  int d=2;
  try {
    try {

      xparam_init();

// multiple declarations of the same name with different parameters
      ParamSet ps;
      char ch='a';
      ps << oParamVar(ch,"d")
         << oParamVar(d,"d");
      cout << ps;
    } catch(Error e) {
      cout << "Got following error - " << endl << e.what() << endl;
    }
    try {
// multiple declarations of the same name with different parameters
      ParamSet ps;
      string a;
      ps << iParamVar(a,"a")
         << oParamVar(d,"a");
      ifstream ifs("data/test_file4.txt");
      ifs >> ps;
      cout << ps;
    } catch(Error e) {
      cout << "Got following error - " << endl << e.what() << endl;
    }
    try {
// multiple declarations of the same name with same parameters
      ParamSet ps;
      string a;
      ps << ioParamVar(a,"a")
         << ioParamVar(a,"a");
      ifstream ifs("data/test_file4.txt");
      ifs >> ps;
      cout << ps;
    } catch(Error e) {
      cout << "Got following error - " << endl << e.what() << endl;
    }
// Multiple assignments - should be Ok
    {
      ParamSet ps;
      string a;
      ps << ioParamVar(a,"a");
      const char* input[]={"test6", "a=\"original definition of a\""};
      ps.input(2,input);
      ifstream ifs("data/test_file4.txt");
      ifs >> ps;
      cout << ps;
    }
    {
      ParamSet ps;
      duckling duck1,duck2,duck3,duck4,duck5;
      duckling *duckp1,*duckp2,*duckp3,*duckp4,*duckp5=NULL;
      ps << iParamVar(duck1,"duck1 ! my first duck")
         << iParamVar(duck2,"duck2 ! duckling with default",Val(duckling("default val")))
         << ioParamVar(duck3,"duck3! with output",Val(duckling(7,8)))
         << ioParamVar(duck4,"duck4! No default")
         << oParamVar(duck5,"duck5 ! output only")
         << iParamPtrVar(duckp1,"duckp1 ! my first duck")
         << iParamPtrVar(duckp2,"duckp2 ! duckling with default",PtrVal(new duckling("default val")))
         << ioParamPtrVar(duckp3,"duckp3! with output",PtrVal(new duckling(7,8)))
         << ioParamPtrVar(duckp4,"duckp4! No default")
        << oParamPtrVar(duckp5,"duckp5 ! output only")
         ;

      const char* input[]={"test1","duck1=duckling() duck2=duckling() duck4",
                           "=duckling(5.0,0.7) duckp1=NULL",
                           "duckp3=duckling(\"overriding default\") ",
                           "duckp4=NULL ; duckp4=This should have no effect."};
      ps.input(5,input);
      cout << ps;
      cout << "duck1: " << duck1.whoami() << endl;
      cout << "duck2: " << duck2.whoami() << endl;
      cout << "duckp1: " << PtrVal(duckp1) << endl;
      cout << "duckp2: " << duckp2->whoami() << endl;

      delete duckp1;
      delete duckp2;
      delete duckp3;
      delete duckp4;
      delete duckp5;
    }
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }

// This shouldn't work because we registered it as an explicit conversion.
  try {
    ParamSet ps;
    ducky d(1);
    ps << iParamVar(d,"d");
    const char* input[]={"test6", "d=int(7)"};
    ps.input(2,input);
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }

  try {
    ParamSet ps;
    ducky d(1);
    ps << iParamVar(d,"d");
    const char* input[]={"test6", "d=ducky(7)"};
    ps.input(2,input);
    cout << d.whoami() << endl;
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }

  try {
    ParamSet ps;
    ducky d(1);
    ps << iParamVar(d,"d");
    const char* input[]={"test6", "d=hello"};
    ps.input(2,input);
    cout << d.whoami() << endl;
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }

  try {
    ParamSet ps;
    ducky d(1);
    ps << iParamVar(d,"d");
    const char* input[]={"test6", "d=ducky(hello)"};
    ps.input(2,input);
    cout << d.whoami() << endl;
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }

  try {
    ParamSet ps;
    ducky d(1);
    ps << iParamVar(d,"d");
    const char* input[]={"test6", "d=ducky()"};
    ps.input(2,input);
    cout << d.whoami() << endl;
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }

// This shouldn't work because we registered it as an explicit creator.
  try {
    ParamSet ps;
    ducky d(1);
    ps << iParamVar(d,"d");
    const char* input[]={"test6", "d=double(3.5)"};
    ps.input(2,input);
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }

  try {
    ParamSet ps;
    ducky d(1);
    ps << iParamVar(d,"d");
    const char* input[]={"test6", "d=ducky(3.6)"};
    ps.input(2,input);
    cout << d.whoami() << endl;
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }

          // extract<T> called on value of type S
	  // get_owned_copy<T> called on value of type S
	  // error while printing (somebody else threw error)
	  // error while downcasting (somebody else threw error)
	  // error in xparam_name() (somebody else)
	  // error in create_value() (somebody else)
	  // error in ctor (somebody else threw error)
	return 0;
}
