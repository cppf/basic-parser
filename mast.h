#pragma once
#include "mval.h"
#include "mrun.h"
#include <vector>
#include <string>
#include <sstream>

using namespace std;


struct Ast {
  virtual void ins(ostream& o) = 0;
  virtual Value eval(Env& m) = 0;
  string s() {
    stringstream o;
    ins(o); return o.str();
  }
  friend ostream& operator <<(ostream& o, Ast& a) { a.ins(o); return o; }
};

struct Asts : Ast {
  vector<Ast*> xs;
  Asts() {}
  Asts(vector<Ast*> _xs) { xs = _xs; }
  void ins(ostream& o) { string s; for (const auto& x : xs) { o<<s<<*x; s = " "; } }
  Value eval(Env& m) { return false; }
  Ast* add(Ast *x) { xs.push_back(x); return this; }
};

struct Declare : Ast {
  string n;
  Ast *fs;
};


struct Litr : Ast {
  Value x;
  Litr(Value _x) { x = _x; }
  void ins(ostream& o) { o<<x.s(); }
  Value eval(Env& m) { return x; }
};

struct Id : Ast {
  string x;
  Id(string _x) { x = _x; }
  void ins(ostream& o) { o<<x; }
  Value eval(Env& m) { return m[x]; }
};

struct Let : Ast {
  string x;
  Ast *e;
  Let(Ast *_x, Ast *_e) { x = _x->s(); e = _e; }
  void ins(ostream& o) { o<<"(let "<<x<<" "<<*e<<")"; }
  Value eval(Env& m) { return m[x] = e->eval(m); }
};

struct Call1 : Ast {
  Fn1 f;
  Ast *x;
  Call1(Fn1 _f, Ast *_x) { f = _f; x = _x; }
  void ins(ostream& o) { o<<"("<<pname1[f]<<" "<<*x<<")"; }
  Value eval(Env& m) { return f(x->eval(m)); }
};

struct Call2 : Ast {
  Fn2 f;
  Ast *x, *y;
  Call2(Fn2 _f, Ast *_x, Ast *_y) { f = _f; x = _x; y = _y; }
  void ins(ostream& o) { o<<"("<<pname2[f]<<" "<<*x<<" "<<*y<<")"; }
  Value eval(Env& m) { return f(x->eval(m), y->eval(m)); }
};

struct Call : Ast {
  string x;
  Ast *ps;
  Call(Ast *_x, Ast *_ps) { x = _x->s(); ps = _ps; }
  void ins(ostream& o) { o<<"("<<x<<" "<<*ps<<")"; }
  Value eval(Env& m) {
    vector<Ast*> pp = ((Asts*)ps)->xs;
    return f1map[x](pp[0]->eval(m));
  }
};

struct IfGoto : Ast {
  Ast *c;
  string l;
  IfGoto(Ast *_c, string _l) { c = _c; l = _l; }
  void ins(ostream& o) { o<<"(ifgoto "<<*c<<" "<<l<<")"; }
  Value eval(Env& m) { if (c->eval(m).b()) m["#l"] = &l; return false; }
};

struct Goto : Ast {
  string l;
  Goto(string _l) { l = _l; }
  void ins(ostream& o) { o<<"(goto "<<l<<")"; }
  Value eval(Env& m) { m["#l"] = &l; return false; }
};

struct Gosub : Ast {
  string l;
  Gosub(string _l) { l = _l; }
  void ins(ostream& o) { o<<"(gosub "<<l<<")"; }
  Value eval(Env& m) { m["#r"] = m["#l"]; m["#l"] = &l; return false; }
};

struct Return : Ast {
  Return() {}
  void ins(ostream& o) { o<<"(return)"; }
  Value eval(Env& m) { m["#l"] = m["#r"]; return false; }
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
