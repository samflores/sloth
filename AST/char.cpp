#include "node.hpp"
#include <sstream>

NChar::NChar(char ch) {
  _value = ch;
}

std::string NChar::toString() {
  std::stringstream str;
  str << "\\" << _value;
  return str.str();
}

Node *NChar::eval() {
  return this;
}
