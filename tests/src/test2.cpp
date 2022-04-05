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
// ambiguity in construction
  try {

    xparam_init();

    ParamSet ps;
    duckling duckula;
    ps << iParamVar(duckula,"d");
    const char* input[]={"test1","d=duckling(0.5,7)"};
    ps.input(2,input);
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
	  // tried to output object with no output function
  try {
    ParamSet ps;
    duck duckula;
    ps << ioParamVar(duckula,"d");
    const char* input[]={"test1","d=duck(\"Testing output\")"};
// this used to work without the escaped double quotes.
    ps.input(2,input);
    ps.output(cout);
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
	  // impossible conversion
  try {
    ParamSet ps;
    string s;
    ps << iParamVar(s,"s",Val(8));
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
	  // more than one user defined conversion is not allowed
  try {
    ParamSet ps;
    ps << iParamVar(d,"d",Val("I am a string"));
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
	  // ambiguity in conversion
  try {
    ParamSet ps;
    ps << iParamVar(d,"d",Val(duck()));
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
  return 0;
}
