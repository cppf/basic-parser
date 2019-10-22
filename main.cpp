#include "main.h"

using namespace std;
extern int yyparse();

int main(int argc, char **argv) {
  yyparse();
  return 0;
}
