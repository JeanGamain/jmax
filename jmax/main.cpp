#include <stdio.h>
#include "load.hpp"
#include "jmax.hpp"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    jmax::engine	test(800, 600, argv[1]);
  }
  return 0;
}
