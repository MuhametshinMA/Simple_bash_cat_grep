#include <stdio.h>

void without_flags(FILE *file);
void cat_s_flag(char ch, char *s_flag, int count_new_str_ch);
void write_non_print_symbols();
void use_flags(const char *filename, char *b, char *n, char *e, char *s,
               char *t, char *v);
void cat_flag_v(const char *filename);
void cat_flag_n(const char *filename);
void cat_flag_e(const char *filename);
void cat_flag_b(const char *filename);
void cat_flag_s(const char *filename);
void cat_flag_t(const char *filename);
void set_flags(const char *str, char *b, char *n, char *e, char *s, char *t,
               char *v);
void show_flags(char b, char n, char e, char s, char t, char v);