GCC = gcc # g++
W_FLAGS = -Wall -Werror -Wextra -Wfloat-equal \
-pedantic -Wimplicit-fallthrough -Wshadow -Wformat=2 \
-Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align \
-D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2\
-fsanitize=undefined -fno-sanitize-recover -fstack-protector\

# flag -O2 for gcov Func % 
# flag -fsanitize=address not for memcheck
GCCFLAGS = -std=c++17 $(W_FLAGS) -lstdc++ 
# CHFLAGS = -lstdc++ -lgtest -lm -std=c++17

# Linker flags (mostly -L)
LDFLAGS = -pthread
LIBS = -lrt -lm
LGENERAL = -lgtest -lcheck -lgcov
LIBTESTADD = -fprofile-arcs -ftest-coverage

# print or not some lines
ifeq ($(V),1)
	Q =
else
	Q = @
endif

NAME = s21_matrix_oop
NAME_TEST = $(NAME)_test
SOURCE = $(wildcard s21_*.cc)
realpath := $(shell pwd)
Yellow_ = \033[0;33m
Green__ = \033[0;32m
Blue___ = \033[0;34m
NoColor = \033[0m
MAKE = make

OS := $(shell uname)
ifeq ($(OS),Linux) # определяем ОС
	LIBS_TEST = $(LGENERAL) -pthread $(LIBS) -lsubunit $(LIBTESTADD)
	MEM_CHECK = valgrind --track-origins=yes --leak-check=full --leak-resolution=med -s
else
	LIBS_TEST = $(LGENERAL) -coverage
	MEM_CHECK = leaks --atExit --
endif

.PHONY: all clean test

all: clean memcheck gcov_report check_style

clear: clean

clean:
	@rm -rf *.out *.gcda *.gcno *.a *.info *.o $(NAME).dSYM test report

$(NAME).a: $(SOURCE)
	$(Q) $(GCC) $(GCCFLAGS) -c $(SOURCE) $(LIBS_TEST)
	$(Q) ar rcs $(NAME).a *.o
	$(Q) ranlib $(NAME).a


create_test:
ifeq ("$(wildcard test)","")
	$(Q) echo "${NoColor}"
	$(Q) $(MAKE) --no-print-directory $(NAME).a
	$(Q) $(GCC) $(GCCFLAGS) $(NAME_TEST).cc $(NAME).a -o test $(LIBS_TEST)
	$(Q) echo "${Green__}File 'test' created${NoColor}"
else
	@echo "${Yellow_}File 'test' has already been created ${NoColor}"
endif

tests: test

test:
	$(MAKE)  --no-print-directory clean
	$(MAKE)  --no-print-directory create_test
	./test

gcov_report:
	$(Q) echo "${Blue___}  === COVERAGE CHECK ==="
	$(Q) $(MAKE)  --no-print-directory create_test
	$(Q) echo "${Blue___}"
	./test
	$(Q) echo "${Blue___}"
	$(Q) lcov -t "test" -o test.info -c -d .
	$(Q) genhtml -o report test.info
	$(Q) open ./report$(realpath)/index.html
	$(Q) echo "${NoColor}"

style:
	find . \( -name '*.h' -o -name '*.cc' \) -print0 | xargs -0 clang-format -i -style=Google
	clang-format -i *.cc -style=Google
	clang-format -i *.h -style=Google

check_style:
	@echo "${Green__}"
	find . \( -name '*.h' -o -name '*.cc' \) -print0 | xargs -0 clang-format -n -style=Google
	clang-format -n *.cc -style=Google
	clang-format -n *.h -style=Google

memcheck:
	$(Q) echo "${Yellow_} === MEMORY CHECK ==="
	$(Q) $(MAKE) --no-print-directory create_test
	$(Q) echo "${Yellow_}"
	$(Q) $(MEM_CHECK) ./test
	$(Q) echo "${Yellow_}"
