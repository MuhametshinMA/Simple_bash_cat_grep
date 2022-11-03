#include "grep_flags.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

void set_flags(int argc, char **argv, char *reg_str, grep_flags *grep_flags) {
  char grep_key = 0;
  while ((grep_key = getopt(argc, argv, "e:ivclnhsfo")) != -1) {
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
        break;
      case 'o':
        grep_flags->o = 1;
        break;
      default:
        break;
    }
  }
}

void show_flags(int argc, char **argv, char *reg_str, grep_flags *grep_flags) {
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
  printf("optarg: %s\n", reg_str);
  printf("optind: %d\n", optind);

  while (optind < argc) {
    printf("file: %s\n", argv[optind++]);
  }
}
