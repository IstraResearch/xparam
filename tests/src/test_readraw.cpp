#pragma warning (disable: 4786)

#include <vector>
#include <iostream>
#include <xparam.h>
#include "../include/test_rawprinter.h"

using namespace xParam;
using namespace std;

int main(void)
{
  try {
    xparam_init();
    ParamSet ps;
    bool orig_b;
    rawprinter r;
    RawBytes rb;
    vector<unsigned char> rbdata;
    ps << ioParamVar(r,"r")
       << iParamVar(rb,"rb")
       << oParamVar(orig_b,"b")
       << oParamVar(rbdata,"rbdata");
    ps.input(cin);
    orig_b=r.b;
    r.b=1;
    rbdata.resize(rb.size());
    for(int i=0;i<rb.size();++i) {
      rbdata[i]=rb[i];
    }
    ps.output();
  }
  catch (Error e) {
    cout << "Unexpected error - " << endl << e.what() << endl;
  }
  return 0;
}

