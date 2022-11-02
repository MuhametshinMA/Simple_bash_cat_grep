#include <stdio.h>

void without_flags(FILE *file);
void write_non_print_symbols();
void use_flags(const char *filename, char *b, char *n, char *e, char *s,
               char *t, char *v);
void set_flags(const char *str, char *b, char *n, char *e, char *s, char *t,
               char *v);
void show_flags(char b, char n, char e, char s, char t, char v);