#ifndef __TEST_REG_READER_H__
#define __TEST_REG_READER_H__

#include <string>
#include <xparam.h>

class reader {
  private:
    std::string val;
    std::string desc;
  public:
    reader(char v) : desc("a char")
	{ std::cout << v << std::endl; }
    reader(unsigned char v) : desc("an unsigned char")
      { std::cout << v << std::endl; }
    reader(int v) : desc("an integer") { std::cout << v << std::endl; }
    reader(unsigned int v) : desc("an unsigned integer")
      { std::cout << v << std::endl; }
    reader(long v) : desc("a long") { std::cout << v << std::endl; }
    reader(unsigned long v) : desc("an unsigned long")
      { std::cout << v << std::endl; }
    reader(float v) : desc("a float") { std::cout << v << std::endl; }
    reader(double v) : desc("a double") { std::cout << v << std::endl; }
    reader(const std::string& v) : desc("a string") { std::cout << v << std::endl; }
    std::string describe(void) {
      return "I am a reader, created from " + desc + '.';
    }
};

#endif
