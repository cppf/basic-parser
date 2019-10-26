#pragma once
#include "mval.h"
#include "mrun.h"
#include <vector>
#include <string>
#include <sstream>

using namespace std;


struct Ast {
  virtual void ins(ostream& o) = 0;
  virtual Value eval() = 0;
  string s() {
    stringstream o;
    ins(o); return o.str();
  }
  friend ostream& operator <<(ostream& o, Ast& a) { a.ins(o); return o; }
};


struct Litr : Ast {
  Value x;
  Litr(Value _x) { x = _x; }
  void ins(ostream& o) { o<<x.s(); }
  Value eval() { return x; }
};

struct Id : Ast {
  string x;
  Id(string _x) { x = _x; }
  void ins(ostream& o) { o<<x; }
  Value eval() { return env[x]; }
};

struct Let : Ast {
  string x;
  Ast *e;
  Let(Ast *_x, Ast *_e) { x = _x->s(); e = _e; }
  void ins(ostream& o) { o<<"(let "<<x<<" "<<*e<<")"; }
  Value eval() { return env[x] = e->eval(); }
};

struct Call1 : Ast {
  Fn1 f;
  Ast *x;
  Call1(Fn1 _f, Ast *_x) { f = _f; x = _x; }
  void ins(ostream& o) { o<<"("<<pname1[f]<<" "<<*x<<")"; }
  Value eval() { return f(x->eval()); }
};

struct Call2 : Ast {
  Fn2 f;
  Ast *x, *y;
  Call2(Fn2 _f, Ast *_x, Ast *_y) { f = _f; x = _x; y = _y; }
  void ins(ostream& o) { o<<"("<<pname2[f]<<" "<<*x<<" "<<*y<<")"; }
  Value eval() { return f(x->eval(), y->eval()); }
};

// struct Line : Ast {
//   Ast *label, *stmt;
//   void tos(string& s) { label->tos(s); s+=" "; stmt->tos(s); s+="\n"; }
// };

// struct For : Ast {
//   Ast *x, *f, *t, *s, *ss;
// };

// struct While : Ast {
//   Ast *c, *ss;
//   While(Ast *_c, Ast *_ss) { c = _c; ss = _ss; }
//   void tos(string& s) { s+="(while "; c->tos(s); ss->tos(s); s+=")"; }
//   Value eval() { while (c->eval().b()) ss->eval(); return false; }
// };

// struct Do : Ast {
//   Ast *ce, *cx, *ss;
//   Do(Ast *_ce, Ast *_cx, Ast *_ss) { ce = _ce; cx = _cx; ss = _ss; }
//   void tos(string& s) { s += "(do "; if (ce) ce->tos(s); ss->tos(s); if (cx) cx->tos(s); s+=")"; }
//   Value eval() { while (ce && ce->eval().b()) { ss->eval(); if (cx && !cx->eval().b()) break; } }
// };





struct Exps : Ast {
  vector<Ast*> xs;

  Exps() { }
  Exps(vector<Ast*> _xs) { xs = _xs; }
  Ast* add(Ast *x) { xs.push_back(x); }
  void ins(ostream& o) { }
  Value eval() { return (long)0; }
};

struct Fn : Ast {
  string x;
  vector<Ast*> ps;

  Fn(Ast* _x, Ast* _ps) { printf("fn: %p %p\n", _x, _ps); x = _x->s(); ps = ((Exps*)_ps)->xs; }
  void ins(ostream& o) {
    // s+="("; s+=x;
    // for (auto const& p : ps) { p->tos(s); s+=", "; }
    // if (ps.size()>0) s.resize(s.size()-2);
    // s+=")";
  }
  Value eval() { return pmod(ps[0]->eval(), ps[1]->eval()); }
};

// struct Apply : Ast {
//   string x;
//   list<Ast*> ps;

//   Apply(string _x, list<Ast*> _ps) { x = _x; ps = _ps; }
//   string s() {
//     string a = "(";
//     a += x;
//     for (const auto& p : ps) {
//       a += " ";
//       a += p->s();
//     }
//     a += ")";
//     return a;
//   }
//   void tos(string& s) {}
//   Value eval() { return (long)0; }
// };
