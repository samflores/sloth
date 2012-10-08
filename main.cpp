#include <iostream>
#include "AST/node.hpp"

extern int yyparse();
extern NContext *context;

int main(int argc, const char *argv[])
{
  context = new NContext();
  yyparse();
  context->eval();
  return 0;
}
