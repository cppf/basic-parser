#pragma once
#include <string>

using namespace std;


enum Type {BOL, INT, DEC, STR};
struct Value {
  Type t;
  union {
    bool    b;
    long    i;
    double  d;
    string *s;
  } v;

  Value() {}
  Value(bool x) { t = BOL; v.b = x; }
  Value(long x) { t = INT; v.i = x; }
  Value(double x) { t = DEC; v.d = x; }
  Value(string *x) { t = STR; v.s = x; }
  bool b() { switch(t) {
    case BOL: return v.b;
  }}
  long i() { switch(t) {
    case BOL: return v.b;
    case INT: return v.i;
  }}
  double d() { switch(t) {
    case BOL: return v.b;
    case INT: return v.i;
    case DEC: return v.d;
  }}
  string s() { switch (t) {
    case BOL: return to_string(v.b);
    case INT: return to_string(v.i);
    case DEC: return to_string(v.d);
    case STR: return *v.s;
  }}
};
