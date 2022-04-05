#ifndef __test_reg_everything2_h__
#define __test_reg_everything2_h__

#pragma warning (disable: 4786)

#include <vector>
#include <string>
#include <xparam_extend.h>
#include <xparam.h>

struct everything2 {
  public:
    std::string msg;
    everything2(bool b) : msg("From bool") {}
    everything2(char c) : msg("From char") {}
    everything2(unsigned char uc) : msg("From unsigned char") {}
    everything2(short s) : msg("From short") {}
    everything2(unsigned short us) : msg("From unsigned short") {}
    everything2(int i) : msg("From int") {}
    everything2(unsigned int ui) : msg("From unsigned int") {}
    everything2(long l) : msg("From long") {}
    everything2(unsigned long ul) : msg("From unsigned long") {}
    everything2(float f) : msg("From float") {}
    everything2(double d) : msg("From double") {}
    everything2(long double ld) : msg("From long double") {}
    everything2(const std::string& s) : msg("From string") {}

    everything2(const std::vector<bool>& vb) : msg("From vector of bool") {}
    everything2(const std::vector<char>& vc) : msg("From vector of char") {}
    everything2(const std::vector<unsigned char>& vuc) : msg("From vector of unsigned char") {}
    everything2(const std::vector<short>& vs) : msg("From vector of short") {}
    everything2(const std::vector<unsigned short>& vus) : msg("From vector of unsigned short") {}
    everything2(const std::vector<int>& vi) : msg("From vector of int") {}
    everything2(const std::vector<unsigned int>& vui) : msg("From vector of unsigned int") {}
    everything2(const std::vector<long>& vl) : msg("From vector of long") {}
    everything2(const std::vector<unsigned long>& vul) : msg("From vector of unsigned long") {}
    everything2(const std::vector<float>& vf) : msg("From vector of float") {}
    everything2(const std::vector<double>& vd) : msg("From vector of double") {}
    everything2(const std::vector<long double>& vld) : msg("From vector of long double") {}
    everything2(const std::vector<std::string>& vs) : msg("From vector of string") {}
};

class everything2_output {
  public:
    static xParam::ValueList sub_objects(const everything2& e) {
      xParam::ValueList vl;
      return vl << xParam::Val( e.msg );
    }
};

#endif

