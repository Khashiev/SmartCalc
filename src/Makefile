CC = gcc
FLAGS = -Wall -Werror -Wextra
SRC=$(wildcard ./back/*.c)
SRC_TEST=./tests/test.c
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

# all: install

s21_SmartCalc.a: ${OBJ}
	@ar rcs s21_SmartCalc.a $^
	@ranlib s21_SmartCalc.a

test: clean
	@$(CC) $(FLAGS) $(SRC) $(SRC_TEST) -o tests/test.out $(ADD_LIB)
	@./tests/test.out

clean:
	@rm -rf back/*.o back/*.a tests/*.out 

