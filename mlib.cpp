#include "mlib.h"
#include <map>
#include <cmath>

using namespace std;



int addr;
vector<int> stack;
map<string, Value> env;

map<string, Fn0> f0map = {
  {"system", fsystem}
};
map<string, Fn1> f1map = {
  {"not", pnot}, {"+", ppos}, {"-", pneg},
  {"atn", fatn}, {"cos", fcos}, {"sin", fsin}, {"tan", ftan}, {"sqr", fsqr},
  {"exp", fexp}, {"log", flog}, {"abs", fabs}, {"fix", ffix}, {"int", fint}
};
map<string, Fn2> f2map = {
  {"and", pand}, {"or", por}, {"xor", pxor}, {"imp", pimp}, {"eqv", peqv},
  {"=", peq}, {"<", plt}, {">", pgt}, {"<=", ple}, {">=", pge}, {"<>", pne},
  {"mod", pmod}, {"+", padd}, {"-", psub}, {"*", pmul}, {"/", pdiv},
  {"\\", pidiv}, {"^", ppow}
};



// Value fgoto(Value x) {
//   addr = x.i(); return false;
// }

// Value fgosub(Value x) {
//   rets.push_back(at);
//   at = x.i(); return false;
// }

// Value freturn() {
//   at = rets.back();
//   rets.pop_back();
//   return false;
// }

Value pand(Value x, Value y) { switch (max(x.t, y.t)) {
  case BOL: return x.b() && y.b();
  case INT: return x.i() & y.i();
}}

Value por(Value x, Value y) { switch(max(x.t, y.t)) {
  case BOL: return x.b() || y.b();
  case INT: return x.i() | y.i();
}}

Value pxor(Value x, Value y) { switch (max(x.t, y.t)) {
  case BOL: return (bool) (x.b() ^ y.b());
  case INT: return x.i() ^ y.i();
}}

Value pimp(Value x, Value y) { switch (max(x.t, y.t)) {
  case BOL: return !x.b() && y.b();
  case INT: return ~x.i() & y.i();
}}

Value peqv(Value x, Value y) { switch (max(x.t, y.t)) {
  case BOL: return x.b() == y.b();
  case INT: return x.i() ^ ~y.i();
}}

Value pnot(Value x) { switch (x.t) {
  case BOL: return !x.b();
  case INT: return ~x.i();
}}

Value peq(Value x, Value y) { switch (max(x.t, y.t)) {
  case BOL: return x.b() == y.b();
  case INT: return x.i() == y.i();
  case DEC: return x.d() == y.d();
  case STR: return x.s() == y.s();
}}

Value plt(Value x, Value y) { switch (max(x.t, y.t)) {
  case INT: return x.i() < y.i();
  case DEC: return x.d() < y.d();
}}

Value pgt(Value x, Value y) { switch (max(x.t, y.t)) {
  case INT: return x.i() > y.i();
  case DEC: return x.d() > y.d();
}}

Value ple(Value x, Value y) { switch (max(x.t, y.t)) {
  case INT: return x.i() <= y.i();
  case DEC: return x.d() <= y.d();
}}

Value pge(Value x, Value y) { switch (max(x.t, y.t)) {
  case INT: return x.i() >= y.i();
  case DEC: return x.d() >= y.d();
}}

Value pne(Value x, Value y) { switch (max(x.t, y.t)) {
  case BOL: return x.b() != y.b();
  case INT: return x.i() != y.i();
  case DEC: return x.d() != y.d();
  case STR: return x.s() != y.s();
}}

Value pmod(Value x, Value y) { switch (max(x.t, y.t)) {
  case INT: return x.i() % y.i();
  case DEC: return fmod(x.d(), y.d());
}}

Value ppos(Value x) { switch(x.t) {
  case INT: return x.i();
  case DEC: return x.d();
}}

Value pneg(Value x) { switch(x.t) {
  case INT: return -x.i();
  case DEC: return -x.d();
}}

// not sure about strings: memory leak?
Value padd(Value x, Value y) { switch (max(x.t, y.t)) {
  case INT: return x.i() + y.i();
  case DEC: return x.d() + y.d();
  case STR: return new string(x.s() + y.s());
}}

Value psub(Value x, Value y) { switch (max(x.t, y.t)) {
  case INT: return x.i() - y.i();
  case DEC: return x.d() - y.d();
}}

Value pmul(Value x, Value y) { switch (max(x.t, y.t)) {
  case INT: return x.i() * y.i();
  case DEC: return x.d() * y.d();
}}

Value pdiv(Value x, Value y) { switch (max(x.t, y.t)) {
  case INT: case DEC: return x.d() / y.d();
}}

Value pidiv(Value x, Value y) { switch (max(x.t, y.t)) {
  case INT: return x.i() / y.i();
  case DEC: return x.d() / y.d();
}}

Value ppow(Value x, Value y) { switch (max(x.t, y.t)) {
  case INT: return (long) pow(x.i(), y.i());
  case DEC: return pow(x.d(), y.d());
}}


// functions:
Value fatn(Value x) { switch (x.t) {
  case INT: case DEC: return atan(x.d());
}}

Value fcos(Value x) { switch (x.t) {
  case INT: case DEC: return cos(x.d());
}}

Value fsin(Value x) { switch (x.t) {
  case INT: case DEC: return sin(x.d());
}}

Value ftan(Value x) { switch (x.t) {
  case INT: case DEC: return tan(x.d());
}}

Value fsqr(Value x) { switch(x.t) {
  case INT: case DEC: return sqrt(x.d());
}}

Value fexp(Value x) { switch (x.t) {
  case INT: case DEC: return exp(x.d());
}}

Value flog(Value x) { switch (x.t) {
  case INT: case DEC: return log(x.d());
}}

Value fabs(Value x) { switch (x.t) {
  case INT: return abs(x.i());
  case DEC: return abs(x.d());
}}

Value ffix(Value x) { switch (x.t) {
  case INT: case DEC: return (long) x.d();
}}

Value fint(Value x) { switch (x.t) {
  case INT: case DEC: return (long) floor(x.d());
}}

// hex$, oct$
Value fhex(Value x) { switch (x.t) {
  case INT: case DEC: return new string(to_string((long) x.d()));
}}

// cint, clng
Value fcint(Value x) { switch (x.t) {
  case BOL: case INT: case DEC: return (long) x.d();
}}

// cdbl, csng
Value fcdec(Value x) { switch (x.t) {
  case BOL: case INT: case DEC: return x.d();
}}

// ucase$
Value fucase(Value x) { switch (x.t) {
  case STR: return new string(x.s()); // to uppercase
}}

// lcase$
Value flcase(Value x) { switch (x.t) {
  case STR: return new string(x.s()); // to lowercase
}}

// string$
Value fstring(Value l, Value s) { switch (s.t) {
  case INT: case DEC: return fstring(l, new string(s.s()));
  case STR: string *a = new string(); char c = s.s()[0];
  for (int i=l.i(); i>=0; i--) *a+=c;
  return a;
}}

// str$
Value fstr(Value x) {
  return new string(x.s());
}

Value fval(Value x) { switch (x.t) {
  case STR: return strtod(x.s().c_str(), NULL);
}}

Value fasc(Value x) { switch (x.t) {
  case STR: return (long) x.s()[0];
}}

// chr$
Value fchr(Value x) { switch (x.t) {
  case INT: case DEC:
  string *s = new string();
  s[0] = (char) x.d();
  return s;
}}

Value fsystem() {
  exit(0);
  return false;
}
