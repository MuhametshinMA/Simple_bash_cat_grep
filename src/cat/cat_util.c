#include <stdio.h>

#include "cat_flags.h"

int main(int argc, char *argv[]) {
  char flag_b = 0;
  char flag_n = 0;
  char flag_e = 0;
  char flag_s = 0;
  char flag_v = 0;
  char flag_t = 0;

  for (int i = 1; i < argc - 1; i++) {
    set_flags(argv[i], &flag_b, &flag_n, &flag_e, &flag_s, &flag_v, &flag_t);
  }

  use_flags(argv[argc - 1], &flag_b, &flag_n, &flag_e, &flag_s, &flag_v,
            &flag_t);
  show_flags(flag_b, flag_n, flag_e, flag_s, flag_v, flag_t);
  return 0;
}
