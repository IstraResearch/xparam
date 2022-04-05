/*	Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand */

#pragma warning (disable: 4786)

#include <math.h>
#include <xparam_extend.h>
#include "../include/functions.h"

using namespace xParam;

/*
 * The following definitions sometimes do not appear under <math.h>. *
 * For this reason, they are repeated here. The original definitions *
 * were copied from GNU-C++'s math.h.                                */

#ifndef M_LOG2E

# define M_E            2.7182818284590452354   /* e */
# define M_LOG2E        1.4426950408889634074   /* log_2 e */
# define M_LOG10E       0.43429448190325182765  /* log_10 e */
# define M_LN2          0.69314718055994530942  /* log_e 2 */
# define M_LN10         2.30258509299404568402  /* log_e 10 */
# define M_PI           3.14159265358979323846  /* pi */
# define M_PI_2         1.57079632679489661923  /* pi/2 */
# define M_PI_4         0.78539816339744830962  /* pi/4 */
# define M_1_PI         0.31830988618379067154  /* 1/pi */
# define M_2_PI         0.63661977236758134308  /* 2/pi */
# define M_2_SQRTPI     1.12837916709551257390  /* 2/sqrt(pi) */
# define M_SQRT2        1.41421356237309504880  /* sqrt(2) */
# define M_SQRT1_2      0.70710678118654752440  /* 1/sqrt(2) */

#endif // M_LOG2E

PARAM_BEGIN_REG

  PARAM_CLASS(Expression);

  PARAM_CLASS(ArithValue);
    param_inheritance(DerivedTag<ArithValue>(),BaseTag<Expression>());
    param_ctor(TypeTag<ArithValue>(),ByVal<double>("v"));

  PARAM_CLASS(add);
    param_inheritance(DerivedTag<add>(),BaseTag<ArithValue>());
    param_ctor(TypeTag<add>(),ConstRef<ArithValue>("a"),ConstRef<ArithValue>("b"));

  PARAM_CLASS(sub);
    param_inheritance(DerivedTag<sub>(),BaseTag<ArithValue>());
    param_ctor(TypeTag<sub>(),ConstRef<ArithValue>("a"),ConstRef<ArithValue>("b"));

  PARAM_CLASS(mul);
    param_inheritance(DerivedTag<mul>(),BaseTag<ArithValue>());
    param_ctor(TypeTag<mul>(),ConstRef<ArithValue>("a"),ConstRef<ArithValue>("b"));

  param_class<dv>("div");
    param_inheritance(DerivedTag<dv>(),BaseTag<ArithValue>());
    param_ctor(TypeTag<dv>(),ConstRef<ArithValue>("a"),ConstRef<ArithValue>("b"));

  PARAM_CLASS(Variable);
    param_inheritance(DerivedTag<Variable>(),BaseTag<ArithValue>());
    param_ctor(TypeTag<Variable>(),ConstRef<std::string>("name"));

  PARAM_CLASS(def);
    param_inheritance(DerivedTag<def>(),BaseTag<Expression>());
    param_ctor(TypeTag<def>(),ConstRef<std::string>("name"),
      ConstRef<ArithValue>("val"));
    param_vector<def>();

  PARAM_CLASS(MultiDef);
    param_inheritance(DerivedTag<MultiDef>(),BaseTag<Expression>());
    param_ctor(TypeTag<MultiDef>(),ConstRef<std::vector<def> >("deflist"));

  PARAM_CONST(M_E);
  PARAM_CONST(M_LOG2E);
  PARAM_CONST(M_LOG10E);
  PARAM_CONST(M_LN2);
  PARAM_CONST(M_LN10);
  PARAM_CONST(M_PI);
  PARAM_CONST(M_PI_2);
  PARAM_CONST(M_PI_4);
  PARAM_CONST(M_1_PI);
  PARAM_CONST(M_2_PI);
  PARAM_CONST(M_2_SQRTPI);
  PARAM_CONST(M_SQRT2);
  PARAM_CONST(M_SQRT1_2);

PARAM_END_REG
