#include "node.hpp"

NList::NList() {
  _car = NULL;
  _cdr = NULL;
}

NList::NList(Node *car) {
  _car = car;
  _cdr = NULL;
}

NList::NList(Node *car, Node *cdr) {
  _car = car;
  _cdr = cdr;
}

Node *NList::eval() {
  Node *car = _car == NULL ? NULL : _car->eval();
  Node *cdr = _cdr == NULL ? NULL : _cdr->eval();
  if (car != NULL && car->isFunction() == 1) {
    return ((NFunction*)car)->apply((NList*)cdr);
  }
  return new NList( car, cdr );
}

std::string NList::toString() {
  std::string str = "(";
  if (_car != NULL)
    str.append(_car->toString());
  str.append(" ");
  str.append(_cdr == NULL ? "#" : _cdr->toString());
  str.append(")");
  return str;
}

