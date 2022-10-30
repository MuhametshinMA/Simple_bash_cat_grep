#include <stdio.h>

#include "cat_flags.h"

int main(int argc, char *argv[]) {
  for (int i = 0; i < argc; i++) {
    printf("i=%d, argc=%d, argv=%s; ", i, argc, argv[i]);
    printf("\n");
  }

  char flag_b = 0;
  char flag_n = 0;
  char flag_e = 0;
  char flag_s = 0;
  char flag_v = 0;
  char flag_t = 0;

  for (int i = 1; i < argc - 1; i++) {
    set_flags(argv[i], &flag_b, &flag_n, &flag_e, &flag_s, &flag_v, &flag_t);
  }

  show_flags(flag_b, flag_n, flag_e, flag_s, flag_v, flag_t);
  for (int i = 1; i < argc - 1; i++) {
    switch (argv[i][1]) {
      case 'n':
        cat_flag_n(argv[argc - 1]);
        break;
      case 'b':
        cat_flag_b(argv[argc - 1]);
        break;
      case 'e':
        cat_flag_e(argv[argc - 1]);
        break;
      case 's':
        // printf("done\n");
        cat_flag_s(argv[argc - 1]);
        break;
    }
  }
  return 0;
}
