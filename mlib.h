#pragma once
#include "mval.h"
#include <map>
#include <vector>

using namespace std;


typedef map<string, Value> Env;
typedef Value (*Proc0)();
typedef Value (*Proc1)(Value);
typedef Value (*Proc2)(Value, Value);
typedef Value (*Proc3)(Value, Value, Value);

extern map<string, Value> env;
extern map<string, Proc0> p0map;
extern map<string, Proc1> p1map;
extern int at;
extern vector<int> rets;

#define Proc0(f) Value f()
Proc0(fsystem);

#define Proc1(f) Value f(Value)
Proc1(pnot); Proc1(ppos); Proc1(pneg);
Proc1(fatn); Proc1(fcos); Proc1(fsin); Proc1(ftan); Proc1(fsqr);
Proc1(fexp); Proc1(flog); Proc1(fabs); Proc1(ffix); Proc1(fint);

#define Proc2(f) Value f(Value, Value)
Proc2(pand); Proc2(por);  Proc2(pxor); Proc2(pimp); Proc2(peqv);
Proc2(peq);  Proc2(plt);  Proc2(pgt);  Proc2(ple);  Proc2(pge);  Proc2(pne);
Proc2(pmod); Proc2(padd); Proc2(psub); Proc2(pmul); Proc2(pdiv); Proc2(pidiv); Proc2(ppow);
