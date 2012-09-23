#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>

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
  private:
    std::map<std::string, NAtom *> _atoms;
    std::map<NAtom *, Node *> _values;
  public:
    Context();
    NAtom *getAtom(std::string& name);
    Node *getValue(NAtom *atom);
    void defineValue(NAtom *atom, Node *value);
  protected:
    NFunction *defineCoreFunction(std::string name, Node *(*body)(NList *, Context *));
    NFunction *defineFunction(NAtom *atom, Node *(*body)(NList *, Context *));
};

class Node {
  public:
    virtual ~Node() {}
    virtual Node *eval() {};
    virtual std::string toString() {};
    virtual std::string className() {};
    virtual int isFunction() { return 0; }
};

class NList : public Node {
  private:
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
  private:
    std::string _name;
  public:
    NAtom(const std::string& str);
    std::string toString();
    std::string className() { return "a"; }
    std::string name() { return _name; }
    Node *eval();
};

class NFunction : public Node {
  private:
    NAtom *_atom;
    Context *_context;
    Node *(*_body)(NList *, Context *);
  public:
    NFunction(Node * (*body)(NList *, Context *) );
    NFunction(Context *, Node * (*body)(NList *, Context *) );
    Node *apply(NList *);
    std::string toString();
    std::string name() { return _atom->name(); }
    int isFunction() { return 1; }
};

class NNumber : public Node {
  public:
    virtual NNumber *plus(NNumber *other) {};
    virtual NNumber *minus(NNumber *other) {};
    Node *eval() { return this; }
};

class NInteger : public NNumber {
  private:
    long _value;
  public:
    NInteger();
    NInteger(const char *str);
    NInteger(long l);
    std::string toString();
    std::string className() { return "i"; }
    NNumber *plus(NNumber *other);
    NNumber *minus(NNumber *other);
};

class NDouble : public NNumber {
  private:
    double _value;
  public:
    NDouble();
    NDouble(double d);
    NDouble(const char *str);
    std::string toString();
    NNumber *plus(NNumber *other);
    NNumber *minus(NNumber *other);
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
