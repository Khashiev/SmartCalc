CC = gcc
FLAGS = -Wall -Werror -Wextra
SRC=$(wildcard ./back/*.c)
SRC_TEST=./tests/test.c
GCOV=-fprofile-arcs -ftest-coverage
OS:=$(shell uname)
OBJ=$(patsubst %.c,%.o,$(SRC))

ifeq ($(OS),Linux)
  	OPEN_CMD = xdg-open
	ADD_LIB = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE
endif

ifeq ($(OS),Darwin)
	OPEN_CMD = open
	ADD_LIB = -lcheck -lm
endif

all: install

install:
	mkdir build
	cd build && qmake ../front/Calc && make
	rm -rf build

uninstall:
	rm -rf ~/Calc

dist: install
	tar -czf calc.tar.gz ~/Calc/Calculator
	rm -rf ~/Calc

s21_SmartCalc.a: ${OBJ}
	@ar rcs s21_SmartCalc.a $^
	@ranlib s21_SmartCalc.a

test: clean
	@$(CC) $(FLAGS) $(SRC) $(SRC_TEST) -o tests/test.out $(ADD_LIB) 
	@./tests/test.out

gcov_report:
	@$(CC) $(GCOV) $(SRC) $(SRC_TEST) -o test.out $(ADD_LIB)
	@./test.out
	@lcov -t "test" -o test.info -c -d ./
	@genhtml test.info -o report
	@$(OPEN_CMD) report/index.html

dvi:
	open ./dvi.md

clean:
	@rm -rf back/*.o back/*.a tests/*.out report *.gcno *.gcda *.info *.out

