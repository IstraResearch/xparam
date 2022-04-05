#pragma warning (disable: 4786)

#include <xparam.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../include/test_reg_goose.h"

using namespace std;
using namespace xParam;

void print_param_information(const xParam_internal::Param& p)
{
  cout << "name: " << p.name() << endl;
  cout << "description: " << p.description() << endl;
//  cout << "type_info: " << p.static_type_info().name() << endl;
  cout << "has given value: " << p.has_given_value() << endl;
  cout << "has default: " << p.has_default() << endl;
  cout << "was assigned to: " << p.was_assigned_to() << endl;
  cout << "is input: " << p.is_input() << endl;
  cout << "is output: " << p.is_output() << endl;
  cout << endl;
}

class test_object {
  private:
    ParamSet ps2;
    int member;
  public:
    test_object(ParamSet& ps) {
      ps2 << iParamVar(member,"member") << Match(EXACT);
      ps.import(ps2);
    }
    void print_m(void) {
      cout << "Testing that we are still EXACT..." << endl;
      try {
        cout << "m: " << ps2["m"].name() << endl;
      } catch (Error e) {
        cout << "Error: " << e.what() << endl;
      }

      vector<string> names=ps2.names();
      cout << "PS2 Names:";
      vector<string>::const_iterator i;
      for(i=names.begin();i!=names.end();++i) {
        cout << ' ' << (*i);
      }
      cout << endl;

      cout << "member was assigned to: " << ps2["member"].was_assigned_to() << endl;
      cout << "Should be: 17" << endl;
      cout << "Result:    " << member << endl;
    }
};

class test_object2 {
  private:
    int next;
  public:
    test_object2(ParamSet& ps) {
      ParamSet ps2;
      ps2 << iParamVar(next,"next") << Match(EXACT);
      ps.import(ps2);
    }
    void print_n(void) {
      cout << "Should be: 19" << endl;
      cout << "Result:    " << next << endl;
    }
};

int main(void)
{
  try {

  xparam_init();

  gooseberry d;
  goose g;
  ParamSet ps;
  ps << iParamVar(d,"d")
     << iParamVar(g,"g");

  cout << "Trying duplicate parameters..." << endl;
  try {
    ps << iParamVar(g,"g");
  } catch (Error e) {
    cout << "Error: " << e.what() << endl;
  }

  cout << "Trying default multiple assignment mode (last holds)..." << endl;
  cout << "Should be: 7" << endl;
  {
    char* argv[]={"progname","d=5 d=7"};
    ps.input(2,argv,false);
    cout << "Result:    " << d.num() << endl;
  }

  cout << "Trying first holds mode..." << endl;
  cout << "Should be: 7" << endl;
  {
    char* argv[]={"progname","d=4 d=3"};
    ps << MultipleAssign(FIRST_HOLDS);
    ps.input(2,argv,false);
    cout << "Result:    "  << d.num() << endl;
  }

  cout << "Trying \'is error\' mode..." << endl;
  try {
    char* argv[]={"progname","d=1"};
    ps << MultipleAssign(IS_ERROR);
    ps.input(2,argv,false);
  } catch(Error e) {
    cout << "Error: " << e.what() << endl;
  }

  cout << "Trying last holds mode explicitly..." << endl;
  cout << "Should be: 9" << endl;
  {
    char* argv[]={"progname","d=8 d=9"};
    ps << MultipleAssign(LAST_HOLDS);
    ps.input(2,argv,false);
    cout << "Result:    "  << d.num() << endl;
  }

  cout << "Trying switching to first_holds by method..." << endl;
  cout << "Should be: 9" << endl;
  {
    char* argv[]={"progname","d=2 d=6"};
    ps.multiple_assign(FIRST_HOLDS);
    ps.input(2,argv,false);
    cout << "Result:    "  << d.num() << endl;
  }

  cout << "Trying switching to is_error by method..." << endl;
  try {
    char* argv[]={"progname","d=10"};
    ps.multiple_assign(IS_ERROR);
    ps.input(2,argv,false);
  } catch(Error e) {
    cout << "Error: " << e.what() << endl;
  }

  cout << "Trying switching to last_holds by method..." << endl;
  cout << "Should be: 12" << endl;
  {
    char* argv[]={"progname","d=11 d=12"};
    ps.multiple_assign(LAST_HOLDS);
    ps.input(2,argv,false);
    cout << "Result:    "  << d.num() << endl;
  }

  int tomato, tomato_juice, tobacco, toba, tomato_drink;
  ps << ioParamVar(tomato,"tomato",Val(22))
     << iParamVar(tomato_juice,"tomato_juice ! boring juice")
     << iParamVar(tobacco,"tobacco")
     << iParamVar(toba,"toba")
     << iParamVar(tomato_drink,"tomato_drink");

  cout << "Testing prefix (default) mode..." << endl;
  cout << "tom->tomato: " << ps["tom"].name() << endl;
  cout << "tomato->tomato: " << ps["tomato"].name() << endl;
  cout << "tobacco->tobacco: " << ps["tobacco"].name() << endl;
  cout << "Trying two ambiguities..." << endl;
  try {
    cout << "t: " << ps["t"].name() << endl;
  } catch(Error e) {
    cout << "Error: " << e.what() << endl;
  }
  try {
    cout << "tomato_: " << ps["tomato_"].name() << endl;
  } catch (Error e) {
    cout << "Error: " << e.what() << endl;
  }
  cout << "Trying no match..." << endl;
  try {
    cout << "time: " << ps["time"].name() << endl;
  } catch (Error e) {
    cout << "Error: " << e.what() << endl;
  }

  cout << "Testing exact mode..." << endl;
  ps << Match(EXACT);
  try {
    cout << "tom->tomato: " << ps["tom"].name() << endl;
  } catch(Error e) {
    cout << "Error: " << e.what() << endl;
  }
  cout << "tomato->tomato: " << ps["tomato"].name() << endl;
  cout << "tobacco->tobacco: " << ps["tobacco"].name() << endl;
  cout << "Trying two ambiguities..." << endl;
  try {
    cout << "t: " << ps["t"].name() << endl;
  } catch(Error e) {
    cout << "Error: " << e.what() << endl;
  }
  try {
    cout << "tomato_: " << ps["tomato_"].name() << endl;
  } catch (Error e) {
    cout << "Error: " << e.what() << endl;
  }
  cout << "Trying no match..." << endl;
  try {
    cout << "time: " << ps["time"].name() << endl;
  } catch (Error e) {
    cout << "Error: " << e.what() << endl;
  }

  cout << "Testing prefix (explicit) mode..." << endl;
  ps << Match(PREFIX);
  cout << "tom->tomato: " << ps["tom"].name() << endl;
  cout << "tomato->tomato: " << ps["tomato"].name() << endl;
  cout << "tobacco->tobacco: " << ps["tobacco"].name() << endl;
  cout << "Trying two ambiguities..." << endl;
  try {
    cout << "t: " << ps["t"].name() << endl;
 } catch(Error e) {
    cout << "Error: " << e.what() << endl;
  }
  try {
    cout << "tomato_: " << ps["tomato_"].name() << endl;
  } catch (Error e) {
    cout << "Error: " << e.what() << endl;
  }
  cout << "Trying no match..." << endl;
  try {
    cout << "time: " << ps["time"].name() << endl;
  } catch (Error e) {
    cout << "Error: " << e.what() << endl;
  }

  cout << "Testing exact mode with method..." << endl;
  ps.match(EXACT);
  try {
    cout << "tom->tomato: " << ps["tom"].name() << endl;
  } catch(Error e) {
    cout << "Error: " << e.what() << endl;
  }
  cout << "tomato->tomato: " << ps["tomato"].name() << endl;
  cout << "tobacco->tobacco: " << ps["tobacco"].name() << endl;
  cout << "Trying two ambiguities..." << endl;
  try {
    cout << "t: " << ps["t"].name() << endl;
  } catch(Error e) {
    cout << "Error: " << e.what() << endl;
  }
  try {
    cout << "tomato_: " << ps["tomato_"].name() << endl;
  } catch (Error e) {
    cout << "Error: " << e.what() << endl;
  }
  cout << "Trying no match..." << endl;
  try {
    cout << "time: " << ps["time"].name() << endl;
  } catch (Error e) {
    cout << "Error: " << e.what() << endl;
  }

  cout << "Testing prefix mode with method..." << endl;
  ps.match(PREFIX);
  cout << "tom->tomato: " << ps["tom"].name() << endl;
  cout << "tomato->tomato: " << ps["tomato"].name() << endl;
  cout << "tobacco->tobacco: " << ps["tobacco"].name() << endl;
  cout << "Trying two ambiguities..." << endl;
  try {
    cout << "t: " << ps["t"].name() << endl;
  } catch(Error e) {
    cout << "Error: " << e.what() << endl;
  }
  try {
    cout << "tomato_: " << ps["tomato_"].name() << endl;
  } catch (Error e) {
    cout << "Error: " << e.what() << endl;
  }
  cout << "Trying no match..." << endl;
  try {
    cout << "time: " << ps["time"].name() << endl;
  } catch (Error e) {
    cout << "Error: " << e.what() << endl;
  }

  cout << "Testing with input..." << endl;
  {
    char* argv[]={"progname","tomato_j=21"};
    ps.input(2,argv,false);
    cout << "Should be 21:" << endl;
    cout << "Result:   " << tomato_juice << endl;
  }

  cout << "Testing param information..." << endl;
  print_param_information(ps["tomato_jui"]);
  print_param_information(ps["tom"]);
  print_param_information(ps["g"]);

  cout << "Testing constants..." << endl;
  {
    char* argv[]={"progname", "d=duffy g=duffy"};
    ps.input(2,argv,false);
    cout << "should be: 314, 628" << endl;
    cout << "Result:    " << d.num() << ", " << g.num() << endl;
  }

  cout << "Testing import, with persistent foreign paramset..." << endl;
  test_object test(ps);
  {
    vector<string> names=ps.names();
    cout << "PS Names:";
    vector<string>::const_iterator i;
    for(i=names.begin();i!=names.end();++i) {
      cout << ' ' << (*i);
    }
    cout << endl;
  }
  {
    char* argv[]={"progname","m=17"};
    ps.input(2,argv,false);
    cout << "m was assigned to: " << ps["m"].was_assigned_to() << endl;
    test.print_m();
  }
  
  cout << "Testing import, with intermittent foreign paramset..." << endl;
  test_object2 test2(ps);
  {
    vector<string> names=ps.names();
    cout << "PS Names:";
    vector<string>::const_iterator i;
    for(i=names.begin();i!=names.end();++i) {
      cout << ' ' << (*i);
    }
    cout << endl;
  }
  {
    char* argv[]={"progname","n=19"};
    ps.input(2,argv,false);
    cout << "n was assigned to: " << ps["n"].was_assigned_to() << endl;
    test2.print_n();
  }

  {
    cout << "Testing for constants of user defined type." << endl;
    char* argv[]={"progname","g=groucho"};
    ps.input(2,argv,false);
    cout << "Val-g: " << Val(g) << endl;
  }

  {
    cout << "Testing constants read from stream." << endl;
    ifstream ifs("data/test_file6.txt");
    gooseberry a;
    goose b;
    ifs >> Var(a) >> Var(b);
    cout << "Stream vals: " << Val(a) << ' ' << Val(b) << endl;
  }
      
  } catch (Error e) {
    cout << "This is an unexpected error: " << endl;
    cout << e.what() << endl;
  }

  return 0;
}
