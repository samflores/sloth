#include "node.hpp"

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

NNumber *NDouble::times(NNumber *other) {
  double _ovalue = ((NDouble*)other)->_value;
  return new NDouble(_value * _ovalue);
}

NNumber *NDouble::divide(NNumber *other) {
  double _ovalue = ((NDouble*)other)->_value;
  return new NDouble(_value / _ovalue);
}

std::string NDouble::toString() {
  char buffer[20];
  sprintf(buffer, "%f", _value);
  return *new std::string(buffer, strlen(buffer));
}

