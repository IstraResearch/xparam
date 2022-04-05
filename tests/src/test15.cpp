#pragma warning (disable: 4786)
#include <utility>
#include <vector>
#include <list>
#include <map>
#include <xparam.h>
#include "../include/test_reg_goose.h"
#include "../include/test_bottle.h"

using namespace xParam;
using namespace std;

int main(void)
{
  xparam_init();
 
  ParamSet ps;
  pair<goose,double> p;
  map<goose,string> str_map;
  map<goose,bottle> bot_map;
  map<goose,bottle*> bot_ptr_map;
  map<goose,const bottle*> bot_cptr_map;

  vector<goose> v;
  vector<goose*> vp;
  vector<const goose*> vcp;

  list<goose> l;
  list<goose*> lp;
  list<const goose*> lcp;
 
  try {
      ps << iParamVar(p,"p")
         << iParamVar(v,"v")
         << iParamVar(vp,"vp")
         << iParamVar(vcp,"vcp")
         << iParamVar(l,"l")
         << iParamVar(lp,"lp")
         << iParamVar(lcp,"lcp")
         << iParamVar(str_map,"str_map")
         << iParamVar(bot_map,"bot_map")
         << iParamVar(bot_ptr_map,"bot_ptr_map")
         << iParamVar(bot_cptr_map,"bot_cptr_map");

    const char* input[]={"test13","!"};
    ps.input(2,input);

  } catch (Error e) {
    cout << "Unexpected error - " << endl << e.what() << endl;
  }
  return 0;
}
