#include "node.hpp"

NFunction::NFunction(Node * (*body)(NList *) ){
  _body = body;
}

std::string NFunction::toString() {
  return "f";
}

Node *NFunction::apply(NList *list) {
  return _body(list);
}

