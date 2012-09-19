%{
#include "node.hpp"

extern int yylex();
void yyerror(const char *s) { printf("ERROR: %s\n", s); }
%}

%union {
  Node *node;
  NAtom *atom;
  NList *list;
  NNumber *number;
  std::string *string;
  int token;
}

%token <string> TATOM TINTEGER TDOUBLE TBINARY THEXADECIMAL TOCTAL
%token <token>  TLPAREN TRPAREN TLBRACE TRBRACE TDOT

%type <node>   sexpr
%type <list>   list members
%type <number> number

%start program

%%

program : members;

sexpr   : TATOM                    { $$ = new NAtom(*$1); }
        | number
        | list
        ;

list    : TLPAREN members TRPAREN  { $$ = $2 }
        | TLPAREN TRPAREN          { $$ = new NList(); }
        ;

members : sexpr                    { $$ = new NList($1); }
        | sexpr members            { $$ = new NList($1, $2); }
        ;

number  : TINTEGER                 { $$ = new NInteger($1->c_str()); }
        | TDOUBLE                  { $$ = new NDouble($1->c_str()); }
        | TBINARY                  { $$ = new NBinary($1->c_str()); }
        | THEXADECIMAL             { $$ = new NHexadecimal($1->c_str()); }
        | TOCTAL                   { $$ = new NOctal($1->c_str()); }
        ;

%%
