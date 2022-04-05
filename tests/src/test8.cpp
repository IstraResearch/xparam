#pragma warning (disable: 4786)

#include <iostream>
#include <xparam_extend.h>

using namespace xParam;
using namespace std;

enum DOW { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };

enum Month { January, February, March, April, May, June, July, August,
             September, October, November, December };

PARAM_BEGIN_REG

PARAM_ENUM_VAL(Wednesday);
PARAM_ENUM(DOW);
PARAM_ENUM_VAL(Tuesday);

PARAM_ENUM(Month);
PARAM_ENUM_VAL(March);

PARAM_END_REG

int main(void)
{
  try {

  xparam_init();

  int v=7;
  const int c=8;
  int* vp=NULL;
  int* const pc=new int(9);
  const int* cp=pc;
  const int* const cpc=pc;

  cout << "Testing input..." << endl;
  {
    ParamSet ps;
    ps << iParamVar(v,"v");
    ps << iParamPtrVar(vp,"vp");
    char* argv[]={"progname","v=1 vp=2"};
    ps.input(2,argv);
    ps.output();
  }
  cout << "Testing input/output..." << endl;
  {
    ParamSet ps;
    ps << ioParamVar(v,"v");
    ps << ioParamPtrVar(vp,"vp");
    char* argv[]={"progname","v=3 vp=4"};
    ps.input(2,argv);
    ps.output();
  }
  cout << "Testing output..." << endl;
  {
    ParamSet ps;
    ps << oParamVar(v,"v");
    ps << oParamVar(c,"c");
    ps << oParamPtrVar(vp,"vp");
    ps << oParamPtrVar(cp,"cp");
    ps << oParamPtrVar(pc,"pc");
    ps << oParamPtrVar(cpc,"cpc");
    char* argv[]={"progname"};
    ps.input(1,argv);
    ps.output();
  }
  cout << "Testing serialization..." << endl;

  cout << Val(v) << endl;
  cout << Val(c) << endl;
  cout << PtrVal(vp) << endl;
  cout << PtrVal(cp) << endl;
  cout << PtrVal(pc) << endl;
  cout << PtrVal(cpc) << endl;

  delete vp;
  delete pc;

  cout << "Testing enums..." << endl;
  {
    DOW dow1,dow2;
    Month m;
    ParamSet ps;
    ps << ioParamVar(dow1,"dow1") << ioParamVar(dow2,"dow2");
    ps << ioParamVar(m,"m");
    char* argv[]={"progname","dow1=Wednesday dow2=DOW(4) m=March"};
    ps.input(2,argv);
    cout << "dow1: " << dow1 << ' ' << Val(Wednesday) << endl;
    cout << "dow2: " << dow2 << ' ' << Val(Friday) << endl;
    cout << "m   : " << m    << ' ' << Val(March) << endl;
    ps.output();
  }

  } catch (Error e) {
    cout << "Unexpected error:" << endl;
    cout << e.what() << endl;
  }
  return 0;
}
