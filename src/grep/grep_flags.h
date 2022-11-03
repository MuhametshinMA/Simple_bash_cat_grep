typedef struct Grep_flags {
  char e;
  char i;
  char v;
  char c;
  char l;
  char n;
  char h;
  char s;
  char f;
  char o;
} grep_flags;

void set_flags(int argc, char **argv, char *reg_str, grep_flags *grep_flags);
void show_flags(int argc, char **argv, char *reg_str, grep_flags *grep_flags);