#include <stdio.h>

#include "cat_flags.h"

int main(int argc, char *argv[]) {
  Cat_flags cat_flags = {0};

  set_flags(argc, argv, &cat_flags);

  use_flags(argc, argv, &cat_flags);

  return 0;
}
