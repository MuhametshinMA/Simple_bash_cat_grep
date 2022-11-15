FLAG=-Werror -Wall -Wextra -g
rebuild: clean s21_cat

s21_cat: cat_util.c cat_flags.c
	gcc $(FLAG) cat_util.c cat_flags.c -o s21_cat

test_func_cat: test_func_cat.sh
	sh test_func_cat.sh

test_leak_cat: test_leak_cat.sh
	sh test_leak_cat.sh
clean:
	rm  s21_cat