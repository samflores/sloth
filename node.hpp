#include <iostream>
#include <vector>
#include <llvm/Value.h>

class CodeGenContext;
class Node;
class NAtom;

class NInteger;
class NDouble;
class NBinary;
class NOctal;
class NHexadecimal;

class NList;

class Node {
  public:
    virtual ~Node() {}
    virtual llvm::Value* codeGen(CodeGenContext& context) {}
    virtual std::string toString() {};
    virtual std::string className() {};
};

class NList : public Node {
  Node *_car;
  Node *_cdr;
  public:
    NList();
    NList(Node * car);
    NList(Node * car, Node * cdr);
    std::string toString();
    std::string className() { return "l"; }
};

class NAtom : public Node {
  std::string _name;
  public:
    NAtom(const std::string& str);
    std::string toString();
    std::string className() { return "a"; }
};

class NNumber : public Node {
};

class NInteger : public NNumber {
  long _value;
  public:
    NInteger();
    NInteger(const char *str);
    std::string toString();
    std::string className() { return "i"; }
};

class NDouble : public NNumber {
  float _value;
  public:
    NDouble();
    NDouble(const char *str);
    std::string toString();
};

class NOctal : public NInteger {
  public:
    NOctal(const char *str);
};

class NHexadecimal : public NInteger {
  public:
    NHexadecimal(const char *str);
};

class NBinary : public NInteger {
  public:
    NBinary(const char *str);
};
