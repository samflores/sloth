#include <iostream>
#include "node.hpp"

extern int yyparse();

int main(int argc, const char *argv[])
{
  yyparse();
  std::cout << std::endl;
  return 0;
}
