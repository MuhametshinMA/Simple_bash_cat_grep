#include <stdio.h>
typedef struct Cat_flags {
  char b;
  char n;
  char e;
  char s;
  char t;
  char v;
} Cat_flags;

void without_flags(FILE *file);
void write_non_print_symbols();
void use_flags(int argc, char **argv, Cat_flags *cat_flags);
void set_flags(int argc, char **argv, Cat_flags *cat_flags);
void show_flags(Cat_flags *cat_flags);