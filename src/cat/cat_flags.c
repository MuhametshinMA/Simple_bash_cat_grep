#include "cat_flags.h"

#include <stdio.h>
#include <string.h>

void use_flags(const char *filename, char *b, char *n, char *e, char *s,
               char *t, char *v) {
  FILE *file = fopen(filename, "r");
  char ch;
  int count_new_str_ch = 0;
  int count_new_str_ch_b = 0;
  char print_char_flag = 0;
  char print_new_line_flag = 0;
  //   char buf_str[255];
  int count_str = 0;
  if ((file = fopen(filename, "r")) != NULL) {
    if (!(*b || *n || *e || *s || *t || *v)) {
      without_flags(file);
    }
    while (!feof(file) && !ferror(file)) {
      ch = getc(file);
      if (ch != EOF) {
        // s flag
        if (*s && (ch == '\n')) {
          ++count_new_str_ch;
          if (count_new_str_ch < 3) {
            putchar('\n');
          }
        } else {
          count_new_str_ch = 0;
          print_char_flag = 1;
          print_new_line_flag = 1;
        }
        // s flag

        // t flag
        if (*t && (ch == 9)) {
          printf("^I");
        } else {
          print_char_flag = 1;
        }

        // t flag

        // v flag
        if (*v) {
          if (ch < 32) {
            if ((ch == 10) || (ch == 9)) {
              print_char_flag = 1;
            } else {
              printf("^%c", ch + 64);
            }
          } else {
            print_char_flag = 1;
          }
          if ((ch == 127)) {
            printf("^%c", ch - 64);
          }
        }
        // v flag
        // e flag
        if (*e && (ch == '\n')) {
          printf("$");
          // printf("flag e works");
        } else {
          print_char_flag = 1;
        }
        // e flag

        // b flag
        if (*b) {
          if (ch == '\n') {
            ++count_new_str_ch_b;
            if (count_new_str_ch_b < 2) {
              printf("\n%d", count_str++);
            }
          } else {
            count_new_str_ch = 0;
            print_char_flag = 1;
            print_new_line_flag = 1;
          }
        }
        // b flag
        if (print_char_flag && print_new_line_flag) {
          putchar(ch);
        }
        print_char_flag = 0;
        print_new_line_flag = 0;
      }
    }
    if (*n) {
      printf("flag n works");
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

void cat_flag_b(const char *filename) {
  FILE *file;
  char buf_str[255];
  int count_str = 0;
  if ((file = fopen(filename, "r")) != NULL) {
    while ((fgets(buf_str, 255, file)) != NULL) {
      if (strlen(buf_str) > 1) {
        printf("    %d  %s", ++count_str, buf_str);
      } else {
        printf("\n");
      }
    }
  } else {
    perror("can't read file");
  }
  fclose(file);
}

void cat_flag_n(const char *filename) {
  FILE *file;
  char buf_str[255];
  int num_str = 0;
  if ((file = fopen(filename, "r")) != NULL) {
    while ((fgets(buf_str, 255, file)) != NULL) {
      printf("%d    %s", ++num_str, buf_str);
    }
  } else {
    perror("can't read file");
  }
  fclose(file);
}

void set_flags(const char *str, char *b, char *n, char *e, char *s, char *t,
               char *v) {
  if (str[1] == 'b') {
    *b = str[1];
  }
  if (str[1] == 'n') {
    *n = str[1];
  }
  if (str[1] == 'e') {
    *e = str[1];
    *v = 'v';
  }
  if (str[1] == 's') {
    *s = str[1];
  }
  if (str[1] == 't') {
    *t = str[1];
    *v = 'v';
  }
  if (str[1] == 'v') {
    *v = str[1];
  }
}

void show_flags(char b, char n, char e, char s, char t, char v) {
  if (b == 'b') {
    printf("flag b exists\n");
  }
  if (n == 'n') {
    printf("flag n exists\n");
  }
  if (e == 'e') {
    printf("flag e exists\n");
  }
  if (s == 's') {
    printf("flag s exists\n");
  }
  if (t == 't') {
    printf("flag t exists\n");
  }
  if (v == 'v') {
    printf("flag v exists\n");
  }
}
