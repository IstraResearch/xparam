#pragma warning (disable: 4786)

#include <iostream>
#include <xparam_extend.h>
#include <xparam.h>
#include <stdio.h>

using namespace xParam;
using namespace std;

struct everything {
  public:
    string msg;
    everything(bool b) : msg("From bool") {}
    everything(char c) : msg("From char") {}
    everything(unsigned char uc) : msg("From unsigned char") {}
    everything(short s) : msg("From short") {}
    everything(unsigned short us) : msg("From unsigned short") {}
    everything(int i) : msg("From int") {}
    everything(unsigned int ui) : msg("From unsigned int") {}
    everything(long l) : msg("From long") {}
    everything(unsigned long ul) : msg("From unsigned long") {}
    everything(long long ll) : msg("From long long") {}
    everything(unsigned long long ull) : msg("From unsigned long long") {}
    everything(float f) : msg("From float") {}
    everything(double d) : msg("From double") {}
    everything(const string& s) : msg("From string") {}

    everything(const vector<bool>& vb) : msg("From vector of bool") {}
    everything(const vector<char>& vc) : msg("From vector of char") {}
    everything(const vector<unsigned char>& vuc) : msg("From vector of unsigned char") {}
    everything(const vector<short>& vs) : msg("From vector of short") {}
    everything(const vector<unsigned short>& vus) : msg("From vector of unsigned short") {}
    everything(const vector<int>& vi) : msg("From vector of int") {}
    everything(const vector<unsigned int>& vui) : msg("From vector of unsigned int") {}
    everything(const vector<long>& vl) : msg("From vector of long") {}
    everything(const vector<unsigned long>& vul) : msg("From vector of unsigned long") {}
    everything(const vector<long long>& vll) : msg("From vector of long long") {}
    everything(const vector<unsigned long long>& vul) : msg("From vector of unsigned long long") {}
    everything(const vector<float>& vf) : msg("From vector of float") {}
    everything(const vector<double>& vd) : msg("From vector of double") {}
    everything(const vector<string>& vs) : msg("From vector of string") {}
};

class everything_output {
  public:
    static ValueList sub_objects(const everything& e) {
      ValueList vl;
      return vl << Val( e.msg );
    }
};


PARAM_BEGIN_REG

PARAM_CLASS(everything);
param_ctor(TypeTag<everything>(),ByVal<bool>("b"));
param_ctor(TypeTag<everything>(),ByVal<char>("c"));
param_ctor(TypeTag<everything>(),ByVal<unsigned char>("uc"));
param_ctor(TypeTag<everything>(),ByVal<short>("s"));
param_ctor(TypeTag<everything>(),ByVal<unsigned short>("us"));
param_ctor(TypeTag<everything>(),ByVal<int>("i"));
param_ctor(TypeTag<everything>(),ByVal<unsigned int>("ui"));
param_ctor(TypeTag<everything>(),ByVal<long>("l"));
param_ctor(TypeTag<everything>(),ByVal<unsigned long>("ul"));
param_ctor(TypeTag<everything>(),ByVal<long long>("ll"));
param_ctor(TypeTag<everything>(),ByVal<unsigned long long>("ull"));
param_ctor(TypeTag<everything>(),ByVal<float>("f"));
param_ctor(TypeTag<everything>(),ByVal<double>("d"));
param_ctor(TypeTag<everything>(),ConstRef<string>("s"));

param_ctor(TypeTag<everything>(),ConstRef<vector<bool> >("vb"));
param_ctor(TypeTag<everything>(),ConstRef<vector<char> >("vc"));
param_ctor(TypeTag<everything>(),ConstRef<vector<unsigned char> >("vuc"));
param_ctor(TypeTag<everything>(),ConstRef<vector<short> >("vs"));
param_ctor(TypeTag<everything>(),ConstRef<vector<unsigned short> >("vus"));
param_ctor(TypeTag<everything>(),ConstRef<vector<int> >("vi"));
param_ctor(TypeTag<everything>(),ConstRef<vector<unsigned int> >("vui"));
param_ctor(TypeTag<everything>(),ConstRef<vector<long> >("vl"));
param_ctor(TypeTag<everything>(),ConstRef<vector<unsigned long> >("vul"));
param_ctor(TypeTag<everything>(),ConstRef<vector<long long> >("vll"));
param_ctor(TypeTag<everything>(),ConstRef<vector<unsigned long long> >("vull"));
param_ctor(TypeTag<everything>(),ConstRef<vector<float> >("vf"));
param_ctor(TypeTag<everything>(),ConstRef<vector<double> >("vd"));
param_ctor(TypeTag<everything>(),ConstRef<vector<string> >("vs"));

param_output<everything,everything_output>();
param_vector<everything>();

PARAM_END_REG

int main(void)
{
  try {
    xparam_init();

  cout << "Testing constructors..." << endl;
  {
    vector<everything> v;
    ParamSet ps;
    ps << ioParamVar(v,"v");
    const char* argv[]=
                 {"progname","v=true, '1', uchar('1'), short(1), ushort(1),",
                  "1, 1u, 1U, 1l, 1L, 1UL, 1ul, 1uL, 1Ul,",
                  "1.0, 1.0f, hello, longlong(1), ulonglong(1),",
                  "[true], ['1'], [uchar('1')], [short(1)], [ushort(1)],",
                  "[1], [1u], [1U], [1l], [1L], [1UL], [1ul],",
                  "[1uL], [1Ul],[longlong(1)], [ulonglong(1)],",
                  "[1.0], [1.0f], [hello]"};

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
    vector<long long> vll;
    vector<unsigned long long> vull;
    vector<float> vf;
    vector<double> vd;

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
       << ioParamVar(vll,"vll")
       << ioParamVar(vull,"vull")
       << ioParamVar(vf,"vf")
       << ioParamVar(vd,"vd");

    const char* argv[]={"progname",
                  "vb=longlong(1), ulonglong(1)",
                  "vc=longlong(1), ulonglong(1)",
                  "vuc=longlong(1), ulonglong(1)",
                  "vs=longlong(1), ulonglong(1)",
                  "vus=longlong(1), ulonglong(1)",
                  "vi=longlong(1), ulonglong(1)",
                  "vui=longlong(1), ulonglong(1)",
                  "vl=longlong(1), ulonglong(1)",
                  "vf=longlong(1), ulonglong(1)",
                  "vd=longlong(1), ulonglong(1)",
                  "vul=longlong(1), ulonglong(1)",
                  "vll=longlong('1'),uchar('1'),short(1),ushort(1),1,1u,",
                      "1l,1ul,1.0,1.0f,ulonglong(1)",
                  "vull=ulonglong('1'),uchar('1'),short(1),ushort(1),1,1u,",
                      "1l,1ul,1.0,1.0f,longlong(1)"};

    ps.input(16,argv);
    ps.output();
  }

  } catch (Error e) {
    cout << "Unexpected error:" << endl;
    cout << e.what() << endl;
  }
  return 0;
}
