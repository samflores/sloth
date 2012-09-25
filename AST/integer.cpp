#include "node.hpp"
#include <sstream>

char *cleanup(const char *str) {
  int len = strlen(str);
  char *clean = (char*)malloc(sizeof(char) * (len+1));
  const char* ptr;
  char *dst;
  for (ptr = str, dst = clean; ptr < str + len; ptr++) {
    if (*ptr != ',')
      memset(dst++, *ptr, 1);
  }
  return clean;
}

NInteger::NInteger() {
  _value = 0;
}

NInteger::NInteger(const char *str) {
  _value = atol(cleanup(str));
}

NInteger::NInteger(long l) {
  _value = l;
}

NOctal::NOctal(const char *str) {
  std::stringstream stream;
  stream << std::string(cleanup(str)).substr(2);
  stream >> std::oct >> _value;
}

NHexadecimal::NHexadecimal(const char *str) {
  std::stringstream stream;
  stream << cleanup(str);
  stream >> std::hex >> _value;
}

NBinary::NBinary(const char *str) {
  int bin = atol(std::string(cleanup(str)).substr(2).c_str());
  int dec = 0;

  int m = 1;

  while(bin > 0) {
    if(bin % 10 == 1)
      dec += m;
    bin /= 10;
    m <<= 1;
  }
  _value = dec;
}

NNumber *NInteger::plus(NNumber *other) {
  long _ovalue = ((NInteger*)other)->_value;
  return new NInteger(_value + _ovalue);
}

NNumber *NInteger::minus(NNumber *other) {
  long _ovalue = ((NInteger*)other)->_value;
  return new NInteger(_value - _ovalue);
}

NNumber *NInteger::times(NNumber *other) {
  long _ovalue = ((NInteger*)other)->_value;
  return new NInteger(_value * _ovalue);
}

NNumber *NInteger::divide(NNumber *other) {
  long _ovalue = ((NInteger*)other)->_value;
  return new NInteger(_value / _ovalue);
}

std::string NInteger::toString() {
  char buffer[20];
  sprintf(buffer, "%ld", _value);
  return *new std::string(buffer, strlen(buffer));
}

