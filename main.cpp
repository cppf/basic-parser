#include "main.h"

using namespace std;
extern Ast *yyroot;
extern int yyparse();

int main(int argc, char **argv) {
  yyparse();
  printf("%s\n", yyroot->s().c_str());
  printf("%ld\n", yyroot->eval().i());
  return 0;
}
