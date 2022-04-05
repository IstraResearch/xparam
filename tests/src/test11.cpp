#pragma warning (disable: 4786)

#include <iostream>
#include <vector>
#include <string>
#include <xparam.h>
#include "../include/test_reg_everything2.h"

using namespace xParam;
using namespace std;

int main(void)
{
  try {

  xparam_init();

  cout << "Testing constructors..." << endl;
  {
    vector<everything2> v;
    long double l;
    ParamSet ps;
    ps << ioParamVar(v,"v")
       << ioParamVar(l,"l");
    const char* argv[]={"progname",
                  "v=true, '1', uchar('1'), short(1), ushort(1),",
                  "1, 1u, 1U, 1l, 1L, 1UL, 1ul, 1uL, 1Ul,",
                  "1.0, 1.0f, hello,",
                  "[true], ['1'], [uchar('1')], [short(1)], [ushort(1)],",
                  "[1], [1u], [1U], [1l], [1L], [1UL], [1ul],",
                  "[1uL], [1Ul],",
                  "[1.0], [1.0f], [hello],",
                  "1.0l, 1.0L, [1.0l], [1.0L] l=NaNL"};

    ps.input(9,argv);
    ps.output();
  }

  cout << "Testing conversions..." << endl;
  {
    vector<bool> vb;
    vector<char> vc;
    vector<unsigned char> vuc;
    vector<short> vs;
    vector<unsigned short> vus;
    vector<int> vi;
    vector<unsigned int> vui;
    vector<long> vl;
    vector<unsigned long> vul;
    vector<float> vf;
    vector<double> vd;
    vector<long double> vld;

    ParamSet ps;
    ps << ioParamVar(vb,"vb")
       << ioParamVar(vc,"vc")
       << ioParamVar(vuc,"vuc")
       << ioParamVar(vs,"vs")
       << ioParamVar(vus,"vus")
       << ioParamVar(vi,"vi")
       << ioParamVar(vui,"vui")
       << ioParamVar(vl,"vl")
       << ioParamVar(vul,"vul")
       << ioParamVar(vf,"vf")
       << ioParamVar(vd,"vd")
       << ioParamVar(vld,"vld");

    char* argv[]={"progname",
                  "vb=[1.0l] vc=[char(1.0l)] vuc=[1.0l] vs=[1.0l] vus=[1.0l]",
                  "vi=[1.0l] vui=[1.0l] vl=[1.0l] vul=[1.0l] vf=[1.0l]",
                  "vd=[1.0l]",
                  "vld=long_double('1'),uchar('1'),short(1),ushort(1),",
                      "1,1u,1l,1ul,1.0,1.0f"};

    ps.input(6,argv);
    ps.output();
  }

  } catch (Error e) {
    cout << "Unexpected error:" << endl;
    cout << e.what() << endl;
  }
  return 0;
}
