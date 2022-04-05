#pragma warning (disable: 4786)

#include <xparam.h>
#include "../include/test_reg_duck.h"

using namespace xParam;
using namespace std;

int main(void) {
  try {

  xparam_init();

  cout << "xparam name: " << xparam_name(typeid(duck)) << endl;
  cout << "xparam help:" << endl;
  cout << xparam_help(xparam_name(typeid(duck))) << endl;

  } catch(Error e) {
    cout << "Unexpected error:" << endl;
    cout << e.what() << endl;
  }
  return 0;
}
