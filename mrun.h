#pragma once
#include "mval.h"
#include "mast.h"
#include <map>
#include <vector>


typedef map<string, Value> Environment;

struct Breakpoint {
  int  step;
  Ast *cond;
};

struct Procedure {
  map<string, Type> args;
  vector<string>    exts;
  int step;
};

struct Program {
  map<int, int>    lines;
  map<string, int> labls;
  map<string, Procedure> procs;
  vector<Ast*> steps;
};

struct ExecutionContext {
  int step;
  vector<int> rets;
  vector<Environment> envs;
  vector<Breakpoint>  brks;
  Program *prog;
};
