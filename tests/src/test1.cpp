#pragma warning (disable: 4786)

#include <string>
#include <iostream>
#include <fstream>
#include <xparam.h>

using namespace std;
using namespace xParam;

int main(int argc, char* argv[])
{
  int d=2;
	  // Thrown errors:
	  // no name found in "name ! desc" string
  try {

    xparam_init();

    ParamSet ps;
    ps << iParamVar(d,"#4652afg");
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
  try {
    ParamSet ps;
    ps << iParamVar(d,"   !afg");
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
	  // first char in name is digit
  try {
    ParamSet ps;
    ps << iParamVar(d," 3rdfromleft! third from left ");
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
	  // no ! before description
  try {
    ParamSet ps;
    ps << iParamVar(d,"hello there!");
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
	  // inputting a non-input parameter
  try {
    ParamSet ps;
    ps << oParamVar(d,"d");
    const char* input[]={"test1","d=7"};
    ps.input(2,input);
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
	  // inputting an undefined parameter
  try {
    ParamSet ps;
    ps << iParamVar(d,"d");
    ps.input("e=7");
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
	  // error parsing value
  // This is only an example of parser errors. Extensive tests will follow.
  try {
    ParamSet ps;
    ps << iParamVar(d,"d");
    const char* input[]={"test1","d=int(7"};
    ps.input(2,input);
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
	  // file not found
  try {
    ParamSet ps;
    ps << iParamVar(d,"d");
    const char* input[]={"test1","@non_existent_file"};
    ps.input(2,input);
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
	  // Access of unregistered type
  try {
    ParamSet ps;
    ps << iParamVar(d,"d");
    const char* input[]={"test1","d=non_existent_class()"};
    ps.input(2,input);
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
  try {
    ParamSet ps;
    ps << iParamVar(d,"d");
    const char* input[]={"test1","d=unregistered_type()"};
    ps.input(2,input);
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
	  // Integer too large
  try {
    ParamSet ps;
    ps << iParamVar(d,"d");
    const char* input[]={"test1","d=76542979874298718347"};
    ps.input(2,input);
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
	  // Integer too large
  try {
    ParamSet ps;
    char ch;
    ps << iParamVar(ch,"ch");
    const char* input[]={"test1","ch=3000000000"};
    ps.input(2,input);
    cout << "ch: " << Val(ch) << endl;
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
	  // Integer too large, but can still fit an unsigned long
  try {
    ParamSet ps;
    ps << iParamVar(d,"d");
    const char* input[]={"test1","d=3000000000"};
    ps.input(2,input);
    cout << "d: " << Val(d) << endl;
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
	  // no ctor found <- no matching path in "create"
	  //   (should this be an assert?)
	  // no conversion path found
  try {
    ParamSet ps;
    string s;
    ps << iParamVar(s,"s");
    const char* input[]={"test1","s=duck()"};
    ps.input(2,input);
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
  try {
    ParamSet ps;
    ps << iParamVar(d,"d");
    const char* input[]={"test1","d=duckling()"};
    ps.input(2,input);
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
  return 0;
}
