#pragma warning (disable: 4786)

#include <string>
#include <vector>
#include <iostream>
#include <xparam.h>
#include <xparam_extend.h>

using namespace std;
using namespace xParam;

template<class T>
class abstract_testing {
  public:
    virtual const T& get_t(void) const=0;
};

template<class T>
class testing : public abstract_testing<T> {
  private:
    T t;
  public:
    testing(const T& _t) : t(_t) {}
    const T& get_t(void) const { return t; }
};

template<class T>
class output_testing {
  public:
    static ValueList sub_objects(const testing<T>& t) {
      ValueList vl;
      return vl << Val(t.get_t());
    }
};

class not_registered {};

template<class T>
class abstract_testingRegCommand :
  public ClassRegCommand<abstract_testing<T>,
                         AbstractClassKind<abstract_testing<T> > > {
  public:
    abstract_testingRegCommand(void) :
      ClassRegCommand<abstract_testing<T>,
                      AbstractClassKind<abstract_testing<T> > >(typeid(T)) {}
    std::string type_name(void) const {
      return "abstract_testing<"+xparam_or_cpp_name(typeid(T))+">";
    }
};

template<class T>
class testingRegCommand : public ClassRegCommand<testing<T> > {
  public:
    testingRegCommand(void) : ClassRegCommand<testing<T> >(typeid(T)) {}
    std::string type_name(void) const {
      return "testing<"+xparam_or_cpp_name(typeid(T))+">";
    }
};

template<class T>
class param_testing {
  public:
    param_testing(void) {
      param_class<testing<T> >(new testingRegCommand<T>());
      param_abstract_class<abstract_testing<T> >
        (new abstract_testingRegCommand<T>());
      param_inheritance(DerivedTag<testing<T> >(),
                        BaseTag<abstract_testing<T> >());
      param_ctor(TypeTag<testing<T> >(),ConstRef<T>("_t"));
      param_output<testing<T>,output_testing<T> >();
    }
};

PARAM_BEGIN_REG

/*
  This part was removed from the test, because it yields non-portable
  results. It should yield 5 pending registration calls:
    1) param_testing<not_registered>
    2) param_abstract_testing<not_registered>
    3) param_testing<not_registered> inheritance from param_abstract_testing
    4) param_testing<not_registered>(int) constructor
    5) param_testing<not_registered> output
    
  param_testing<not_registered>();
*/
  param_testing<int>();

PARAM_END_REG

int main(int argc, char* argv[])
{
  xparam_init();

  ParamSet ps;

  try {
	cout << "Testing template registration." << endl;
    char c;
    string s;
    vector<bool> vb;
    testing<int> ti(7);
    ps << ioParamVar(c,"c")
       << ioParamVar(s,"s")
       << ioParamVar(vb,"vb")
       << ioParamVar(ti,"ti");

    const char* input1[]={"test17","c=\'\\\'\' s=\"\\\"\" vb=[true, false]"
                                   "ti=8"};
    ps.input(2,input1);
    ps.output();
  } catch(Error e) {
	cout << "Unexpected error - " << endl << e.what() << endl;
  }
  try {
	cout << xparam_help(xparam_name(typeid(testing<int>))) << endl;
  } catch(Error e) {
	cout << "Unexpected error - " << endl << e.what() << endl;
  }
  try {
    const char* input2[]={"test17","!","PENDING"};
    ps.input(3,input2);
  } catch(Error e) {
	cout << "Unexpected error - " << endl << e.what() << endl;
  }
  return 0;
}
