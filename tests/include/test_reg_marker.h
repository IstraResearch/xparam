#ifndef __test_reg_marker_h__
#define __test_reg_marker_h__

#pragma warning (disable: 4786)

#include <iostream>
#include <fstream>

class unregistered_type {
  public:
    operator int() {return 1;}
};

class marker {
  private:
    int id;
//    marker(const marker&) {}
// xParam can not handle if marker is non copyable.
  public:
// marker has no default constructor.
	  marker(int _id) : id(_id) {std::cout << "marker " << id << " is born." << std::endl;}
	  ~marker() { std::cout << "marker " << id << " has expired." << std::endl; }
};

class static_marker {
  private:
    static int id;
    int my_id;
//    static_marker(const static_marker&) {}
// xParam can not handle if static_marker is non copyable.
  public:
    static_marker() : my_id(id+1)
	{++id; std::cout << "smarker " << my_id << " is born." << std::endl;}
    ~static_marker() { std::cout << "smarker " << my_id << " has expired." << std::endl; }
};

#endif
