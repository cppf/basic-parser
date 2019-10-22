#pragma once
#include <string>
#include <list>

using namespace std;


enum Type {
  VOID,
  BOOL,
  INTEGER,
  LONG,
  SINGLE,
  DOUBLE,
  STRING
};

struct Value {
  Type t;
  union {
    bool    b;
    int     i;
    long    l;
    float   f;
    double  d;
    string *s;
  } v;

  string str() { switch (t) {
    case VOID:    return string("void");
    case BOOL:    return string(v.b? "true" : "false");
    case INTEGER: return to_string(v.i);
    case LONG:    return to_string(v.l);
    case SINGLE:  return to_string(v.f);
    case DOUBLE:  return to_string(v.d);
    case STRING:  return *v.s;
  }}
};


struct Ast {
  virtual string str() = 0;
  virtual Value eval() = 0;
};

struct Literal : Ast {
  Value v;

  Literal(Value _v) { v = _v; }
  string str() { return v.str(); } 
  Value eval() { return v; }
};


struct Apply : Ast {
  string x;
  list<Ast*> ps;

  Apply(string _x, list<Ast*> _ps) { x = _x; ps = _ps; }
  string str() {
    string a = "(";
    a += x;
    for (const auto& p : ps) {
      a += " ";
      a += p->str();
    }
    a += ")";
    return a;
  }
  Value eval() { return {VOID}; }
};


struct Neg : Ast {
  Ast *x;

  Neg(Ast *_x) { x = _x; }
  Value eval() {
    Value p = x->eval();
    switch (p.t) {
      case INTEGER: return {INTEGER, {i: -p.v.i}};
      case LONG: return {LONG, {l: -p.v.l}};
      case SINGLE: return {SINGLE, {f: -p.v.f}};
      case DOUBLE: return {DOUBLE, {d: -p.v.d}};
      default: throw 0;
    }
  }
};

/*
// pop: remove n chars from end of string
char *pop(char *s, int n) {
  s[strlen(s) - n] = '\0';
  return s;
}

// lower: lowercase characters in place
char *lower(char *s) {
  for(char *d=s; *d; d++) { *d = tolower(*d); }
  return s;
}


char *unescape(char *s) {
  char *_s = s;
  for(char *d=s; *s; s++) {
    if (*s == '\\') {switch(s[1]) {
      case 'a': *d = '\a'; s++;
      case 'b': *d = '\b'; s++;
      case 'e': *d = '\e'; s++;
      case 'f': *d = '\f'; s++;
      case 'n': *d = '\n'; s++;
      case 'r': *d = '\r'; s++;
      case 't': *d = '\t'; s++;
      case 'v': *d = '\v'; s++;
      case '\\': *d = '\\'; s++;
      case '\'': *d = '\''; s++;
      case '\"': *d = '\"'; s++;
      case '?': *d = '\?'; s++;
      default: *d = *s; d++;
    }}
  }
  return _s;
}
*/
