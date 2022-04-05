#pragma warning (disable: 4786)

#include <string>
#include <iostream>
#include <fstream>
#include <xparam.h>
#include "../include/test_reg_duck.h"
#include "../include/test_reg_reader.h"

using namespace std;
using namespace xParam;

int main(int argc, char* argv[])
{
  int d=2;
  try {
    {

      xparam_init();

      cout << "duckling print1: " << Val(duckling(17)) << endl;
      cout << "duckling print2: ";
      Saver(cout) << Val(duckling(15));
      Saver(cout) << Val(1);
      Saver(cout) << Val(1.0);
      Saver(cout) << Val(1.0f);
      Saver(cout) << Val(1u);
      Saver(cout) << Val(1l);
      Saver(cout) << Val(1ul);
      Saver(cout) << Val('1');
      Saver(cout) << Val("1");
      Saver(cout) << Val(((unsigned char)(1)));
      cout << Val(1) << endl;
      cout << Val(1.0) << endl << Val(1.0f) <<  endl;
      cout << Val(1u) << endl << Val(1l) << endl << Val(1ul) << endl;
      cout << Val('1') << endl << Val("1") << endl;

      {
        ifstream ifs("data/test_file5.txt");
        reader r(8);
        for(int i=0;i<13;++i) {
          Loader(ifs) >> Var(r);
          cout << r.describe() << endl;
        }
      }
      ifstream ifs("data/test_file3.txt");
      char c;
      char* cp;
      Loader(ifs) >> Var(c);
      ifstream ifs2("data/test_file3.txt");
      Loader(ifs2) >> PtrVar(cp);
      cout << "This is c: " << c << endl;
      cout << "This is cp: " << (*cp) << endl;
      cout << "This is Val(c)" << Val(c) << endl;
      cout << "This is PtrVal(cp)" << PtrVal(cp) << endl;
      Saver(cout) << Val(c);
      Saver(cout) << PtrVal(cp);
      delete cp;
    }
    {
      ParamSet ps;
      archduck* a;
      vector<duck> b;
      vector<duck> c;
      ps << iParamPtrVar(a,"a")
         << iParamVar(b,"b")
         << iParamVar(c,"c")
         << ioParamVar(d,"d");
      const char* input[]={"test1","@data/test_file1.txt"};
      ps.input(2,input);
      ps.output(cout);
      cout << a->whoami() << endl;
      cout << (b[0].whoami()) << endl;
      cout << (b[1].whoami()) << endl;
      cout << (c[0].whoami()) << endl;
      cout << (c[1].whoami()) << endl;
      cout << "Polymorphic output: " << PtrVal(a) << endl;
      delete a;
    }
// multiple declaration - should be OK.
    try {
      ParamSet ps;
      archduck* a;
      vector<duck> b;
      vector<duck> c;
      ps << iParamPtrVar(a,"a")
         << iParamVar(b,"b")
         << iParamVar(c,"c")
         << ioParamVar(d,"d");
      const char* input[]={"test1","@data/test_file1.txt @data/test_file4.txt"};
      ps.input(2,input);
      cout << "Polymorphic output: " << PtrVal(a) << endl;
      delete a;
    }
    catch(Error e) {
      cout << "Got following error - " << endl << e.what() << endl;
    }
    {
// const type support.
      ParamSet ps;
      const char ch='a';
      ps << oParamVar(ch,"ch")
         << iParamVar(d,"d");
      ps.output(cout);
    }
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
  return 0;
}
