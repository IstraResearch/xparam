#ifndef __functions_h__
#define __functions_h__

/*	Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * As a special exception, the copyright holders give permission
 * for additional uses of the text contained in its release of XPARAM.
 *
 * The exception is that, if you link the XPARAM library with other files
 * to produce an executable, this does not by itself cause the
 * resulting executable to be covered by the GNU General Public License.
 * Your use of that executable is in no way restricted on account of
 * linking the XPARAM library code into it.
 *
 * This exception does not however invalidate any other reasons why
 * the executable file might be covered by the GNU General Public License.
 *
 * If you write modifications of your own for XPARAM, it is your choice
 * whether to permit this exception to apply to your modifications.
 * If you do not wish that, delete this exception notice.  
 */

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
