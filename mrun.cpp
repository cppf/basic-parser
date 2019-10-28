#include "mrun.h"


bool Breakpoint::hit(int s, Environment& e) {
  if (step >= 0 && step != s) return false;
  return cond->eval(e).b();
}

int ExecutionContext::breakpoint() {
  Environment& e = envs.back();
  for (int i=0; i<brks.size(); i++)
    if (brks[i].hit(step, e)) return i;
  return 0;
}
  // GOTO, GOSUB, RETURN, TGOTO, FGOTO,
  // PCALL, PRETURN

int ExecutionContext::stepInto() {
  int s = ++step;
  Environment& e = envs.back();
  Ast *a = prog->steps[s];
  switch (a->t) {
    // case GOTO:   step = a->l;
    // case GOTOC:  if (a->c->eval().b()) step = a->l;
    // case GOSUBC: if (a->c->eval().b()) { rets.push_back(step); step = a->l; }
    // case RETURN: step = rets.size()? rets.back() : -1; rets.pop_back();
    // case CALLP:
    //   
    // case 

  }
  return breakpoint();
}
