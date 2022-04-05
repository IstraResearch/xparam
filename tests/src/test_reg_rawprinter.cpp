#pragma warning (disable: 4786)

#include <vector>
#include <xparam_extend.h>
#include "../include/test_rawprinter.h"

using namespace std;
using namespace xParam;

class rawprinter_output_functor {
  public:
    static ValueList sub_objects(const rawprinter& r) {
      ValueList vl;
      if (r.b) {
        vl << Val(r.b) << Val(r.v);
      } else {
        RawBytes rb;
        for(int i=0;i<r.v.size();++i) {
          rb.push_back(r.v[i]);
        }
        vl << Val(r.b) << Val(rb);
      }
      return vl;
    }
};

PARAM_BEGIN_REG
  PARAM_CLASS(rawprinter);
  param_ctor(TypeTag<rawprinter>(),ByVal<bool>("b"),ConstRef<vector<unsigned char> >("v"));
  param_ctor(TypeTag<rawprinter>());
  param_output<rawprinter,rawprinter_output_functor>();
PARAM_END_REG

  
