#pragma once
#include "mval.h"
#include "mast.h"
#include <map>
#include <vector>

using namespace std;


struct Breakpoint {
  int  step;
  Ast *cond;
  bool hit(int s, Environment& e);
};

struct Procedure {
  string name;
  vector<string> args;
  vector<string> exts;
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
  Procedure *proc;
  Program   *prog;
  int stepInto();
  int breakpoint();
  void eval();
};
