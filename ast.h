#pragma once
#include <string>
#include <list>
#include <map>

using namespace std;


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
