#include "grep_flags.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_match(grep_flags *grep_flags, char *buf_str) {
  regex_t reg_ptr;
  int ignore_case_flag = 0;
  int reg_rez = 0;
  char finded = 0;

  for (int i = 0; i < grep_flags->ind_reg_str; i++) {
    // grep - i
    if (grep_flags->i) {
      ignore_case_flag = REG_ICASE;
    }
    //  grep -i
    if (regcomp(&reg_ptr, grep_flags->arr_reg_str[i], ignore_case_flag) == 0) {
      reg_rez = regexec(&reg_ptr, buf_str, 0, NULL, 0);
    }
    if (!reg_rez) {
      finded = 1;
    }
  }
  regfree(&reg_ptr);
  return finded;
}

void get_search_res(int argc, char **argv, grep_flags *grep_flags) {
  int tmp_optind = optind;
  FILE *file = NULL;

  int chars = 0;
  size_t buf_size = 256;
  char *buf_str;
  char lexeme[256] = "";
  buf_str = (char *)malloc(buf_size * sizeof(char));
  while (tmp_optind < argc) {
    int finded_num_str = 1;
    if ((file = fopen(argv[tmp_optind], "r")) != NULL) {
      int count_matches = 0;
      char was_find = 0;
      while ((chars = getline(&buf_str, &buf_size, file)) != -1) {
        // add \n
        if (buf_str[strlen(buf_str) - 1] == '\n') {
          buf_str[strlen(buf_str) - 1] = '\0';
        }
        // add \n
        // flag o
        if (grep_flags->o) {
          strcpy(lexeme, buf_str);
          printf("lexeme: %s\n", lexeme);
        }
        // flag o
        if (((!grep_flags->v) && (find_match(grep_flags, buf_str))) ||
            ((grep_flags->v) && (!find_match(grep_flags, buf_str)))) {
          was_find = 1;
          count_matches++;
          if (!grep_flags->c && !grep_flags->l) {
            // exp
            if (grep_flags->count_files < 2) {
              // flag n
              if (grep_flags->n) {
                printf("%d:%s\n", finded_num_str, buf_str);
              } else {
                printf("%s\n", buf_str);
              }
              // flag n
            } else {
              if (grep_flags->n) {
                if (grep_flags->h) {
                  printf("%d:%s\n", finded_num_str, buf_str);
                } else {
                  printf("%s:%d:%s\n", argv[tmp_optind], finded_num_str,
                         buf_str);
                }
              } else {
                if (grep_flags->h) {
                  printf("%s\n", buf_str);
                } else {
                  printf("%s:%s\n", argv[tmp_optind], buf_str);
                }
              }
            }
            // exp
          }
        }
        // grep n
        finded_num_str++;
        // grep n
      }
      if (was_find) {
        // exp 2
        if (grep_flags->l && !(grep_flags->c)) {
          printf("%s\n", argv[tmp_optind]);
        }
      }
      if ((grep_flags->count_files < 2) && !(grep_flags->l) && grep_flags->c) {
        printf("%d\n", count_matches);
      }
      if ((grep_flags->count_files < 2) && grep_flags->l && grep_flags->c) {
        printf("%d\n%s\n", count_matches, argv[tmp_optind]);
      }
      if (!(grep_flags->count_files < 2) && (grep_flags->l) && grep_flags->c) {
        printf("%s:%d\n", argv[tmp_optind], count_matches);
      }
      if (!(grep_flags->count_files < 2) && !(grep_flags->l) && grep_flags->c) {
        printf("%s:%d\n", argv[tmp_optind], count_matches);
      }
    } else {
      // grep s
      // if (!grep_flags->s) {
      //   printf("s21_grep: %s: No such file or directory",
      //   argv[tmp_optind]);
      // }
      // grep s
    }

    /*if (str[strlen(str) -1] == '\n'){
          str[strlen(str) -1] = '\0'
        }

        puts(str);
        printf("%s\n", str);*/

    tmp_optind++;
  }

  free(buf_str);
  buf_str = NULL;

  fclose(file);
  file = NULL;
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

  static struct option long_options[] = {
      {"e", 1, 0, 1}, {"i", 0, 0, 1}, {"v", 0, 0, 1}, {"c", 0, 0, 1},
      {"l", 0, 0, 1}, {"n", 0, 0, 1}, {"h", 0, 0, 1}, {"s", 0, 0, 1},
      {"f", 1, 0, 1}, {"o", 0, 0, 1}, {0, 0, 0, 0}};
  while ((grep_key =
              getopt_long(argc, argv, "e:ivclnhsf:o", long_options, 0)) != -1) {
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
  }
  if (!grep_flags->e && !grep_flags->f) {
    grep_flags->count_files = argc - optind - 1;
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] != '-') {
        grep_flags->set_reg_arg(grep_flags, argv[i]);
        break;
      }
    }
  } else {
    grep_flags->count_files = argc - optind;
  }
  file = NULL;
  fclose(file);
}

void show_flags(grep_flags *grep_flags) {
  printf("!!!show flag begin!!!\n");
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
  printf("count_files: %d\n", grep_flags->count_files);
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

      if (!strcmp(buf_str, "\n")) {
        grep_flags->set_reg_arg(grep_flags, "**");
        break;
      }
      if (strlen(buf_str) == 1) {
        grep_flags->set_reg_arg(grep_flags, buf_str);
      }
      if (strlen(buf_str) > 1) {
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
