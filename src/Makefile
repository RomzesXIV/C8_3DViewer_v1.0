CFLAGS = -Wall -Werror -Wextra -std=c11
ARCH = $(shell arch)
ifeq "$(ARCH)" "i386"
MYFLAGS = -lcheck -lpthread -lm  -I /usr/local/include -L/usr/local/lib
endif
ifeq "$(ARCH)" "x86_64"
MYFLAGS = -lcheck -lm -lpthread -lsubunit -g
endif

all: clean test gcov_report

install:
	mkdir build
	#cd build && ~/Qt/6.4.2/macos/bin/qmake ../view/3dviewer && make
	cd build && qmake ../view/3dviewer && make
	rm -rf build

dist: install
	tar -czf 3dviewer.tar.gz ~/Viewer/3dviewer
	rm -rf ~/Viewer

uninstall:
	rm -rf ~/Viewer

test: model/model.c model/model_operations.c model/parser.c model/tests/test.c 
	gcc $^ -o $@ $(CFLAGS) $(MYFLAGS) --coverage

gcov_report: test
	./test
	gcovr --html-details rep.html
	open rep.html

dvi:
	doxygen Doxyfile
	open ../doxygen/html/index.html

check:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -i model/*.c
	clang-format -i model/*.h
	clang-format -i model/tests/*.c
	clang-format -i view/3dviewer/*.cpp
	clang-format -i view/3dviewer/*.h

clean:
	rm -rf *.o *.gcda *.a *.html *.gcno *.css .clang-format build 
	rm -f test
	rm -rf *.tar.gz
	rm -rf view/build-3dviewer-Desktop-Debug
	rm -rf view/build-3dviewer-Desktop_x86_darwin_generic_mach_o_64bit-Debug

rebuild: clean all

git:
	git add model/*.* model/tests/*.* view/3dviewer/*.* Doxyfile Title.md Makefile
	git commit -m "prerelase"
	git push origin develop
