#include <stdio.h>

#include "grep_flags.h"

int main(int argc, char *argv[]) {
  grep_flags grep_flags = {0};
  grep_flags.set_reg_arg = &set_reg_arg;
  grep_flags.set_regs_from_file = &set_regs_from_file;
  grep_flags.show_reg_args = &show_reg_args;

  set_flags(argc, argv, &grep_flags);
  //  grep_flags.show_reg_args(&grep_flags);
  // show_flags(&grep_flags);
  get_search_res(argc, argv, &grep_flags);
  return 0;
}
