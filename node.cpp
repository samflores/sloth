#include "node.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *core_plus(NList *list) {
  NNumber *a = (NNumber *)list->car();
  NNumber *b = (NNumber *)((NList *)list->cdr())->car();
  return a->plus(b);
}

NAtom::NAtom(const std::string& str) {
  _name = str;
}

Node *NAtom::eval() {
#ifdef __DEBUG
  std::cout << "a=> " << toString() << std::endl;
#endif
  if (_name == "+")
    return new NFunction(this, core_plus);
  return this;
}

std::string NAtom::toString() {
  return _name;
}

NFunction::NFunction(NAtom *atom, Node * (*body)(NList *) ){
  _atom = atom;
  _body = body;
}

std::string NFunction::toString() {
  return "f" + name();
}

Node *NFunction::apply(NList *list) {
#ifdef __DEBUG
  std::cout << "foo" << std::endl;
#endif
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
#ifdef __DEBUG
  std::cout << "l=> " << toString() << std::endl;
#endif
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
#ifdef __DEBUG
  std::cout << "n=> " << toString() << std::endl;
#endif
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

std::string NDouble::toString() {
  char buffer[20];
  sprintf(buffer, "%f", _value);
  return *new std::string(buffer, strlen(buffer));
}

NOctal::NOctal(const char *str) : NInteger() {}

NHexadecimal::NHexadecimal(const char *str) : NInteger() {}

NBinary::NBinary(const char *str) : NInteger() {}
