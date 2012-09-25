#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>

class Node;
class NAtom;
class NChar;
class NString;
class NInteger;
class NDouble;
class NBinary;
class NOctal;
class NHexadecimal;
class NList;
class NFunction;
class NContext;

class Node {
  public:
    virtual ~Node() {}
    virtual Node *eval() {};
    virtual std::string toString() {};
    virtual std::string className() {};
};

class NContext : public Node {
  private:
    NContext *_parent;
    std::map<std::string, NAtom *> _atoms;
    std::map<NAtom *, Node *> _values;
  public:
    NContext(Node *node=NULL, NContext *parent=NULL);
    NAtom *getAtom(std::string& name);
    NAtom *getOrCreateAtom(std::string& name);
    Node *getValue(NAtom *atom);
    Node *defineValue(NAtom *atom, Node *value);
    std::string className() { return "x"; }
  protected:
    NFunction *defineCoreFunction(std::string name, Node *(*body)(NList *, NContext *));
    NFunction *defineFunction(NAtom *atom, Node *(*body)(NList *, NContext *));
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
    NContext *_context;
    Node *(*_body)(NList *, NContext *);
  public:
    NFunction(Node * (*body)(NList *, NContext *) );
    NFunction(NContext *, Node * (*body)(NList *, NContext *) );
    Node *apply(NList *);
    std::string toString();
    std::string className() { return "f"; }
};

class NNumber : public Node {
  public:
    virtual NNumber *plus(NNumber *other) {};
    virtual NNumber *minus(NNumber *other) {};
    virtual NNumber *times(NNumber *other) {};
    virtual NNumber *divide(NNumber *other) {};
    Node *eval() { return this; }
};

class NChar : public Node {
  private:
    char _value;
  public:
    NChar(char ch);
    std::string toString();
    std::string className() { return "c"; }
    Node *eval();
};

class NString : public NList {
  private:
    std::string toString(NList *list);
  public:
    NString() : NList() {};
    NString(Node * car) : NList(car) {};
    NString(Node * car, Node * cdr) : NList(car, cdr) {};
    std::string toString();
    std::string className() { return "s"; }
    Node *eval();
};

class NInteger : public NNumber {
  protected:
    long _value;
  public:
    NInteger();
    NInteger(const char *str);
    NInteger(long l);
    std::string toString();
    std::string className() { return "i"; }
    NNumber *plus(NNumber *other);
    NNumber *minus(NNumber *other);
    NNumber *times(NNumber *other);
    NNumber *divide(NNumber *other);
};

class NDouble : public NNumber {
  private:
    double _value;
  public:
    NDouble();
    NDouble(double d);
    NDouble(const char *str);
    std::string toString();
    std::string className() { return "d"; }
    NNumber *plus(NNumber *other);
    NNumber *minus(NNumber *other);
    NNumber *times(NNumber *other);
    NNumber *divide(NNumber *other);
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
