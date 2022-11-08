#include <stdio.h>

#include "grep_flags.h"

int main(int argc, char *argv[]) {
  grep_flags grep_flags = {0};
  char reg_str[64] = "";
  char reg_filename[32] = "";
  set_flags(argc, argv, reg_str, reg_filename, &grep_flags);
  // show_flags(argc, argv, reg_str, reg_filename, &grep_flags);
  get_search_res(argc, argv, reg_str, reg_filename, &grep_flags);

  return 0;
}
