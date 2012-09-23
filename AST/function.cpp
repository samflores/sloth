#include "node.hpp"

extern Context *context;

NFunction::NFunction(Context *context, Node * (*body)(NList *, Context *) ){
  _context = context;
  _body = body;
}

NFunction::NFunction(Node * (*body)(NList *, Context *) ) {
  _context = context;
  _body = body;
}

std::string NFunction::toString() {
  return "f";
}

Node *NFunction::apply(NList *list) {
  return _body(list, _context);
}

