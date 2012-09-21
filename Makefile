CXX := g++
CXXFLAGS := -g
OBJECTS := parser.o tokens.o main.o AST/function.o AST/node.o AST/context.o AST/integer.o AST/double.o AST/atom.o AST/list.o

all: parser

clean:
	rm parser.cpp parser.hpp parser tokens.cpp *.o AST/*.o

parser: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

AST/%.o: AST/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

tokens.cpp: tokens.l
	lex -o tokens.cpp tokens.l

parser.cpp: parser.y
	bison -d parser.y -o parser.cpp
