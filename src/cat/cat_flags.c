#include "cat_flags.h"

#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>

void use_flags(int argc, char **argv, Cat_flags *cat_flags) {
  FILE *file;
  int ch;

  int new_line_count = 1;
  char print_char_flag = 0;

  char is_ch_printed = 1;
  char is_ch_printed_n = 0;

  char can_print = 1;
  for (int i = optind; i < argc; i++) {
    int count_non_empty_str = 0;
    int count_new_str_n = 0;
    if ((file = fopen(argv[i], "r")) != NULL) {
      while (!feof(file) && !ferror(file)) {
        ch = getc(file);
        if (ch != EOF) {
          // s flag
          if (cat_flags->s) {
            if (ch == '\n') {
              if (new_line_count < 2) {
                new_line_count++;
                print_char_flag = 1;
              } else {
                print_char_flag = 0;
              }
            } else {
              new_line_count = 0;
              print_char_flag = 1;
            }
          } else {
            print_char_flag = 1;
          }
          // s flag

          if (print_char_flag) {
            // b flag
            if (cat_flags->b) {
              if (ch == '\n') {
                is_ch_printed = 1;
              } else {
                if (is_ch_printed) {
                  printf("%6d\t", ++count_non_empty_str);
                  is_ch_printed = 0;
                }
              }
            }
            // b flag

            // n flag
            if (cat_flags->n && !(cat_flags->b)) {
              if (!is_ch_printed_n) {
                printf("%6d\t", ++count_new_str_n);
                is_ch_printed_n = 1;
              }
              if (ch == '\n') {
                is_ch_printed_n = 0;
              }
            }
            // n flag

            // e flag
            if (cat_flags->e && (ch == '\n')) {
              printf("$");
            }
            // e flag

            // t flag
            if (cat_flags->t && (ch == 9)) {
              printf("^I");
              can_print = 0;
            }
            // t flag

            // v flag
            if (cat_flags->v) {
              if (((ch >= 0) && (ch < 9)) || ((ch > 10) && (ch < 32))) {
                putchar('^');
                putchar(ch + 64);
                can_print = 0;
              }
              if (ch == 127) {
                putchar('^');
                putchar(ch - 64);
                can_print = 0;
              }
              if ((ch > 127) && (ch < 160)) {
                putchar('-');
                putchar('M');
                putchar('^');
                putchar(ch % 128 + 64);
                can_print = 0;
              }
            }
            // v flag

            if (can_print) {
              putchar(ch);
            } else {
              can_print = 1;
            }
          }
        }
      }
    }
    fclose(file);
  }
}

void set_flags(int argc, char **argv, Cat_flags *cat_flags) {
  char cat_key = 0;
  static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                         {"number", 0, 0, 'n'},
                                         {"squeeze-blank", 0, 0, 's'},
                                         {0, 0, 0, 0}};
  while ((cat_key = getopt_long(argc, argv, "bentsvET", long_options, 0)) !=
         -1) {
    switch (cat_key) {
      case 'b':
        cat_flags->b = 1;
        break;
      case 'e':
        cat_flags->e = 1;
        cat_flags->v = 1;
        break;
      case 'n':
        cat_flags->n = 1;
        break;
      case 't':
        cat_flags->t = 1;
        cat_flags->v = 1;
        break;
      case 's':
        cat_flags->s = 1;
        break;
      case 'v':
        cat_flags->v = 1;
        break;
      case 'E':
        cat_flags->e = 1;
        break;
      case 'T':
        cat_flags->t = 1;
        break;
      default:
        break;
    }
  }
}

void show_flags(Cat_flags *cat_flags) {
  printf("b: %d\ne: %d\nn: %d\nt: %d\ns: %d\nv: %d\n", cat_flags->b,
         cat_flags->e, cat_flags->n, cat_flags->t, cat_flags->s, cat_flags->v);
}
