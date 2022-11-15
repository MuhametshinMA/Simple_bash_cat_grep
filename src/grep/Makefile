FLAG=-Werror -Wall -Wextra -g
rebuild: clean s21_grep

s21_grep: grep_util.c grep_flags.c
	gcc $(FLAG) grep_util.c grep_flags.c -o s21_grep

test_f: test_func_grep.sh
	sh test_func_grep.sh

test_l: test_leak_grep.sh
	sh test_leak_grep.sh
clean:
	rm  s21_grep