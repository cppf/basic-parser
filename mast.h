#pragma once
#include "mval.h"
#include "mlib.h"
#include <vector>
#include <string>
#include <sstream>

using namespace std;


struct Ast {
  int t;
  Ast(int t);
  Ast();
};

struct Call : Ast {
  Call(char *x, vector<Ast*> as);
};
// struct Ast {
//   int t;
//   virtual void tos(ostream& o) {}
//   virtual void toe(vector<Ast*> o) { o<<*this; }
//   virtual Value eval(Environment& e) { throw false; }
//   string s() {
//     stringstream o;
//     tos(o); return o.str();
//   }
//   vector<Ast*> steps() {
//     vector<Ast*> o;
//     toe(o); return o;
//   }
//   friend vector<Ast*>& operator <<(vector<Ast*>& o, Ast& a) { a.toe(o); return o; }
//   friend ostream& operator <<(ostream& o, Ast& a) { a.tos(o); return o; }
// };

// struct Asts : Ast {
//   vector<Ast*> xs;
//   Asts() {}
//   Asts(vector<Ast*> _xs) { xs = _xs; }
//   void tos(ostream& o) { string s; for (const auto& x : xs) { o<<s<<*x; s = " "; } }
//   Value eval(Env& m) { return false; }
//   Ast* add(Ast *x) { xs.push_back(x); return this; }
// };

// struct Declare : Ast {
//   string n;
//   Ast *fs;
// };


// struct Litr : Ast {
//   Value x;
//   Litr(Value _x) { x = _x; }
//   void tos(ostream& o) { o<<x.s(); }
//   Value eval(Env& m) { return x; }
// };

// struct Id : Ast {
//   string x;
//   Id(string _x) { x = _x; }
//   void tos(ostream& o) { o<<x; }
//   Value eval(Env& m) { return m[x]; }
// };

// struct Let : Ast {
//   string x;
//   Ast *e;
//   Let(Ast *_x, Ast *_e) { x = _x->s(); e = _e; }
//   void tos(ostream& o) { o<<"(let "<<x<<" "<<*e<<")"; }
//   Value eval(Env& m) { return m[x] = e->eval(m); }
// };

// struct Call0 : Ast {

// };

// struct Call1 : Ast {
//   Proc1 f;
//   Ast *x;
//   Call1(Proc1 _f, Ast *_x) { f = _f; x = _x; }
//   // void tos(ostream& o) { o<<"("<<pname1[f]<<" "<<*x<<")"; }
//   Value eval(Env& m) { return f(x->eval(m)); }
// };

// struct Call2 : Ast {
//   Proc2 f;
//   Ast *x, *y;
//   Call2(Proc2 _f, Ast *_x, Ast *_y) { f = _f; x = _x; y = _y; }
//   // void tos(ostream& o) { o<<"("<<pname2[f]<<" "<<*x<<" "<<*y<<")"; }
//   Value eval(Env& m) { return f(x->eval(m), y->eval(m)); }
// };

// struct Call : Ast {
//   string x;
//   Ast *ps;
//   Call(Ast *_x, Ast *_ps) { x = _x->s(); ps = _ps; }
//   void tos(ostream& o) { o<<"("<<x<<" "<<*ps<<")"; }
//   Value eval(Env& m) {
//     vector<Ast*> pp = ((Asts*)ps)->xs;
//     return p1map[x](pp[0]->eval(m));
//   }
// };

// struct IfGoto : Ast {
//   Ast *c;
//   string l;
//   IfGoto(Ast *_c, string _l) { c = _c; l = _l; }
//   void tos(ostream& o) { o<<"(ifgoto "<<*c<<" "<<l<<")"; }
//   Value eval(Env& m) { if (c->eval(m).b()) m["#l"] = &l; return false; }
// };

// struct Goto : Ast {
//   string l;
//   Goto(string _l) { l = _l; }
//   void tos(ostream& o) { o<<"(goto "<<l<<")"; }
//   Value eval(Env& m) { m["#l"] = &l; return false; }
// };

// struct Gosub : Ast {
//   string l;
//   Gosub(string _l) { l = _l; }
//   void tos(ostream& o) { o<<"(gosub "<<l<<")"; }
//   Value eval(Env& m) { m["#r"] = m["#l"]; m["#l"] = &l; return false; }
// };

// struct Return : Ast {
//   Return() {}
//   void tos(ostream& o) { o<<"(return)"; }
//   Value eval(Env& m) { m["#l"] = m["#r"]; return false; }
// };

// // struct Line : Ast {
// //   Ast *label, *stmt;
// //   void tos(string& s) { label->tos(s); s+=" "; stmt->tos(s); s+="\n"; }
// // };

// struct If : Ast {
//   Ast *c, *t, *e;
//   If(Ast *_c, Ast *_t, Ast *_e) { c = _c; t = _t; e = _e; }
//   void tos(ostream& o) { o<<"(if "<<*c<<"\n"<<*t<<"\n"<<*e<<")"; }
// };

// struct Case : Ast {
//   Ast *x, *b;
//   Case(Ast *_x, Ast *_b) { x = _x; b = _b; }
//   void tos(ostream& o) { o<<"(case "<<*x<<"\n"<<*b<<")"; }
// };

// struct Select : Ast {
//   Ast *x, *cs;
//   Select(Ast *_x, Ast *_cs) { x = _x; cs = _cs; }
//   void tos(ostream& o) { o<<"(select "<<*x<<"\n"<<*cs<<")"; }
// };

// struct For : Ast {
//   Ast *x, *f, *t, *s, *b;
//   For(Ast *_x, Ast *_f, Ast *_t, Ast *_s, Ast *_b) { x = _x; f = _f; t = _t; s = _s; b = _b; }
//   void tos(ostream& o) { o<<"(for "<<*x<<" ["<<*f<<" "<<*t<<" "<<*s<<"]\n"<<*b<<")"; }
// };

// struct While : Ast {
//   Ast *c, *b;
//   While(Ast *_c, Ast *_b) { c = _c; b = _b; }
//   void tos(ostream& o) { o<<"(while "<<*c<<"\n"<<*b<<")"; }
// };

// struct Do : Ast {
//   Ast *ce, *cx, *b;
//   Do(Ast *_ce, Ast *_cx, Ast *_b) { ce = _ce; cx = _cx; b = _b; }
//   void tos(ostream& o) { o<<"(do "<<*ce<<"\n"<<*b<<*cx<<")"; }
//   vector<Ast*> code() { return {
//     new Ngoto(ce, l+1), 
//   };}
// };

// struct Block : Ast {
//   vector<Ast*> lines;
//   Block() {}
//   void tos(ostream& o) { for (const auto& l : lines) o<<*l<<"\n"; }
//   Value eval(Env& m) {
//     at = 0;
//     while (at >= 0)
//       lines[at]->eval(m);
//     return false;
//   }
// };
