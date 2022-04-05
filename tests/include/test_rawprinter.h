#ifndef __test_raw_printer_h__
#define __test_raw_printer_h__

#include <vector>

struct rawprinter {
    bool b;
    std::vector<unsigned char> v;
    rawprinter() {}
    rawprinter(bool _b, const std::vector<unsigned char>& _v) : b(_b) {
      for(int i=0;i<_v.size();++i) {
        v.push_back(_v[i]);
      }
    }
};

#endif
