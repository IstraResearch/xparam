#ifndef __test_reg_goose_h__
#define __test_reg_goose_h__

#pragma warning (disable: 4786)

class gooseberry {
  private:
    int n;
  public:
    gooseberry(void) {}
    gooseberry(int i) : n(i) {}
    int num(void) const { return n; }
};

class goose {
  private:
    int n;
  public:
    goose(void) {}
    goose(int i) : n(i) {}
    goose(const gooseberry& d) : n(d.num()*2) {}
    int num(void) const { return n; }
};

inline bool operator<(const goose& a, const goose& b) {
  return a.num()<b.num();
}

#endif
