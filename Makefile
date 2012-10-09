CXX := g++
CXXFLAGS := -g
OBJECTS := parser.o tokens.o AST/function.o AST/context.o AST/integer.o AST/double.o AST/atom.o AST/list.o AST/string.o AST/char.o

GTEST_DIR = lib/gtest-1.6.0
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

TEST_INC := -I $(GTEST_DIR)/include
TEST_LIB := -lpthread
TEST_FLAGS := $(CXXFLAGS) $(TEST_INC) $(TEST_LIB_DIR) $(TEST_LIB)
TEST_SOURCES := spec/atom.cpp
TEST_BINARY := spec/sloth_test

all: parser

clean: clean-gen clean-objects clean-test

clean-gen:
	rm -f parser.cpp parser.hpp parser tokens.cpp

clean-objects:
	rm -f $(OBJECTS) main.o

clean-test:
	rm -f $(TEST_BINARY) lib/*.o

lib_dir:
	test -d lib || mkdir lib

lib/gtest-all.o : $(GTEST_SRCS_) lib_dir
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) -I$(GTEST_DIR)/include $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc -o $@

lib/gtest_main.o : $(GTEST_SRCS_) lib_dir
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) -I$(GTEST_DIR)/include $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc -o $@

lib/gtest_main.a: lib/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

lib/gtest.a: lib/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

test: parser $(TEST_SOURCES) lib/gtest.a lib/gtest_main.a
	$(CXX) $(TEST_FLAGS) -I. $(TEST_SOURCES) $(OBJECTS) lib/gtest.a lib/gtest_main.a -o $(TEST_BINARY)
	$(TEST_BINARY)

parser: $(OBJECTS) main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

AST/%.o: AST/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

tokens.cpp: tokens.l
	lex -o tokens.cpp tokens.l

parser.cpp: parser.y
	bison -d parser.y -o parser.cpp
