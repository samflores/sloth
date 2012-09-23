#include "node.hpp"

Node *core_plus(NList *list, Context *context) {
  NNumber *a = (NNumber *)list->car();
  NNumber *b = (NNumber *)((NList *)list->cdr())->car();
  return a->plus(b);
}

Node *core_minus(NList *list, Context *context) {
  NNumber *a = (NNumber *)list->car();
  NNumber *b = (NNumber *)((NList *)list->cdr())->car();
  return a->minus(b);
}

Node *core_define(NList *list, Context *context) {
  NAtom *atom = (NAtom *)list->car();
  Node *value = ((NList *)list->cdr())->car();
  context->defineValue(atom, value);
  return value;
}

Context::Context() {
  defineCoreFunction("+", core_plus);
  defineCoreFunction("-", core_minus);
  defineCoreFunction("def", core_define);
}

NAtom *Context::getAtom(std::string& name) {
  NAtom *atom = _atoms[name];
  if (atom == NULL) {
    atom = new NAtom(name);
    _atoms[name] = atom;
  }
  return atom;
}

NFunction *Context::defineCoreFunction(std::string name, Node *(*body)(NList *, Context *)) {
  return defineFunction(getAtom(name), body);
}

NFunction *Context::defineFunction(NAtom *atom, Node *(*body)(NList *, Context *)) {
  NFunction *function = (NFunction *)_values[atom];
  if (function == NULL) {
    function = new NFunction(this, body);
    _values[atom] = function;
  }
  return function;
}

Node *Context::getValue(NAtom *atom) {
  return _values[atom];
}

void Context::defineValue(NAtom *atom, Node *value) {
  _values[atom] = value;
}
