#pragma once
#include <list>
#include <string>
#include <algorithm>
#include <cmath>

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
  long b() { switch(t) {
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


struct Ast {
  virtual void tos(string& s) = 0;
  virtual Value eval() = 0;
  string s() {
    string s;
    tos(s); return s;
  }
};

struct Literal : Ast {
  Value x;

  Literal(Value _x) { x = _x; }
  void tos(string& s) { s+=x.s(); }
  Value eval() { return x; }
};

struct Id : Ast {
  string x;

  Id(string _x) { x = _x; }
  void tos(string& s) { s+=x; }
  Value eval() { return (long)0; }
};

struct Pow : Ast {
  Ast *x, *y;

  Pow(Ast *_x, Ast *_y) { x = _x, y = _y; }
  void tos(string& s) { s+="(^ "; x->tos(s); s+=" "; y->tos(s); s+=")"; }
  Value eval() {
    Value a = x->eval(), b = y->eval();
    switch (max(a.t, b.t)) {
      case INT: return (long) pow(a.i(), b.i());
      case DEC: return pow(a.d(), b.d());
    }
  }
};


struct Apply : Ast {
  string x;
  list<Ast*> ps;

  Apply(string _x, list<Ast*> _ps) { x = _x; ps = _ps; }
  string s() {
    string a = "(";
    a += x;
    for (const auto& p : ps) {
      a += " ";
      a += p->s();
    }
    a += ")";
    return a;
  }
  void tos(string& s) {}
  Value eval() { return (long)0; }
};
