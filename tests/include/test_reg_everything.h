#ifndef __test_reg_everything_h__
#define __test_reg_everything_h__

#pragma warning (disable: 4786)

#include <vector>
#include <string>
#include <xparam_extend.h>
#include <xparam.h>

struct everything {
  public:
    std::string msg;
    everything(bool b) : msg("From bool") {}
    everything(char c) : msg("From char") {}
    everything(unsigned char uc) : msg("From unsigned char") {}
    everything(short s) : msg("From short") {}
    everything(unsigned short us) : msg("From unsigned short") {}
    everything(int i) : msg("From int") {}
    everything(unsigned int ui) : msg("From unsigned int") {}
    everything(long l) : msg("From long") {}
    everything(unsigned long ul) : msg("From unsigned long") {}
    everything(float f) : msg("From float") {}
    everything(double d) : msg("From double") {}
    everything(const std::string& s) : msg("From string") {}

    everything(const std::vector<bool>& vb) : msg("From vector of bool") {}
    everything(const std::vector<char>& vc) : msg("From vector of char") {}
    everything(const std::vector<unsigned char>& vuc) : msg("From vector of unsigned char") {}
    everything(const std::vector<short>& vs) : msg("From vector of short") {}
    everything(const std::vector<unsigned short>& vus) : msg("From vector of unsigned short") {}
    everything(const std::vector<int>& vi) : msg("From vector of int") {}
    everything(const std::vector<unsigned int>& vui) : msg("From vector of unsigned int") {}
    everything(const std::vector<long>& vl) : msg("From vector of long") {}
    everything(const std::vector<unsigned long>& vul) : msg("From vector of unsigned long") {}
    everything(const std::vector<float>& vf) : msg("From vector of float") {}
    everything(const std::vector<double>& vd) : msg("From vector of double") {}
    everything(const std::vector<std::string>& vs) : msg("From vector of string") {}
};

class everything_output {
  public:
    static xParam::ValueList sub_objects(const everything& e) {
      xParam::ValueList vl;
      return vl << xParam::Val( e.msg );
    }
};

#endif
