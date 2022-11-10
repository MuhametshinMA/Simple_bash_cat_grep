#include "grep_flags.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void get_search_res(int argc, char **argv, grep_flags *grep_flags) {
  int tmp_optind = optind;
  FILE *file = NULL;
  regex_t reg_ptr;

  int chars = 0;
  size_t buf_size = 256;
  char *buf_str;
  buf_str = (char *)malloc(buf_size * sizeof(char));

  int reg_rez = 0;
  size_t n_match = 1;
  regmatch_t p_match[1];

  int ignore_case_flag = 0;

  int count_equal_str = 0;

  char was_equal = 0;
  //  char continue_flag = 0;
  // int str_count = 0;
  show_reg_args(grep_flags);
  while (tmp_optind < argc) {
    if ((file = fopen(argv[tmp_optind], "r")) != NULL) {
      int finded_num_str = 0;

      while ((chars = getline(&buf_str, &buf_size, file)) != -1) {
        // printf("%d chars: %d\n", ++str_count, chars);
        for (int i = 0; i < grep_flags->ind_reg_str; i++) {
          //  grep -i
          if (grep_flags->i) {
            ignore_case_flag = REG_ICASE;
          }
          //  grep -i
          if (regcomp(&reg_ptr, grep_flags->arr_reg_str[i], ignore_case_flag) ==
              0) {
            reg_rez = regexec(&reg_ptr, buf_str, n_match, p_match, 0);
          }
          // printf("status: %d reg: %s result: %s", reg_rez,
          // grep_flags->arr_reg_str[i], buf_str);
          // grep n
          finded_num_str++;
          // grep n

          // grep v
          if (grep_flags->v) {
            if (reg_rez) {
              // printf("status: %d\n", reg_rez);
              print_str(buf_str, grep_flags, argv[tmp_optind], finded_num_str);
              count_equal_str++;
              // grep l
              was_equal = 1;
              // grep l
              // continue_flag = 1;
              break;
            }
          } else {
            // printf("status: %d\n", reg_rez);
            if (!reg_rez) {
              // printf("in %d\n", str_count);
              print_str(buf_str, grep_flags, argv[tmp_optind], finded_num_str);
              count_equal_str++;
              // grep l
              was_equal = 1;
              // grep l
              // continue_flag = 1;
              break;
            }
          }
          // grep v
        }
        // if (continue_flag) {
        //   continue;
        //   continue_flag = 0;
        // }
        // printf("done: %d\n", str_count);
      }
      // grep c
      if (grep_flags->c) {
        printf("%d\n", count_equal_str);
      }
      // grep c
    } else {
      if (!grep_flags->s) {
        printf("s21_grep: %s: No such file or directory", argv[tmp_optind]);
      }
    }

    // grep l
    if (grep_flags->l && was_equal) {
      printf("flag_l: %s\n", argv[tmp_optind]);
      was_equal = 0;
    }
    // grep l
    tmp_optind++;
  }
  buf_str = NULL;
  free(buf_str);
  regfree(&reg_ptr);
  file = NULL;
  fclose(file);
}

void print_str(char *buf_str, grep_flags *grep_flags, char *file_name,
               int finded_num_str) {
  if (!grep_flags->c && !grep_flags->l) {
    if (grep_flags->count_files < 2) {
      //  flag n
      if (grep_flags->n) {
        printf("%d:%s", finded_num_str, buf_str);
      } else {
        printf("%s", buf_str);
      }
      // flag n
    } else {
      if (grep_flags->n) {
        if (grep_flags->h) {
          printf("%d:%s", finded_num_str, buf_str);
        } else {
          printf("%s:%d:%s", file_name, finded_num_str, buf_str);
        }
      } else {
        if (grep_flags->h) {
          printf("%s", buf_str);
        } else {
          printf("%s:%s", file_name, buf_str);
        }
      }
    }
  }
}

void set_flags(int argc, char **argv, grep_flags *grep_flags) {
  FILE *file = NULL;
  char grep_key = 0;
  int tmp_optind = 0;
  while ((grep_key = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (grep_key) {
      case 'e':
        grep_flags->e = 1;
        grep_flags->set_reg_arg(grep_flags, optarg);
        break;
      case 'i':
        grep_flags->i = 1;
        break;
      case 'v':
        grep_flags->v = 1;
        break;
      case 'c':
        grep_flags->c = 1;
        break;
      case 'l':
        grep_flags->l = 1;
        break;
      case 'n':
        grep_flags->n = 1;
        break;
      case 'h':
        grep_flags->h = 1;
        break;
      case 's':
        grep_flags->s = 1;
        break;
      case 'f':
        grep_flags->f = 1;
        grep_flags->set_regs_from_file(grep_flags, optarg);
        break;
      case 'o':
        grep_flags->o = 1;
        break;
      default:
        break;
    }
    tmp_optind = optind;
  }

  while (tmp_optind < argc) {
    if ((file = fopen(argv[tmp_optind], "r")) != NULL) {
      grep_flags->count_files++;
    }
    tmp_optind++;
  }

  if (!grep_flags->e && !grep_flags->f) {
    grep_flags->set_reg_arg(grep_flags, optarg);
  }
  file = NULL;
  fclose(file);
}

void show_flags(int argc, char **argv, grep_flags *grep_flags) {
  int tmp_optind = optind;
  (void)argc;
  printf("e: %d, ", grep_flags->e);
  printf("i: %d, ", grep_flags->i);
  printf("v: %d, ", grep_flags->v);
  printf("c: %d, ", grep_flags->c);
  printf("l: %d, ", grep_flags->l);
  printf("n: %d, ", grep_flags->n);
  printf("h: %d, ", grep_flags->h);
  printf("s: %d, ", grep_flags->s);
  printf("f: %d, ", grep_flags->f);
  printf("o: %d\n", grep_flags->o);
  printf("file: %s\n", argv[tmp_optind++]);
  printf("!!!show flag end!!!\n");
}

// struct methods
void set_regs_from_file(grep_flags *grep_flags, char *file_name) {
  FILE *file = NULL;
  char chars = 0;
  size_t buf_size = 256;
  char *buf_str = NULL;

  if ((file = fopen(file_name, "r")) != NULL) {
    while ((chars = getline(&buf_str, &buf_size, file)) != -1) {
      char reg_tmp[255] = {0};
      if (strlen(buf_str) == 1) {
        // memcpy(reg_tmp, buf_str, strlen(buf_str));
        grep_flags->set_reg_arg(grep_flags, "**");
      } else {
        memcpy(reg_tmp, buf_str, strlen(buf_str) - 1);
        grep_flags->set_reg_arg(grep_flags, reg_tmp);
      }
    }
  } else {
    printf("%s no file\n", file_name);
  }
  buf_str = NULL;
  free(buf_str);
  fclose(file);
}

void set_reg_arg(grep_flags *grep_flags, char *reg_str) {
  strcpy(grep_flags->arr_reg_str[grep_flags->ind_reg_str], reg_str);
  grep_flags->ind_reg_str++;
}

void show_reg_args(grep_flags *grep_flags) {
  printf("current index: %d\n", grep_flags->ind_reg_str);
  for (int i = 0; i < grep_flags->ind_reg_str; i++) {
    printf("%d:%s\n", i, grep_flags->arr_reg_str[i]);
  }
}
// struct methods
