CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov
TEST_FLAGS = -lcheck
LIB_FLAGS = -lncurses

OBJ_DIR = obj
INSTALL_DIR = build
DIST_DIR = maze
TEST_DIR = tests

SOURCES = $(wildcard *.c)
TESTS = $(wildcard $(TEST_DIR)/*.c)
OBJECTS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SOURCES))
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TESTS))

TARGET = maze

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

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

install: uninstall $(OBJECTS) | $(INSTALL_DIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(INSTALL_DIR)/$(TARGET) $(LIB_FLAGS)

uninstall:
	@rm -rf $(INSTALL_DIR)
	
run:
	./$(INSTALL_DIR)/$(TARGET)

# test: build
# 	./$(TARGET)

# build: $(LIB) $(TEST_OBJECTS)
# 	$(CC) $(CFLAGS) $(TEST_OBJECTS) $(LIB) -o $(TARGET) $(TEST_FLAGS)
	
-include $(OBJECTS:.o=.d)
#-include $(TEST_OBJECTS:.o=.d)

$(OBJ_DIR)/%.d: %.cc | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -MM -MT $(@:.d=.o) $< > $@

#$(OBJ_DIR)/%.d: $(TEST_DIR)/%.cc | $(OBJ_DIR)
#	@$(CC) $(CFLAGS) -MM -MT $(@:.d=.o) $< > $@
	
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(INSTALL_DIR):
	@mkdir -p $(INSTALL_DIR)

#fsan: CFLAGS += -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable
#fsan: test

gcov_report:
	$(CC) $(GCOV_FLAGS) $(TESTS) $(SOURCES_LIB) -o report.out $(TEST_FLAGS) $(LIB_FLAGS)
	./report.out
	lcov -t "gcov_report" -o coverage.info -c -d .
	lcov --remove coverage.info '*/$(TEST_DIR)/*' -o coverage.info
	genhtml -o ./report coverage.info
	rm -f *.gcno *.gcda *.info *.gcov *.out
	open ./report/index.html

clean: clean_ds
	@rm -f *.o *.a *.out *.gcno *.gcda $(TARGET)
	@rm -rf report $(OBJ_DIR) $(INSTALL_DIR)
	
clean_obj:
	@rm -rf $(OBJ_DIR)
	
clean_ds:
	@cd .. && find . -name ".DS_Store" -type f -delete

rebuild: clean all

clang:
	$(CLANG) $(SOURCES) $(TESTS) *.h

leaks: install
	$(LEAKS) ./$(TARGET)
