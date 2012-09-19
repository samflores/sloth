CXX := g++
CXXFLAGS := `llvm-config --cxxflags`
OBJECTS := tokens.o parser.o node.o main.o

parser: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

tokens.cpp: tokens.l
	lex -o tokens.cpp tokens.l

parser.cpp: parser.y
	bison -d parser.y -o parser.cpp
