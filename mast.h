#pragma once
#include "mval.h"
#include "mrun.h"
#include <list>
#include <string>

using namespace std;


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

struct Op1 : Ast {
  Fn1 f;
  Ast *x;

  Op1(Fn1 _f, Ast *_x) { f = _f; x = _x; }
  void tos(string& s) { s+="("; s+=pname1[f]; s+=" "; x->tos(s); s+=")"; }
  Value eval() { return f(x->eval()); }
};

struct Op2 : Ast {
  Fn2 f;
  Ast *x, *y;

  Op2(Fn2 _f, Ast *_x, Ast *_y) { f = _f; x = _x; y = _y; }
  void tos(string& s) { s+="("; s+=pname2[f]; s+=" "; x->tos(s); s+=" "; y->tos(s); s+=")"; }
  Value eval() { return f(x->eval(), y->eval()); }
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
