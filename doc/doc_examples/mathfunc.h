#ifndef __mathfunc_h__
#define __mathfunc_h__

/*	Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand */

#include <stdexcept>
#include <math.h>
#include "functions.h"

class ln : public ArithValue {
  private:
    double calc_ln(const double& v) {
      if (v<=0.0)
        throw std::out_of_range("Can not take ln of non-positive value.");
      return log(v);
    }
  public:
    ln(const ArithValue& val) : ArithValue(calc_ln(val)) {}
};

class root : public ArithValue {
  private:
    double calc_sqrt(const double& v) {
      if (v<0.0)
        throw std::out_of_range("Can not take square root of negative value.");
      return sqrt(v);
    }
  public:
    root(const ArithValue& val) : ArithValue(calc_sqrt(val)) {}
};

#endif // __mathfunc_h__
