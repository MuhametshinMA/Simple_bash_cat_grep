#include <regex.h>
#include <stdio.h>

#include "grep_flags.h"

int main(int argc, char *argv[]) {
  regex_t regex;
  grep_flags grep_flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  char reg_str[64] = "";
  set_flags(argc, argv, reg_str, &grep_flags);
  show_flags(argc, argv, reg_str, &grep_flags);
  regfree(&regex);
  return 0;
}
