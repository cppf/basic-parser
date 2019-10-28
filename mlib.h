#pragma once
#include "mval.h"
#include <map>
#include <vector>

using namespace std;


typedef map<string, Value> Env;
typedef Value (*Fn0)();
typedef Value (*Fn1)(Value);
typedef Value (*Fn2)(Value, Value);

extern map<string, Value> env;
extern map<string, Fn0> f0map;
extern map<string, Fn1> f1map;
extern int at;
extern vector<int> rets;

#define FN0(f) Value f()
FN0(fsystem);

#define FN1(f) Value f(Value)
FN1(pnot); FN1(ppos); FN1(pneg);
FN1(fatn); FN1(fcos); FN1(fsin); FN1(ftan); FN1(fsqr);
FN1(fexp); FN1(flog); FN1(fabs); FN1(ffix); FN1(fint);

#define FN2(f) Value f(Value, Value)
FN2(pand); FN2(por); FN2(pxor); FN2(pimp); FN2(peqv);
FN2(peq); FN2(plt); FN2(pgt); FN2(ple); FN2(pge); FN2(pne);
FN2(pmod); FN2(padd); FN2(psub); FN2(pmul); FN2(pdiv); FN2(pidiv); FN2(ppow);
