CXX := g++
CXXFLAGS := `llvm-config --cxxflags` -g
OBJECTS := parser.o tokens.o node.o main.o

all: parser

clean:
	rm parser.cpp parser.hpp parser tokens.cpp *.o

parser: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

tokens.cpp: tokens.l
	lex -o tokens.cpp tokens.l

parser.cpp: parser.y
	bison -d parser.y -o parser.cpp
