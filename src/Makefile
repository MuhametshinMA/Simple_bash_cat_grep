FLAG=-Werror -Wall -Wextra
all: 21_grep

21_cat: cat/cat_util.c cat/cat_flags.c
	gcc $(FLAG) cat/cat_util.c cat/cat_flags.c -o cat/s21_cat

21_grep: grep/grep_util.c grep/grep_flags.c
	gcc $(FLAG) grep/grep_util.c grep/grep_flags.c -o grep/s21_grep

clean:
	rm cat/s21_cat grep/s21_grep