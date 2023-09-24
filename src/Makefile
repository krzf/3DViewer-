CC = gcc
CFLAG = -Wall -Wextra -Werror -std=c11
APP = 3DViewer_V1_0.app
BACKEND_FILES = parser.c affine.c
BACKEND_FILES_O = parser.o affine.o
VALGRIND_FLAGS=--leak-check=full
VALGRIND_FLAGS_v2 = --log-file="valgrind.txt" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med
LINUX_FLAGS=-lcheck -lsubunit -lrt -lpthread
MAC_FLAGS=-lcheck -lm
OS := $(shell uname -s)


GCOVFLAGS = -L. --coverage
TEST_FLAGS = -lcheck

ifeq ($(shell uname), Linux)
	TEST_FLAGS += -lpthread -lrt -lsubunit -lm
endif


all: check-style install gcov_report

build:
	mkdir build
	cd ./build/ && qmake ../QT && make 

install: build
	@-cp -rf build/$(APP) $(HOME)/Desktop/
	# make clean

uninstall:
	@rm -rf $(HOME)/Desktop/$(APP)

dvi:
	open readme.html

dist:
	rm -rf Distribut_3DViewer_v1.0
	mkdir Distribut_3DViewer_v1.0
	rsync -av --exclude='Distribut_3DViewer_v1.0' ../src Distribut_3DViewer_v1.0 
	tar cvzf Distribut_3DViewer_v1.0.tgz Distribut_3DViewer_v1.0/
	mv Distribut_3DViewer_v1.0.tgz $(HOME)/Desktop/
	rm -rf Distribut_3DViewer_v1.0/

3dview.a:
	$(CC) $(CFLAG) $(BACKEND_FILES) -c
	# $(CC) $(CFLAG)
	ar r 3dview.a $(BACKEND_FILES_O)
	rm *.o

test: 3dview.a unzip
	$(CC) $(CFLAG) check.c 3dview.a $(TEST_FLAGS) -o test
	./test

	
check-style:
	cp -R ../materials/linters/.clang-format .
	clang-format -n -style=google *.c QT/ima/giflib/*.c
	clang-format -n -style=google QT/*.cpp QT/ima/*.cpp
	clang-format -n -style=google *.h QT/*.h QT/ima/*.h QT/ima/giflib/*.h
	rm .clang-format

	
style:
	cp -R ../materials/linters/.clang-format .
	clang-format -i -style=google *.c QT/ima/giflib/*.c
	clang-format -i -style=google QT/*.cpp QT/ima/*.cpp
	clang-format -i -style=google *.h QT/*.h QT/ima/*.h QT/ima/giflib/*.h
	rm .clang-format


gcov_report: 3dview.a test
	$(CC) $(CFLAG) -w check.c $(BACKEND_FILES) 3dview.a $(TEST_FLAGS) $(GCOVFLAGS) -o test
	./test
	lcov -t tests.c -o test.info -c -d .
	genhtml -o test_html test.info
	open ./test_html/index.html


memory_check: 3dview.a
ifeq ($(OS),Linux)
	$(CC) $(FLAGS) check.c $< -o memory_test $(LINUX_FLAGS) -lm
	CK_FORK=no valgrind $(VALGRIND_FLAGS) ./memory_test
endif
ifeq ($(OS),Darwin)
	$(CC) $(FLAGS) check.c $< -o memory_test $(MAC_FLAGS)
	leaks --atExit -- ./memory_test      
endif

unzip:
	unzip obj.zip
	rm -rf __MACOSX

clean:
	rm -rf *.o *.a
	rm -rf *.gcda *.gcno *.info
	rm -rf test report
	rm -rf 3dview test
	rm -rf ./build*
	rm -rf ../build
	rm -rf test
	rm -rf test_html
	rm -rf QT/*.pro.user
	rm -rf obj



rebuild: clean all
