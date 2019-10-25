#pragma once
#include "mval.h"
#include "mrun.h"
#include <list>
#include <vector>
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
  Value eval() { return env[x]; }
};

struct Let : Ast {
  string x;
  Ast *e;

  Let(Ast *_x, Ast *_e) { x = _x->s(); e = _e; }
  void tos(string& s) { s+="(let "; s+=x; s+=" "; e->tos(s); s+=")"; }
  Value eval() { return env[x] = e->eval(); }
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

struct Exps : Ast {
  vector<Ast*> xs;

  Exps() { }
  Exps(vector<Ast*> _xs) { printf("hello1"); xs = _xs; }
  Ast* add(Ast *x) { printf("hello2"); xs.push_back(x); }
  void tos(string& s) { }
  Value eval() { return (long)0; }
};

struct Fn : Ast {
  string x;
  vector<Ast*> ps;

  Fn(Ast* _x, Ast* _ps) { x = _x->s(); ps = ((Exps*)_ps)->xs; }
  void tos(string& s) {
    s+="("; s+=x;
    for (auto const& p : ps) { p->tos(s); s+=", "; }
    if (ps.size()>0) s.resize(s.size()-2);
    s+=")";
  }
  Value eval() { return pmod(ps[0]->eval(), ps[1]->eval()); }
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
