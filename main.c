#include "value.h"
#include <stdio.h>


int main(int argc, char ** argv) {
  Value x = {VOID, {f: 2.45}};
  printf("%d: %f\n", x.t, x.v.f);
}
