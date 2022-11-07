#include "cat_flags.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

void use_flags(const char *filename, char *b, char *n, char *e, char *s,
               char *t, char *v) {
  FILE *file;
  int ch;
  int new_line_count = 1;
  int count_new_str_n = 0;
  char print_char_flag = 0;

  char is_ch_printed = 1;
  char is_ch_printed_n = 0;

  int count_non_empty_str = 0;

  char can_print = 1;

  if ((file = fopen(filename, "r")) != NULL) {
    if (!(*b || *n || *e || *s || *t || *v)) {
      without_flags(file);
    }
    while (!feof(file) && !ferror(file)) {
      ch = getc(file);
      if (ch != EOF) {
        // s flag
        if (*s) {
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
          if (*b) {
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
          if (*n && !(*b)) {
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
          if (*e && (ch == '\n')) {
            printf("$");
          }
          // e flag

          // t flag
          if (*t && (ch == 9)) {
            printf("^I");
            can_print = 0;
          }
          // t flag

          // v flag
          if (*v) {
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

          // putchar(ch);
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

void without_flags(FILE *file) {
  int ch;
  while (!feof(file) && !ferror(file)) {
    ch = getc(file);
    if (ch != EOF) {
      putchar(ch);
    }
  }
}

void write_non_print_symbols() {
  printf("\n\n\n");
  printf("test");
  printf("\n\n");
  for (int i = 0; i < 32;) {
    printf("%c, ", i++);
  }
  printf("%c", 127);
}

void set_flags(const char *str, char *b, char *n, char *e, char *s, char *t,
               char *v) {
  if ((str[1] == 'b') || (!strcmp(str, "--number-nonblank"))) {
    *b = str[1];
  }
  if ((str[1] == 'n') || (!strcmp(str, "--number"))) {
    *n = str[1];
  }
  if (str[1] == 'e') {
    *e = str[1];
    *v = 'v';
  }
  if (str[1] == 'E') {
    *e = str[1];
  }
  if ((str[1] == 's') || (!strcmp(str, "--squeeze-blank"))) {
    *s = str[1];
  }
  if (str[1] == 't') {
    *t = str[1];
    *v = 'v';
  }
  if (str[1] == 'T') {
    *t = str[1];
  }
  if (str[1] == 'v') {
    *v = str[1];
  }
}

void show_flags(char b, char n, char e, char s, char t, char v) {
  if (b) {
    printf("flag b exists\n");
  }
  if (n) {
    printf("flag n exists\n");
  }
  if (e) {
    printf("flag e exists\n");
  }
  if (s) {
    printf("flag s exists\n");
  }
  if (t) {
    printf("flag t exists\n");
  }
  if (v) {
    printf("flag v exists\n");
  }
}
