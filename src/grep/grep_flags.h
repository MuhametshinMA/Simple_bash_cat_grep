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
  char arr_reg_str[1024][256];
  int ind_reg_str;
  void (*set_reg_arg)();
  void (*set_regs_from_file)();
  void (*show_reg_args)();
  char *reg_str;
} grep_flags;

// struct methods
void set_regs_from_file(grep_flags *grep_flags, char *file_name);
void set_reg_arg(grep_flags *grep_flags, char *reg_str);
void show_reg_args(grep_flags *grep_flags);
// struct methods

void print_str(char *buf_str, grep_flags *grep_flags, char *file_name,
               int finded_num_str);

void get_search_res(int argc, char **argv, grep_flags *grep_flags);
void set_flags(int argc, char **argv, grep_flags *grep_flags);
void show_flags(int argc, char **argv, grep_flags *grep_flags);
