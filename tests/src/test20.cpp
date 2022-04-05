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
    vector<unsigned char> v(6);
    for(int i=0;i<v.size();++i) v[i]=2*i;
    rawprinter r(0,v);
    RawBytes rb(3,'t');
    ps << oParamVar(r,"r")
       << oParamVar(rb,"rb");
    ps.output();
  }
  catch (Error e) {
    cout << "Unexpected error - " << endl << e.what() << endl;
  }
  return 0;
}

