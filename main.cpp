#include <iostream>
#include "AST/node.hpp"

extern int yyparse();
extern Node *mainNode;

int main(int argc, const char *argv[])
{
  yyparse();
  std::cout << mainNode->eval()->toString() << std::endl;
  return 0;
}
