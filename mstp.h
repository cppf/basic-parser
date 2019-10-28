#pragma once
#include "mval.h"
#include "mlib.h"
#include <string>
#include <sstream>


enum StepType {
  LITERAL, ID, LET, GOTO, GOSUB, RETURN, TGOTO, FGOTO,
  CALL0, CALL1, CALL2, CALL3, PCALL, PRETURN
};

struct Step {
  StepType t;
  Value  v;
  Step  *a;
  Step  *b;
  Step  *c;
  Step **as;
  int    n;
  union {
    Proc0 p0;
    Proc1 p1;
    Proc2 p2;
    Proc3 p3;
  } p;
  string s();
  void tos(ostream& o);
};
