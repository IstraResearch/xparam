#ifndef __functions_h__
#define __functions_h__

/*	Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand */

#include <map>
#include <vector>
#include <string>

class Expression {
  protected:
    static std::map<std::string,double> variable;
    Expression(void) {}
  public:
    virtual ~Expression(void) {}
};

class ArithValue : public Expression {
  private:
    double _val;
  public:
    ArithValue(const double v) : _val(v) {}
    operator double() const { return _val; }
    virtual ~ArithValue(void) {}
};

class add : public ArithValue {
  public:
    add(const ArithValue& a, const ArithValue& b) : ArithValue(a+b) {}
};

class sub : public ArithValue {
  public:
    sub(const ArithValue& a, const ArithValue& b) : ArithValue(a-b) {}
};

class mul : public ArithValue {
  public:
    mul(const ArithValue& a, const ArithValue& b) : ArithValue(a*b) {}
};

class dv : public ArithValue {
  public:
    dv(const ArithValue& a, const ArithValue& b) : ArithValue(a/b) {}
};

class Variable : public ArithValue {
  public:
    Variable(const std::string& name) : ArithValue(variable[name]) {}
};

class def : public Expression {
  public:
    def(const std::string& name, const ArithValue& val) {
      variable[name]=val;
    }
};

class MultiDef : public Expression {
  public:
    MultiDef(const std::vector<def>& deflist) {}
};
        
#endif // __functions_h__
