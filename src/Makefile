CC = g++
FLAGS = -Wall -Werror -Wextra --std=c++17 # -g -fsanitize=address
FLAGS_COV = -lgtest -pthread -lgcov -fprofile-arcs -ftest-coverage

all: install

.PHONY: install
install:
	cd ../build && cmake ../src/rendering/. && make
	../build/GLWidget

.PHONY: uninstall
uninstall:
	rm -fr ../build/*

.PHONY: gcov_report
gcov_report: test
	gcc -o test s21_3DViever.a ./backend/parser.c ./tests/s21_3DViever_test.c $(FLAG_COV)
	./test
	lcov -t "gcov_report" -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info
	open ./report/index.html
	rm -fr s21_3DViever.a test *.gcda *.gcno gcov_report.info

.PHONY: test
test: s21_3DViever.a
	$(CC) $(FLAGS) s21_3DViever.a tests/s21_3DViever_test.cc -o test $(FLAGS_COV)
	./test

.PHONY: s21_3DViever.a
s21_3DViever.a: o_files
	ar rcs s21_3DViever.a parser.o
	ranlib s21_3DViever.a

.PHONY: o_files
o_files:
	$(CC) $(FLAGS)  -c ./backend/parser.cc -o parser.o

.PHONY: clean
clean: uninstall
	rm -fr *.o s21_3DViever.a test *.gcda *.gcno gcov_report.info ./report