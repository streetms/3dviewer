FLAGS		=-Wall -Werror -Wextra -std=c11 -g
LIBS = -lcheck -lm
TEST_SOURCE := $(shell find ./tests  -iname "*.c" )

OS :=$(shell uname -s)
ifeq ($(OS), Darwin)
	LEAKS =leaks -atExit -- 
else
	LEAKS =valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --leak-resolution=med
	#LIBS += -lsubunit
endif

.PHONY: test s21_matrix.a gcov_report

test: s21_matrix.a
	gcc $(GCOV) ${TEST_SOURCE} $(CFLAGS_TEST) $(LIBS) s21_matrix.a -o $@.out

all: clean test

s21_matrix.a: s21_matrix.c
	gcc $(FLAGS) -c $^ -lm
	ar rc $@ s21*.o
	rm -rf s21*.o
	ranlib $@

gcov_report: 
	make gcov GCOV="--coverage"

gcov: test
	rm -rf report
	# ./$< || true
	lcov -t "$@" -o $@.info -c -d .
	$(GCOV_INFO_FILTER_MATCH)
	genhtml -o report $@.info
	# rm -rf *.gcno *.gcna *.gcda $@.info $@ file_gcno $<
	open report/index.html

main: s21_matrix.a
	gcc -g s21_test.c main.c $< -o $@.out
	./$@.out | tee $@.log

leaks: test
	$(LEAKS) ./$<.out

style_fix:
	clang-format -i *.c *.h tests/*

style:
	clang-format -n *.c *.h tests/*




clean:
	rm -rf test/*.txt
	rm -rf *.out
	rm -rf *.gcno *.gcna *.gcda *.info report gcov_report file_gcno
	rm -rf *.dSYM
	rm -rf *.log
	rm -rf *.a
