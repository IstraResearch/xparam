#ifndef __test_bottle_h__
#define __test_bottle_h__

#pragma warning (disable: 4786)

#include <string>

class bottle {
  private:
    std::string mesg;
  public:
    bottle(void) : mesg("No message") {}
    bottle(const std::string& message) : mesg(message) {}
    const std::string& msg(void) const {return mesg;}
};

#endif
