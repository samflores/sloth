#include <iostream>
#include <map>

class CodeGenContext;
class Node;
class NAtom;

class NInteger;
class NDouble;
class NBinary;
class NOctal;
class NHexadecimal;

class NList;
class NFunction;
class Context;

class Context {
  public:
    std::map<NAtom *, Node *> values;
};

class Node {
  public:
    virtual ~Node() {}
    virtual Node *eval() {};
    virtual std::string toString() {};
    virtual std::string className() {};
    int isFunction() { return 0; }
};

class NList : public Node {
  Node *_car;
  Node *_cdr;
  public:
    NList();
    NList(Node * car);
    NList(Node * car, Node * cdr);
    Node *car() { return _car; }
    Node *cdr() { return _cdr; }
    std::string toString();
    std::string className() { return "l"; }
    Node *eval();
    Node *eval(Node *node);
};

class NAtom : public Node {
  std::string _name;
  public:
    NAtom(const std::string& str);
    std::string toString();
    std::string className() { return "a"; }
    std::string name() { return _name; }
    Node *eval();
};

class NFunction : public Node {
  NAtom *_atom;
  Node *(*_body)(NList *);
  public:
    NFunction(NAtom *atom, Node * (*body)(NList *) );
    Node *apply(NList *);
    std::string name() { return _atom->name(); }
    int isFunction() { return 1; }
};


class NNumber : public Node {
  public:
    virtual NNumber *plus(NNumber *other) {};
    Node *eval();
};

class NInteger : public NNumber {
  long _value;
  public:
    NInteger();
    NInteger(const char *str);
    NInteger(long l);
    std::string toString();
    std::string className() { return "i"; }
    NNumber *plus(NNumber *other);
};

class NDouble : public NNumber {
  double _value;
  public:
  NDouble();
  NDouble(double d);
  NDouble(const char *str);
  std::string toString();
  NNumber *plus(NNumber *other);
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
