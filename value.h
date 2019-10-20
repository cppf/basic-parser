#pragma once
#include <string>


using namespace std;

enum Type {
  VOID,
  BOOL,
  INTEGER,
  LONG,
  SINGLE,
  DOUBLE,
  STRING,
  // array?
  // custom?
};

struct Value {
  Type t;
  union {
    bool    b;
    int     i;
    long    l;
    float   f;
    double  d;
    string  s;
  } v;
};
