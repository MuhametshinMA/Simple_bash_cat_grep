#include "cat_flags.h"

#include <stdio.h>
#include <string.h>

void cat_flag_s(const char *filename) {
  int ch;
  // int count_new_str_ch = 0;
  FILE *file = fopen(filename, "r");
  while (!feof(file) && !ferror(file)) {
    ch = getc(file);
    if (ch != EOF) {
      if (ch == '\n') {
        printf("$\n");
        // putchar('\n');
        //  printf("%d  ", num_str++);
      } else {
        putchar(ch);
      }
    }
  }
  putchar('$');
  putchar('\n');
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

void cat_flag_e(const char *filename) {
  FILE *file;
  char buf_str[255];
  if ((file = fopen(filename, "r")) != NULL) {
    while ((fgets(buf_str, 255, file)) != NULL) {
      char copyed_str[strlen(buf_str)];
      if (strlen(buf_str) > 1) {
        strcpy(copyed_str, buf_str);
        copyed_str[strlen(buf_str) - 2] = '$';
        copyed_str[strlen(buf_str) - 1] = '\n';
        printf("%s", copyed_str);
      } else {
        printf("$\n");
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
  }
  if (str[1] == 's') {
    *s = str[1];
  }
  if (str[1] == 't') {
    *t = str[1];
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
/*
void cat_flag_n(const char* filename)
{
  int ch;
  int num_str = 1;

  FILE *file = fopen(filename, "r");
  while (!feof(file) && !ferror(file))
  {
    ch = getc(file);
    if (ch != EOF) {
      if (ch == '\n') {
        putchar('\n');
        printf("%d  ", num_str++);
      } else {
        putchar(ch);
      }
    }
  }
  putchar('\n');
}
*/
/*
void cat_flag_b(const char* filename)
{
  int ch;
  int num_str = 1;
  int end_str = 0;
  FILE *file = fopen(filename, "r");
  while (!feof(file) && !ferror(file))
  {
    ch = getc(file);
    if (ch != EOF) {
      if (ch == '\n') {
        //putchar('\n');
        end_str++;
        if (end_str > 0)
        {
          putchar(ch);
        } else {
        putchar(ch);
        printf("%d  ", num_str++);
        num_str = 0;
        }
      } else {
        putchar(ch);
      }
    }
  }
  putchar('\n');
}
*/
