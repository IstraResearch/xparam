#pragma warning (disable: 4786)

#include <iostream>
#include <vector>
#include <string>
#include <xparam.h>
#include "../include/test_reg_everything.h"

using namespace xParam;
using namespace std;

int main(void)
{
  try {

  xparam_init();

  cout << "Testing constructors..." << endl;
  {
    vector<everything> v;
    float f;
    double d;
    ParamSet ps;
    ps << ioParamVar(v,"v")
       << ioParamVar(f,"f")
       << ioParamVar(d,"d");
    const char* argv[]=
                 {"progname","v=true, '1', uchar('1'), short(1), ushort(1),",
                  "1, 1u, 1U, 1l, 1L, 1UL, 1ul, 1uL, 1Ul,",
                  "1.0, 1.0f, hello,",
                  "[true], ['1'], [uchar('1')], [short(1)], [ushort(1)],",
                  "[1], [1u], [1U], [1l], [1L], [1UL], [1ul],",
                  "[1uL], [1Ul],",
                  "[1.0], [1.0f], [hello] f=NaNF d=NaN"};

    ps.input(8,argv);
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
    vector<string> vst;

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
       << ioParamVar(vst,"vst");

    char* argv[]={"progname",
                  "vb=true, 1, 1u, short(1), ushort(1), 1L, 1UL, 1.0, 1.0f",
                  "vc=char(true), '1',uchar('1'), char(short(1)),",
                     "char(ushort(1)),char(1),char(1u),char(1l),char(1ul),",
                     "char(1.0), char(1.0f)",
                  
                  "vuc=true,uchar('1'),short(1),ushort(1),1,1u,1l,1ul,1.0,",
                      "1.0f",

                  "vs=short('1'),uchar('1'),ushort(1),1,1u,1l,1ul,1.0,1.0f",
                  "vus=ushort('1'),uchar('1'),short(1),1,1u,1l,1ul,1.0,1.0f",
                  "vi=1,int('1'),uchar('1'),true,short(1),ushort(1),1u,1l,",
                     "1ul,1.0,1.0f",

                  "vui=1u,uint('1'),uchar('1'),short(1),ushort(1),1,1l,1ul,",
                      "1.0,1.0f",

                  "vl=1l,long('1'),uchar('1'),short(1),ushort(1),1,1u,1ul,",
                     "1.0,1.0f",

                  "vul=1ul,uchar('1'),ulong('1'),ushort(1),short(1),1,1u,",
                      "1l,1.0,1.0f",
                  "vf=float('1'),uchar('1'),short(1),ushort(1),1,1u,1l,1ul,",
                     "1.0,1.0f",

                  "vd=1.0,double('1'),uchar('1'),short(1),ushort(1),1,1u,",
                     "1l,1ul,1.0f",

                  "vst=[ hello ]"};

    ps.input(22,argv);
    ps.output();
  }

  } catch (Error e) {
    cout << "Unexpected error:" << endl;
    cout << e.what() << endl;
  }
  return 0;
}
