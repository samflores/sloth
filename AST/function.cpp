#include "node.hpp"

extern NContext *context;

NFunction::NFunction(NContext *context, Node * (*body)(NList *, NContext *) ){
  _context = context;
  _body = body;
}

NFunction::NFunction(Node * (*body)(NList *, NContext *) ) {
  _context = context;
  _body = body;
}

std::string NFunction::toString() {
  return "f";
}

Node *NFunction::apply(NList *list) {
  return _body(list, _context);
}

