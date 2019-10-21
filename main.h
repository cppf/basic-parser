#pragma once
#include <string>
#include <list>
#include <map>

using namespace std;


enum Type {
  VOID,
  BOOL,
  INTEGER,
  LONG,
  SINGLE,
  DOUBLE,
  STRING,
  // array?
  // custom?
};

struct Value {
  Type t;
  union {
    bool    b;
    int     i;
    long    l;
    float   f;
    double  d;
    string  s;
  } v;
};

enum Kind {
  VBOOL,
  VINTEGER,
  VLONG,
  VSINGLE,
  VDOUBLE,
  VSTRING,
  KBOOL,
  KINTEGER,
  KLONG,
  KSINGLE,
  KDOUBLE,
  KSTRING,
  ID,
  IF,
  LET,
  FUNCTION,
  APPLY,
};

struct Ast {
  Kind k;
  union {
    bool    b;
    int     i;
    long    l;
    float   f;
    double  d;
    string  s;
    char   *id;
    struct {
      Ast *c;
      Ast *t;
      Ast *e;
    } ifte;
    struct {
      Ast *id;
      Ast *x;
    } let;
    struct {
      Ast         *id;
      list<Ast[2]> fs;
    } function;
    struct {
      Ast      *id;
      list<Ast> ps;
    } apply;
  } v;
};





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
