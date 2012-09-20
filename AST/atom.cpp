#include "node.hpp"

extern Context *context;

NAtom::NAtom(const std::string& str) {
  _name = str;
}

Node *NAtom::eval() {
  Node *value = context->getValue(this);
  if (value != NULL)
    return value;
  return this;
}

std::string NAtom::toString() {
  return _name;
}
