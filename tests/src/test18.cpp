#pragma warning (disable: 4786)

// This file tests globbing using the : a b : syntax.

#include <string>
#include <vector>
#include <xparam.h>
#include <xparam_extend.h>

using namespace std;
using namespace xParam;

struct xxx {
  xxx(const vector<string>&) {}
};

PARAM_BEGIN_REG

  param_class<xxx>("abc::def<ghi::jkl>");
  param_ctor(TypeTag<xxx>(),ConstRef<vector<string> >("v1"));

PARAM_END_REG

void try_glob(int size, char** input)
{
  try {
    ParamSet ps;
    vector<string> vs;
    bool t;

    ps << ioParamVar(vs,"vs");
    ps << ioParamVar(t,"t",Val(false));
    ps.input(size,input);
    ps.output();
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }
}

int main(int argc, char* argv[])
{
  try {
    xparam_init();
  }
  catch(Error e) {
    cout << "Got following error - " << endl << e.what() << endl;
  }

  {
    char* argv[]={"progname",":","a",":"};
    try_glob(4,argv);
  }
  {
    char* argv[]={"progname","vs=:","a",":"};
    try_glob(4,argv);
  }
  {
    char* argv[]={"progname","vs= : ","a"," : "};
    try_glob(4,argv);
  }
  {
    char* argv[]={"progname",":","a","b",":"};
    try_glob(5,argv);
  }
  {
    char* argv[]={"progname","vs=:","a","b",":"};
    try_glob(5,argv);
  }
  {
    char* argv[]={"progname","vs=:","a b",":"};
    try_glob(4,argv);
  }
  {
    char* argv[]={"progname","vs=: a",":"};
    try_glob(3,argv);
  }
  {
    char* argv[]={"progname","vs=:","a :"};
    try_glob(3,argv);
  }
  {
    char* argv[]={"progname","vs=: a :"};
    try_glob(2,argv);
  }
  {
    char* argv[]={"progname","vs=:",":"};
    try_glob(3,argv);
  }
  {
    char* argv[]={"progname","vs=: :"};
    try_glob(2,argv);
  }
  {
    char* argv[]={"progname","vs=::"};
    try_glob(2,argv);
  }
  {
    char* argv[]={"progname","vs=:"};
    try_glob(2,argv);
  }
  {
    char* argv[]={"progname","vs=:","a"};
    try_glob(3,argv);
  }
  {
    char* argv[]={"progname","vs=:","a","b"};
    try_glob(4,argv);
  }
  {
    char* argv[]={"progname","vs=:","a:","b:"};
    try_glob(4,argv);
  }
  {
    char* argv[]={"progname","vs=:","a b"};
    try_glob(3,argv);
  }
  {
    char* argv[]={"progname","vs=:","c:\\home_dir\\My file\\file-name.txt"};
    try_glob(3,argv);
  }
  {
    char* argv[]={"progname","vs=:","/my dir/my file - unix_version.txt"};
    try_glob(3,argv);
  }
  {
    char* argv[]={"progname","vs=:","a","b",": -t"};
    try_glob(5,argv);
  }
  {
    char* argv[]={"progname","vs=abc","::","def<ghi","::","jkl>(:","a","b",":)"};
    try_glob(9,argv);
  }
  return 0;
}
