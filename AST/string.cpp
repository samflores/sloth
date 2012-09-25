#include "node.hpp"
#include <sstream>

Node *NString::eval() {
  return this;
}

std::string NString::toString() {
  std::stringstream str;
  str << "\"";
  str << toString(this);
  str << "\"";
  return str.str();
}

std::string NString::toString(NList *list) {
  std::stringstream str;
  str << list->car()->toString().c_str()[1];
  if (list->cdr() != NULL)
    str << toString((NList*)list->cdr());
  return str.str();
}
