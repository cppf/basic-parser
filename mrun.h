#pragma once
#include "mval.h"
#include <map>

using namespace std;


typedef map<string, Value> Env;
typedef Value (*Fn0)();
typedef Value (*Fn1)(Value);
typedef Value (*Fn2)(Value, Value);

extern map<string, Value> env;
extern map<string, Fn0> f0map;
extern map<string, Fn1> f1map;
extern map<Fn1, string> pname1;
extern map<Fn2, string> pname2;

#define FN0(f) Value f()

#define FN1(f) Value f(Value)
FN1(pnot); FN1(ppos); FN1(pneg);

#define FN2(f) Value f(Value, Value)
FN2(pand); FN2(por); FN2(pxor); FN2(pimp); FN2(peqv);
FN2(peq); FN2(plt); FN2(pgt); FN2(ple); FN2(pge); FN2(pne);
FN2(pmod); FN2(padd); FN2(psub); FN2(pmul); FN2(pdiv); FN2(pidiv); FN2(ppow);
