#pragma warning (disable: 4786)

#include <string>
#include <iostream>
#include <fstream>
#include <xparam.h>
#include "../include/test_reg_duck.h"
#include "../include/test_reg_marker.h"

using namespace std;
using namespace xParam;

int main(int argc, char* argv[])
{
  int d=2;
/*
  Skipping this test, because type_info.name() returns different strings
  on different systems.

	  // NULL passed
  try {

    // xparam_init();

    ParamSet ps;
    ps << iParamVar(d,"d");
    const char* input[]={"test1","d=NULL"};
    ps.input(2,input);
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
*/
  try {

    xparam_init();

    {
      cout << "Now testing that ptr passers work as expected." << endl;
      ParamSet ps;
      duckling duckula;
      ps << iParamVar(duckula,"d");
      const char* input[]={"test1","d=","duckling(marker(1),marker(2),marker(",
                                        "3),marker(4))"};
      ps.input(4,input);
      cout << "all 4 ptrs should have been deleted by now." << endl;
    }
    {
// This worked once. Then it started saying this:
// Got following error - 
// while parsing assignment to parameter 'd':
// while parsing element 0 of value list:
// while parsing constructor for 'duckling':
// in create_value() - tried to access unregistered type f

      cout << "Now testing correct handling of static objects." << endl;
      ParamSet ps;
      duckling duckula;
      ps << ioParamVar(duckula,"d");
      const char* input[]={"test1","d","=duckling(static_marker()",
                   ",static_marker(),static_marker(),static_marker())"};
      ps.input(4,input);
      cout << "all 4 ptrs should have been deleted by now." << endl;
      ps.output(cout);
	return 0;
    }
  } catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
  return 0;
}
