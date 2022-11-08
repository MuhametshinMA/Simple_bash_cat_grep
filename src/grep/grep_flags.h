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
  char count_files;
} grep_flags;

void print_str(/*int reg_rez, */char *buf_str, grep_flags *grep_flags, char *file_name);

void get_search_res(int argc, char **argv, char *reg_str, char *reg_filename,
                    grep_flags *grep_flags);
void set_flags(int argc, char **argv, char *reg_str, char *reg_filename,
               grep_flags *grep_flags);
void show_flags(int argc, char **argv, char *reg_str, char *reg_filename,
                grep_flags *grep_flags);
