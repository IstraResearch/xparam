#pragma warning (disable: 4786)

// This file tests feedback, error handling policy and string defaults.

#include <string>
#include <vector>
#include <xparam.h>
#include <iostream>

using namespace std;
using namespace xParam;

int a,c,d=17;
vector<string> b;

void test(ParamSet& ps,int size, char** input)
{
  try {
    ps << ioParamVar(a,"avalon");
    ps << ioParamVar(b,"avalanche",xParse("[ one,two ]"));
    ps << iParamVar(c,"input_only",Val(5));
    ps << oParamVar(d,"output_only");
    ps.input(size,input);
    ps.output();
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
}

int main(int argc, char* argv[])
{
  try {
    xparam_init();
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }

  {
    ParamSet ps;
    char* input[]={"progname","avalo=5 avalanc=[ a, b ]"};
    test(ps,2,input);
  }
  {
    ParamSet ps;
    char* input[]={"progname","avalo=5 avalanc=[ c, d ]"};
    ps.set_feedback_stream(cout);
    test(ps,2,input);
  }
  {
    ParamSet ps;
    char* input[]={"progname","avalo=5 avalanc=[ c, d ]"};
    ps.set_feedback_stream(cout);
    test(ps,2,input);
    ps.write_feedback();
  }
  {
    ParamSet ps;
    char* input[]={"progname","avalo=5 avalanc=[ c, d ]"};
    ps.set_feedback_stream(cout);
    ps.feedback_enabled(true);
    test(ps,2,input);
  }
  {
    ParamSet ps;
    char* input[]={"progname","avalo=5 avalanc=[ c, d ]"};
    ps.set_feedback_stream(cout);
    ps.feedback_enabled(true);
    ps.max_feedback_length(20);
    test(ps,2,input);
  }
  {
    ParamSet ps;
    char* input[]={"progname","avalo=5 avalanc=[ c, d ]"};
    ps.set_feedback_stream(cout);
    ps.feedback_enabled(true);
    ps.max_feedback_length(20);
    ps.max_feedback_length(0);
    test(ps,2,input);
  }
  {
    ParamSet ps;
    char* input[]={"progname","avalo=5 avalanc=[ c, d ]"};
    ps.set_feedback_stream(cout);
    ps.feedback_enabled(true);
    ps.max_feedback_length(20);
    ps.max_feedback_length(0);
    ps.feedback_enabled(false);
    test(ps,2,input);
  }
  {
    ParamSet ps;
    char* input[]={"progname","avalo=5 aval=[ c, d ]"};
    ps.set_feedback_stream(cout);
    ps.feedback_enabled(true);
    test(ps,2,input);
  }
  {
    ParamSet ps;
    char* input[]={"progname","avalo=5 aval=[ c, d ]"};
    ps.set_feedback_stream(cout);
    ps.feedback_enabled(true);
    ps.warning_is_error(false);
    test(ps,2,input);
  }
  {
    ParamSet ps;
    char* input[]={"progname","aval=5 avala=[ c, d ]"};
    ps.set_feedback_stream(cout);
    ps.feedback_enabled(true);
    ps.warning_is_error(false);
    test(ps,2,input);
  }
  {
    ParamSet ps;
    char* input[]={"progname","avalo=5 b=hello avala=[ c, d ]"};
    ps.set_feedback_stream(cout);
    ps.feedback_enabled(true);
    test(ps,2,input);
  }
  {
    ParamSet ps;
    char* input[]={"progname","avalo=5 b=hello avala=[ c, d ]"};
    ps.set_feedback_stream(cout);
    ps.feedback_enabled(true);
    ps.warning_is_error(false);
    test(ps,2,input);
  }
  {
    ParamSet ps;
    char* input[]={"progname","avalo=5 b=hello avala=[ c, d ]"};
    ps.set_feedback_stream(cout);
    ps.feedback_enabled(true);
    ps.warning_is_error(false);
    ps.ignore_unexpected(true);
    test(ps,2,input);
  }
  {
    ParamSet ps;
    char* input[]={"progname","avalo=5 b=hello avala=[ c, d ]"};
    ps.set_feedback_stream(cout);
    ps.feedback_enabled(true);
    ps.warning_is_error(false);
    ps.ignore_unexpected(true);
    ps.warning_is_error(true);
    test(ps,2,input);
  }
  {
    ParamSet ps;
    char* input[]={"progname","avalo=5"};
    ps.set_feedback_stream(cout);
    ps.feedback_enabled(true);
    test(ps,2,input);
  }
  {
    ParamSet ps;
    char* input[]={"progname","avalo=5"};
    ps.set_feedback_stream(cout);
    ps.feedback_enabled(true);
    ps.warning_is_error(false);
    test(ps,2,input);
  }
  {
    ParamSet ps;
    char* input[]={"progname","avala=[e,f,g]"};
    ps.set_feedback_stream(cout);
    ps.feedback_enabled(true);
    test(ps,2,input);
  }
  {
    ParamSet ps;
    char* input[]={"progname","avala=:","h"};
    ps.set_feedback_stream(cout);
    ps.feedback_enabled(true);
    ps.warning_is_error(false);
    test(ps,3,input);
  }
  return 0;
}
