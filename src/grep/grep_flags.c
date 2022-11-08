#include "grep_flags.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void get_search_res(int argc, char **argv, char *reg_str, char *reg_filename,
                    grep_flags *grep_flags) {
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
  // int can_print = 0;
  int count_equal_str = 0;

  char was_equal = 0;

  // printf("reg_str: %s\n", reg_str);
  printf("reg_filename: %s\n", reg_filename);
  while (tmp_optind < argc) {
    // printf("optind: %d\n", tmp_optind);
    // printf("reg_str: %s\n", reg_str);
    // printf("\n!!!!%s!!!\n", argv[tmp_optind]);
    if ((file = fopen(argv[tmp_optind], "r")) != NULL) {
      // printf("optind: %d; file: %s; reg_str: %s\n", tmp_optind,
      //        argv[tmp_optind], reg_str);
      while ((chars = getline(&buf_str, &buf_size, file)) != -1) {
        // printf("  %d   %s", chars, buf_str);

        //  grep -i
        if (grep_flags->i) {
          ignore_case_flag = REG_ICASE;
        }
        //  grep -i

        if (regcomp(&reg_ptr, reg_str, ignore_case_flag) == 0) {
          reg_rez = regexec(&reg_ptr, buf_str, n_match, p_match, 0);
        }

        // grep v
        if (grep_flags->v) {
          if (reg_rez) {
            print_str(/*reg_rez, */ buf_str, grep_flags, argv[tmp_optind]);
            count_equal_str++;
            // grep l
            was_equal = 1;
            // grep l
          }
        } else {
          if (!reg_rez) {
            print_str(/*reg_rez, */ buf_str, grep_flags, argv[tmp_optind]);
            count_equal_str++;
            // grep l
            was_equal = 1;
            // grep l
          }
        }
        // grep v
      }
      // grep c
      if (grep_flags->c) {
        printf("%d\n", count_equal_str);
      }
      // grep c
    }

    // grep l
    if (grep_flags->l && was_equal) {
      printf("flag_l: %s\n", argv[tmp_optind]);
      was_equal = 0;
    }
    // grep l
    tmp_optind++;
  }
  // printf("B: in get_search\n");
  //  printf("count files: %d\n", count_files);
  // printf("E: in get_search\n");
  free(buf_str);
  regfree(&reg_ptr);
}

void print_str(/*int reg_rez, */ char *buf_str, grep_flags *grep_flags,
               char *file_name) {
  if (!grep_flags->c && !grep_flags->l) {
    // printf("reg_rez: %d finded str: %s", reg_rez, buf_str);
    if (grep_flags->count_files < 2) {
      printf("%s", buf_str);
      // flag n
      if (grep_flags->n) {
        printf("%s", /*str_count++,*/ buf_str);
      }
      // flag n
    } else {
      printf("%s:%s", file_name, buf_str);
    }
  }
}

void set_flags(int argc, char **argv, char *reg_str, char *reg_filename,
               grep_flags *grep_flags) {
  FILE *file = NULL;
  char grep_key = 0;
  int tmp_optind = 0;
  while ((grep_key = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (grep_key) {
      case 'e':
        grep_flags->e = 1;
        stpcpy(reg_str, optarg);
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
        strcpy(reg_filename, optarg);
        break;
      case 'o':
        grep_flags->o = 1;
        break;
      default:
        break;
    }
    tmp_optind = optind;
    // printf("!!!optind: %d key: %c optarg: %s\n", optind, grep_key, optarg);
  }

  while (tmp_optind < argc) {
    if ((file = fopen(argv[tmp_optind], "r")) != NULL) {
      grep_flags->count_files++;
    }
    tmp_optind++;
  }
  // printf("B: in set_flags!!!\n");
  // printf("count_files: %d\n", count_files);
  // printf("E: in set_flags!!!\n");
  if (!grep_flags->e) {
    stpcpy(reg_str, argv[optind]);
  }
}

void show_flags(int argc, char **argv, char *reg_str, char *reg_filename,
                grep_flags *grep_flags) {
  int tmp_optind = optind;
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
  printf("reg_str: %s\n", reg_str);
  printf("reg_filename: %s\n", reg_filename);
  printf("optind: %d\n", optind);
  // code duplication
  if (grep_flags->e) {
    while (tmp_optind < argc) {
      printf("file: %s\n", argv[tmp_optind++]);
    }
  } else {
    while (tmp_optind < argc) {
      printf("file: %s\n", argv[tmp_optind++]);
    }
  }
  // code duplication

  printf("!!!show flag end!!!\n");
}
