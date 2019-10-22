#include "main.h"

using namespace std;
extern Ast *yyroot;
extern int yyparse();

int main(int argc, char **argv) {
  yyparse();
  printf("%s\n", yyroot->str().c_str());
  return 0;
}
