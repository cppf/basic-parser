#include "mstp.h"
#include <string>
#include <sstream>


string Step::s() {
  stringstream o;
  tos(o); return o.str();
}

ostream& operator <<(ostream& o, Step& s) {
  s.tos(o); return o;
}

void Step::tos(ostream& o) { switch(t) {
  case LITERAL: o<<"\'"<<v.s()<<"\'"; return;
  case ID: o<<v.s(); return;
  case LET: o<<"LET "<<v.s()<<" = "<<*a; return;
  case GOTO: o<<"GOTO "<<v.s(); return;
  case GOSUB: o<<"GOSUB "<<v.s(); return;
  case RETURN: o<<"RETURN"; return;
  case TGOTO: o<<"TGOTO "<<*a<<" "<<v.s(); return;
  case FGOTO: o<<"FGOTO "<<*a<<" "<<v.s(); return;
  case CALL0: o<<p.p0<<"()"; return;
  case CALL1: o<<p.p1<<"("<<*a<<")"; return;
  case CALL2: o<<p.p2<<"("<<*a<<" "<<*b<<")"; return;
  case CALL3: o<<p.p3<<"("<<*a<<" "<<*b<<" "<<*c<<")"; return;
  case PCALL: 
}}
