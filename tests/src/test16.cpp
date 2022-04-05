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
      ps << ioParamVar(p,"p")
         << ioParamVar(v,"v")
         << ioParamVar(vp,"vp")
         << ioParamVar(vcp,"vcp")
         << ioParamVar(l,"l")
         << ioParamVar(lp,"lp")
         << ioParamVar(lcp,"lcp")
         << ioParamVar(str_map,"str_map")
         << ioParamVar(bot_map,"bot_map")
         << ioParamVar(bot_ptr_map,"bot_ptr_map")
         << ioParamVar(bot_cptr_map,"bot_cptr_map");

    const char* input[]={"test13","p=pair<goose,double>(groucho,3.1) "
                                  "v=[0, 3, 4] "
                                  "vp=[1, groucho] "
                                  "vcp=[0, 5] "
                                  "l=1, 2, 3 "
                                  "lp=0, 4 ,5 "
                                  "lcp=[11] "
                                  "str_map={ groucho => one, 5 => two} "
                                  "bot_map={ 0 => three } "
                                  "bot_ptr_map= { 4 => 4, 5 => 5 } "
                                  "bot_cptr_map = {6=>6, 7=>7}"
    };
    ps.input(2,input);
    ps.output();

    const char* input2[]={"test13","p=pair<goose,double>(groucho,3.1) "
                                  "v=vector<goose>(3,3) "
                                  "vp=vector<goose*>(1,1) "
                                  "vcp=vector<const goose*>(0,0) "
                                  "l=list<goose>(0,0) "
                                  "lp=list<goose*>(3,NULL) "
                                  "lcp=list<const goose*>(4,1) "
               "str_map=map<goose,string>({ groucho => one, 5 => two}) "
               "bot_map={} "
               "bot_ptr_map= { 4 => NULL, 5 => NULL } "
               "bot_cptr_map = {6=>6, 7=>7}"
    };
    ps.input(2,input2);
    ps.output();

  } catch (Error e) {
    cout << "Unexpected error - " << endl << e.what() << endl;
  }
  return 0;
}
