#include <stdio.h>

#include "grep_flags.h"

int main(int argc, char *argv[]) {
  grep_flags grep_flags = {0};
  // char reg_str[64] = "";
  grep_flags.set_reg_arg = &set_reg_arg;
  grep_flags.show_reg_args = &show_reg_args;
  // printf("size_reg_str: %d", grep_flags.count_files);

  set_flags(argc, argv, &grep_flags);
  grep_flags.show_reg_args(&grep_flags);
  // show_flags(argc, argv, reg_str, reg_filename, &grep_flags);
  // get_search_res(argc, argv, &grep_flags);

  return 0;
}
