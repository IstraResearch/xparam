#ifndef __test_reg_duck_h__
#define __test_reg_duck_h__

#pragma warning (disable: 4786)

#include <string>
#include <iostream>
#include <fstream>
#include <xparam_extend.h>
#include "test_reg_coordinate.h"
#include "test_reg_marker.h"

class archduck {
  private:
	virtual std::string identity() const=0;
	std::string ancestors;
  public:
	std::string heritage() const { return identity()+" born of "+ancestors; }
    std::string whoami() const { return "I am "+heritage()+"."; }
    archduck(void) : ancestors("the void") {}
    archduck(const archduck& d) : ancestors(d.heritage()) {}
    archduck(const int i) : ancestors("an integer") {}
    archduck(const std::string& i) : ancestors("the string \""+i+"\"") {}
};

class duck : public archduck {
  private:
    virtual std::string identity() const {return "a duck";}
  public:
    duck(void) {}
    template<class T> duck(const T& t) : archduck(t) {}
    operator unsigned int() { return 7; }
    operator long() { return 8; }
};

class duckling : public duck {
  private:
    virtual std::string identity() const {return "a duckling";}
  public:
    duckling(void) {}
    template<class T> duckling(const T& t) : duck(t) {}
    duckling(int, int) : duck("two integers") {}
    duckling(double a, double) : duck("two doubles") {}
    duckling(const marker* my_const_marker, const marker* your_const_marker,
             marker* my_marker, marker* your_marker) {
      delete your_const_marker;
      delete your_marker;
    }
    duckling(const static_marker* my_const_marker,
             const static_marker* your_const_marker,
             static_marker* my_marker, static_marker* your_marker) {
      delete your_const_marker;
      delete your_marker;
    }
};

class ducky : public duckling {
  private:
    virtual std::string identity() const {return "a ducky";}
  public:
    explicit ducky(const int& t) : duckling(t) {}
    ducky(const std::string& t) : duckling(t) {}
    ducky(const archduck& t) : duckling(t) {}
};

class duckling_output_functor {
  public:
    static xParam::ValueList sub_objects(const duckling& d) {
      xParam::ValueList vl;
      return vl << xParam::Val(d.whoami()) << xParam::Val(coordinate(3,5));
    }
};

class ducky_output_functor {
  public:
    static xParam::ValueList sub_objects(const ducky& d) {
    xParam::ValueList vl;
    return vl << xParam::Val(d.whoami());
  }
};

class ducky_creator {
  public:
    static ducky* create(void) {
      return new ducky("the void by a creator");
    }
};

class ducky_explicit_creator {
  public:
    static ducky* create(double d) {
      return new ducky("a double by a creator");
    }
};
#endif
