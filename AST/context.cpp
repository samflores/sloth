#include "node.hpp"

Node *core_plus(NList *list, NContext *context) {
  NNumber *a = (NNumber *)list->car();
  NNumber *b = (NNumber *)((NList *)list->cdr())->car();
  return a->plus(b);
}

Node *core_minus(NList *list, NContext *context) {
  NNumber *a = (NNumber *)list->car();
  NNumber *b = (NNumber *)((NList *)list->cdr())->car();
  return a->minus(b);
}

Node *core_times(NList *list, NContext *context) {
  NNumber *a = (NNumber *)list->car();
  NNumber *b = (NNumber *)((NList *)list->cdr())->car();
  return a->times(b);
}

Node *core_divide(NList *list, NContext *context) {
  NNumber *a = (NNumber *)list->car();
  NNumber *b = (NNumber *)((NList *)list->cdr())->car();
  return a->divide(b);
}

Node *core_define(NList *list, NContext *context) {
  NAtom *atom = (NAtom *)list->car();
  Node *value = ((NList *)list->cdr())->car();
  context->defineValue(atom, value);
  return value;
}

Node *core_print(NList *list, NContext *context) {
  NAtom *value = (NAtom *)list->car();
  std::cout << value->toString() << std::endl;
  return NULL;
}

NContext::NContext(Node *node, NContext *parent) {
  _parent = parent;
  _node = node;
  defineCoreFunction("+", core_plus);
  defineCoreFunction("-", core_minus);
  defineCoreFunction("*", core_times);
  defineCoreFunction("/", core_divide);
  defineCoreFunction("def", core_define);
  defineCoreFunction("print", core_print);
}

Node *NContext::eval() {
  return _node->eval();
}

NAtom *NContext::getAtom(std::string& name) {
  NAtom *atom = _atoms[name];
  if (atom == NULL && _parent != NULL)
    atom = _parent->getAtom(name);
  return atom;
}

NAtom *NContext::getOrCreateAtom(std::string& name) {
  NAtom *atom = getAtom(name);
  if (atom == NULL) {
    atom = new NAtom(name);
    _atoms[name] = atom;
  }
  return atom;
}

NFunction *NContext::defineCoreFunction(std::string name, Node *(*body)(NList *, NContext *)) {
  return defineFunction(getOrCreateAtom(name), body);
}

NFunction *NContext::defineFunction(NAtom *atom, Node *(*body)(NList *, NContext *)) {
  NFunction *function = (NFunction *)_values[atom];
  if (function == NULL) {
    function = new NFunction(this, body);
    _values[atom] = function;
  }
  return function;
}

Node *NContext::getValue(NAtom *atom) {
  return _values[atom];
}

Node *NContext::defineValue(NAtom *atom, Node *value) {
  _values[atom] = value;
  return value;
}
