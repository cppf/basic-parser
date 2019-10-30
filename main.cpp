#include "mast.h"

using namespace std;


extern Ast *yyroot;
extern int yyparse();

int main(int argc, char **argv) {
  string s;
  yyparse();
  printf("parsing done: %p\n", yyroot);
  printf("%s\n", yyroot->s().c_str());
  printf("%s\n", yyroot->eval(env).s().c_str());
  printf("%s\n", env["a"].s().c_str());
  return 0;
}


void yyerror(const char *s) {
  fprintf(stderr, "error: %s\n", s);
}
