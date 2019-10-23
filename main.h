#pragma once
#include <map>
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

typedef Value (*Fn1)(Value);
extern map<Fn1, string> pname1;
struct Op1 : Ast {
  Fn1 f;
  Ast *x;

  Op1(Fn1 _f, Ast *_x) { f = _f; x = _x; }
  void tos(string& s) { s+="("; s+=pname1[f]; s+=" "; x->tos(s); s+=")"; }
  Value eval() { return f(x->eval()); }
};
#define FN1(n) Value n(Value)
FN1(pnot); FN1(ppos); FN1(pneg);

typedef Value (*Fn2)(Value, Value);
extern map<Fn2, string> pname2;
struct Op2 : Ast {
  Fn2 f;
  Ast *x, *y;

  Op2(Fn2 _f, Ast *_x, Ast *_y) { f = _f; x = _x; y = _y; }
  void tos(string& s) { s+="("; s+=pname2[f]; s+=" "; x->tos(s); s+=" "; y->tos(s); s+=")"; }
  Value eval() { return f(x->eval(), y->eval()); }
};
#define FN2(n) Value n(Value, Value)
FN2(pand); FN2(por); FN2(pxor); FN2(pimp); FN2(peqv);
FN2(peq); FN2(plt); FN2(pgt); FN2(ple); FN2(pge); FN2(pne);
FN2(pmod); FN2(padd); FN2(psub); FN2(pmul); FN2(pdiv); FN2(pidiv); FN2(ppow);

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
