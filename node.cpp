#include "node.hpp"

NAtom::NAtom(const std::string& str) {
  _name = str;
  std::cout << _name << std::endl;
}

std::string NAtom::toString() {
  return _name;
}

NList::NList() {
  _car = NULL;
  _cdr = NULL;
  std::cout << toString() << std::endl;
}

NList::NList(Node *car) {
  _car = car;
  _cdr = new NList();
  std::cout << toString() << std::endl;
}

NList::NList(Node *car, Node *cdr) {
  _car = car;
  _cdr = cdr;
  std::cout << toString() << std::endl;
}

std::string NList::toString() {
  std::string str = className();
  str.append("(");
  if (_car != NULL)
    str.append(_car->toString());
  str.append(" ");
  if (_cdr != NULL)
    str.append(_cdr->toString());
  str.append(")");
  return str;
}

NInteger::NInteger() {
  _value = 0;
  std::cout << toString() << std::endl;
}

NInteger::NInteger(const char *str) {
  _value = atol(str);
  std::cout << toString() << std::endl;
}

std::string NInteger::toString() {
  char buffer[20];
  sprintf(buffer, "%ld", _value);
  return className().append(*new std::string(buffer, strlen(buffer)));
}

NDouble::NDouble() {
  _value = 0;
  // printf("%f\n", _value);
}

NDouble::NDouble(const char *str) {
  _value = atof(str);
  // printf("%f\n", _value);
}

std::string NDouble::toString() {
  char buffer[20];
  sprintf(buffer, "%f", _value);
  return *new std::string(buffer, strlen(buffer));
}

NOctal::NOctal(const char *str) : NInteger() {}

NHexadecimal::NHexadecimal(const char *str) : NInteger() {}

NBinary::NBinary(const char *str) : NInteger() {}
