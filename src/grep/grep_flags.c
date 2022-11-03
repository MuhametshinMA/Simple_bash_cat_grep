#include "grep_flags.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void get_search_res(int argc, char **argv, char *reg_str, char *reg_filename) {
  printf("!!in getsearch: file!!\n");
  int tmp_optind = optind;
  FILE *file = NULL;
  regex_t reg_ptr;

  int chars = 0;
  size_t buf_size = 256;
  char *buf_str;
  buf_str = (char *)malloc(buf_size * sizeof(char));

  int reg_rez = 0;
  size_t n_match = 1;
  regmatch_t p_match[2];

  printf("reg_str: %s\n", reg_str);
  printf("reg_filename: %s\n", reg_filename);
  printf("argc: %d; optind: %d\n", argc, tmp_optind);
  while (tmp_optind < argc) {
    printf("optind: %d\n", tmp_optind);
    printf("file: %s\n", argv[tmp_optind]);
    if ((file = fopen(argv[tmp_optind], "r")) != NULL) {
      // printf("file: %s; reg_str: %s\n", argv[tmp_optind], reg_str);
      while ((chars = getline(&buf_str, &buf_size, file)) != -1) {
        printf("  %d   %s", chars, buf_str);
        // regex
        if (regcomp(&reg_ptr, reg_str, 0) == 0) {
          if ((reg_rez = regexec(&reg_ptr, buf_str, n_match, p_match, 0)) ==
              0) {
            // printf(
            //     "With the whole expression, a matched substring \"%lld\" is "
            //     "found at position %d to %d.\n",
            //     p_match[0].rm_eo - p_match[0].rm_so,
            //     &buf_str[p_match[0].rm_so], p_match[0].rm_so,
            //     p_match[0].rm_eo - 1);
            // printf(
            //     "With the sub-expression, "
            //     "a matched substring \"%.*s\" is found at position %d to
            //     %d.\n", p_match[1].rm_eo - p_match[1].rm_so,
            //     &buf_str[p_match[1].rm_so], p_match[1].rm_so,
            //     p_match[1].rm_eo - 1);
            printf("1");
          }
        }
        // regex
      }
    }

    tmp_optind++;
  }
  free(buf_str);
  regfree(&reg_ptr);
  printf("!!END: in getsearch: file!!\n");
}

void set_flags(int argc, char **argv, char *reg_str, char *reg_filename,
               grep_flags *grep_flags) {
  char grep_key = 0;
  while ((grep_key = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    printf("grep_key: %d, ", grep_key);
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

  while (tmp_optind < argc) {
    printf("file: %s\n", argv[tmp_optind++]);
  }
  printf("!!!show flag end!!!\n");
}
