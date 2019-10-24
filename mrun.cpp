#include "mrun.h"
#include <map>
#include <cmath>

using namespace std;


// environment:
map<string, Value> env;

// primitive names:
map<Fn1, string> pname1 = {{pnot, "not"}, {ppos, "+"}, {pneg, "-"}};
map<Fn2, string> pname2 = {
  {pand, "and"}, {por, "or"}, {pxor, "xor"}, {pimp, "imp"}, {peqv, "eqv"},
  {peq, "="}, {plt, "<"}, {pgt, ">"}, {ple, "<="}, {pge, ">="}, {pne, "<>"},
  {pmod, "mod"}, {padd, "+"}, {psub, "-"}, {pmul, "*"}, {pdiv, "/"},
  {pidiv, "\\"}, {ppow, "^"}
};


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
