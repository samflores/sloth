#include "node.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern Context *context;

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
  if (function != NULL) {
    return NULL;
  } else {
    function = new NFunction(body);
    _values[atom] = function;
    return function;
  }
}

Node *Context::getValue(NAtom *atom) {
  return _values[atom];
}

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

NFunction::NFunction(Node * (*body)(NList *) ){
  _body = body;
}

std::string NFunction::toString() {
  return "f" + name();
}

Node *NFunction::apply(NList *list) {
  return _body(list);
}

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
  Node *car = _car->eval();
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

Node *NNumber::eval() {
  return this;
}

NInteger::NInteger() {
  _value = 0;
}

NInteger::NInteger(const char *str) {
  _value = atol(str);
}

NInteger::NInteger(long l) {
  _value = l;
}

NNumber *NInteger::plus(NNumber *other) {
  long _ovalue = ((NInteger*)other)->_value;
  return new NInteger(_value + _ovalue);
}

NNumber *NInteger::minus(NNumber *other) {
  long _ovalue = ((NInteger*)other)->_value;
  return new NInteger(_value - _ovalue);
}

std::string NInteger::toString() {
  char buffer[20];
  sprintf(buffer, "%ld", _value);
  return *new std::string(buffer, strlen(buffer));
}

NDouble::NDouble() {
  _value = 0;
}

NDouble::NDouble(const char *str) {
  _value = atof(str);
}

NDouble::NDouble(double d) {
  _value = d;
}

NNumber *NDouble::plus(NNumber *other) {
  double _ovalue = ((NDouble*)other)->_value;
  return new NDouble(_value + _ovalue);
}

NNumber *NDouble::minus(NNumber *other) {
  double _ovalue = ((NDouble*)other)->_value;
  return new NDouble(_value - _ovalue);
}

std::string NDouble::toString() {
  char buffer[20];
  sprintf(buffer, "%f", _value);
  return *new std::string(buffer, strlen(buffer));
}

NOctal::NOctal(const char *str) : NInteger() {}

NHexadecimal::NHexadecimal(const char *str) : NInteger() {}

NBinary::NBinary(const char *str) : NInteger() {}
