#pragma once
#include "mval.h"
#include "mlib.h"
#include <sstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;


typedef pair<string, string> Definition;
enum Kind {
  NONE, LITR, ID, CALL, LINE, DECLARE, PROC, IF, SELECT,
  FOR, WHILE, DO, EXIT, RETURN, GOSUB, GOTO, LINEINPUT, INPUT,
  LET, CASE
};


struct Ast {
  int t;
  Ast(int _t) { t = _t; }
  virtual void tos(ostream& o) {}
  string s() { stringstream o; tos(o); return o.str(); }
  friend ostream& operator<<(ostream& o, Ast& a) { a.tos(o); return o; }
  friend ostream& operator<<(ostream& o, vector<Ast*> as) {
    o<<*as.front();
    for (auto& a : as) o<<" "<<*a;
  }
};

struct Litr : Ast {
  Value x;
  Litr(Value _x) : Ast(LITR) { x = _x; }
  void tos(ostream& o) { o<<x.s(); }
};

struct Id : Ast {
  string x;
  Id(string _x) : Ast(ID) { x = _x; }
  void tos(ostream& o) { o<<x; }
};

struct Call : Ast {
  string x;
  vector<Ast*> as;
  Call(string _x, vector<Ast*> _as) : Ast(CALL) { x = _x; as = _as; }
  void tos(ostream& o) { o<<"("<<x<<" "<<as<<")"; }
};

struct Line : Ast {
  string l;
  Ast *x;
  Line(string _l, Ast* _x) : Ast(LINE) { l = _l; x = _x; }
  void tos(ostream& o) { if (l.size()) o<<l<<": "; o<<*x<<"\n"; }
};

struct Declare : Ast {
  string x;
  vector<Definition> fs;
  Declare(string _x, vector<Definition> _fs) : Ast(DECLARE) { x = _x; fs = _fs; }
  void tos(ostream& o) { o<<"(declare "<<x<<" ["<<fs<<"])"; }
};

struct Proc : Ast {
  string x;
  vector<Definition> fs;
  Ast *b;
  Proc(string _x, vector<Definition> _fs, Ast* _b) : Ast(PROC) { x = _x; fs = _fs; b = _b; }
  void tos(ostream& o) { o<<"(proc "<<x<<" ["<<fs<<"]\n"<<*b<<")"; }
};

struct If : Ast {
  Ast *c, *t, *e;
  If(Ast* _c, Ast* _t, Ast* _e) : Ast(IF) { c = _c; t = _t; e = _e; }
  void tos(ostream& o) { o<<"(if "<<*c<<" "<<*t<<" "<<*e<<")"; }
};

struct Select : Ast {
  Ast *x;
  vector<Ast*> cs;
  Select(Ast* _x, vector<Ast*> _cs) : Ast(SELECT) { x = _x; cs = _cs; }
  void tos(ostream& o) { o<<"(select\n"<<cs<<")"; }
};

struct For : Ast {
  string x, n;
  Ast *f, *t, *s, *b;
  For(string _x, Ast *_f, Ast *_t, string _n, Ast *_s, Ast *_b) : Ast(FOR)
  { x = _x; f = _f; t = _t; n = _n; s = _s; b = _b; }
  void tos(ostream& o) { o<<"(for "<<x<<" ["<<*f<<" "<<*t<<"] "<<n<<" ["<<*s<<"]\n"<<*b<<")"; }
};

struct While : Ast {
  Ast *c, *b;
  While(Ast *_c, Ast *_b) : Ast(WHILE) { c = _c; b = _b; }
  void tos(ostream& o) { o<<"(while "<<*c<<"\n"<<*b<<")"; }
};

struct Do : Ast {
  Ast *ce, *cx, *b;
  Do(Ast *_ce, Ast *_cx, Ast *_b) : Ast(DO) { ce = _ce; cx = _cx; b = _b; }
  void tos(ostream& o) { o<<"(do "<<*ce<<"\n"<<*b<<" "<<*cx<<")"; }
};

struct Exit : Ast {
  char f;
  Exit(char _f) : Ast(EXIT) { f = _f; }
  void tos(ostream& o) { o<<"(exit "<<f<<")"; }
};

struct Return : Ast {
  string l;
  Return(string _l) : Ast(RETURN) { l = _l; }
  void tos(ostream& o) { o<<"(return "<<l<<")"; }
};

struct Gosub : Ast {
  string l;
  Gosub(string _l) : Ast(GOSUB) { l = _l; }
  void tos(ostream& o) { o<<"(gosub "<<l<<")"; }
};

struct Goto : Ast {
  string l;
  Goto(string _l) : Ast(GOTO) { l = _l; }
  void tos(ostream& o) { o<<"(goto "<<l<<")"; }
};

struct LineInput : Ast {
  string p, x;
  LineInput(string _p, string _x) : Ast(LINEINPUT) { p = _p; x = _x; }
  void tos(ostream& o) { o<<"(lineinput "<<p<<" "<<x<<")"; }
};

struct Input : Ast {
  string p;
  vector<string> xs;
  Input(string _p, vector<string> _xs) : Ast(INPUT) { p = _p; xs = _xs; }
  void tos(ostream& o) { o<<"(input "<<p<<" "<<xs<<")"; }
};

struct Let : Ast {
  string x;
  Ast *e;
  Let(string _x, Ast *_e) : Ast(LET) { x = _x; e = _e; }
  void tos(ostream& o) { o<<"(let "<<x<<" "<<e<<")"; }
};

struct Case : Ast {
  Ast *f, *t;
  Case(Ast *_f, Ast *_t) : Ast(CASE) { f = _f; t = _t; }
  void tos(ostream& o) { o<<"(case "<<*f<<" "<<*t<<")"; }
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
