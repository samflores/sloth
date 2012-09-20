#include "node.hpp"

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

