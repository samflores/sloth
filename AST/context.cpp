#include "node.hpp"

Node *core_plus(NList *list) {
  NNumber *a = (NNumber *)list->car();
  NNumber *b = (NNumber *)((NList *)list->cdr())->car();
  return a->plus(b);
}

Node *core_minus(NList *list) {
  NNumber *a = (NNumber *)list->car();
  NNumber *b = (NNumber *)((NList *)list->cdr())->car();
  return a->minus(b);
}

Context::Context() {
  defineCoreFunction("+", core_plus);
  defineCoreFunction("-", core_minus);
}

NAtom *Context::getAtom(std::string name) {
  NAtom *atom = _atoms[name];
  if (atom == NULL) {
    atom = new NAtom(name);
    _atoms[name] = atom;
  }
  return atom;
}

NFunction *Context::defineCoreFunction(std::string name, Node *(*body)(NList *)) {
  return defineFunction(getAtom(name), body);
}

NFunction *Context::defineFunction(NAtom *atom, Node *(*body)(NList *)) {
  NFunction *function = (NFunction *)_values[atom];
  if (function == NULL) {
    function = new NFunction(body);
    _values[atom] = function;
  }
  return function;
}

Node *Context::getValue(NAtom *atom) {
  return _values[atom];
}
