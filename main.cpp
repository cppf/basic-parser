#include "mast.h"

using namespace std;
extern Ast *yyroot;
extern int yyparse();

int main(int argc, char **argv) {
  yyparse();
  printf("%s\n", yyroot->s().c_str());
  printf("%s\n", yyroot->eval().s().c_str());
  return 0;
}


