CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov
TEST_FLAGS = -lcheck
LIB_FLAGS = -lncurses

OBJ_DIR = obj
INSTALL_DIR = build
TEST_DIR = tests
SRC_DIRS = maze cave gui common io
OBJ_SUBDIRS = $(foreach dir, $(SRC_DIRS), $(OBJ_DIR)/$(dir))
DIST_DIRS = $(SRC_DIRS) tests

SOURCES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
SRC_OBJECTS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SOURCES))
DEPENDS = $(patsubst %.c, $(OBJ_DIR)/%.d, $(SOURCES))
TESTS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJECTS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(TESTS))
MAIN = main.c
MAIN_OBJECT = $(patsubst %.c, $(OBJ_DIR)/%.o, $(MAIN))

TARGET = program
TEST_TARGET = $(TEST_DIR)/maze_test

CLANG = clang-format -i

ifeq ($(OS), Windows_NT)
	SYSTEM := Windows
else
    SYSTEM := $(shell uname -s)
endif
ifeq ($(SYSTEM), Linux)
	TEST_FLAGS += -lsubunit -lrt -lm
	OPEN = xdg-open
	LEAKS = valgrind --tool=memcheck --leak-check=yes
endif
ifeq ($(SYSTEM), Darwin)
	OPEN = open
	LEAKS = leaks --atExit --
endif

all: install
	
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPENDS)

$(OBJ_DIR)/%.d: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -MM -MT $(@:.d=.o) $< > $@

install: uninstall $(SRC_OBJECTS) $(MAIN_OBJECT) | $(INSTALL_DIR)
	$(CC) $(CFLAGS) $(SRC_OBJECTS) $(MAIN_OBJECT) -o $(INSTALL_DIR)/$(TARGET) $(LIB_FLAGS)

uninstall:
	@rm -rf $(INSTALL_DIR)
	
run:
	./$(INSTALL_DIR)/$(TARGET)

test: $(SRC_OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $(SRC_OBJECTS) $(TEST_OBJECTS) -o $(TEST_TARGET) $(TEST_FLAGS) $(LIB_FLAGS)
	./$(TEST_TARGET)
	
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_SUBDIRS)
	@mkdir -p $(OBJ_DIR)/$(TEST_DIR)

$(INSTALL_DIR):
	@mkdir -p $(INSTALL_DIR)
	
dist:
	tar -czf maze.tar.gz $(DIST_DIRS) $(MAIN) Makefile

fsan: CFLAGS += -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable
fsan: test

gcov_report:
	$(CC) $(GCOV_FLAGS) $(TESTS) $(SOURCES) -o report.out $(TEST_FLAGS) $(LIB_FLAGS)
	./report.out
	lcov -t "gcov_report" -o coverage.info -c -d .
	lcov --remove coverage.info '*/$(TEST_DIR)/*' '*/common/*' '*/gui/*' '*/io/*' -o coverage.info
	genhtml -o ./report coverage.info
	rm -f *.gcno *.gcda *.info *.gcov *.out
	open ./report/index.html

clean: clean_ds
	@rm -f *.o *.a *.out *.gcno *.gcda *.tar.gz $(TARGET) $(TEST_TARGET)
	@rm -rf report $(OBJ_DIR) $(INSTALL_DIR)
	@rm -f generated_maze.txt maze_solution.txt
	
clean_obj:
	@rm -rf $(OBJ_DIR)
	
clean_ds:
	@cd .. && find . -name ".DS_Store" -type f -delete

rebuild: clean all

clang:
	$(CLANG) */*.c *.c */*.h 

leaks: install
	$(LEAKS) ./$(TARGET)
