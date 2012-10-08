%{
#include "AST/node.hpp"
NContext *context;

extern int yylex();
void yyerror(const char *s) {}
%}

%union {
  Node *node;
  NAtom *atom;
  NList *list;
  NNumber *number;
  std::string *string;
  int token;
}

%token <string> TIDENTIFIER TINTEGER TDOUBLE TBINARY THEXADECIMAL TOCTAL TSTRING TCHAR
%token <token>  TLPAREN TRPAREN TLBRACE TRBRACE TDOT TQUOTE TBACKSLASH

%type  <node>   slist sexpr atom number achar charl
%type  <list>    list members schars stringl

%start program

%%

program : slist                    { context->setRootNode($1); }
        ;

slist   : sexpr                    { $$ = new NList($1); }
        | sexpr slist              { $$ = new NList($1, $2); }
        ;

sexpr   : atom                     { $$ = $1; }
        | list                     { $$ = $1; }
        ;

atom    : TIDENTIFIER              { $$ = context->getOrCreateAtom(*$1); }
        | stringl                  { $$ = $1; }
        | charl                    { $$ = $1; }
        | number                   { $$ = $1; }
        ;

stringl : TQUOTE schars TQUOTE     { $$ = $2; }
        | TQUOTE TQUOTE            { $$ = new NString(); }
        ;

schars  : achar                    { $$ = new NString($1); }
        | achar schars             { $$ = new NString($1, $2); }
        ;

charl   : TBACKSLASH achar         { $$ = $2; }
        ;

achar   : TCHAR                    { $$ = new NChar($1->c_str()[0]); }

list    : TLPAREN members TRPAREN  { $$ = $2; }
        | TLPAREN TRPAREN          { $$ = new NList(); }
        ;

members : sexpr                    { $$ = new NList($1); }
        | sexpr TDOT sexpr         { $$ = new NList($1, $3); }
        | sexpr members            { $$ = new NList($1, $2); }
        ;

number  : TINTEGER                 { $$ = new NInteger($1->c_str()); }
        | TDOUBLE                  { $$ = new NDouble($1->c_str()); }
        | TBINARY                  { $$ = new NBinary($1->c_str()); }
        | THEXADECIMAL             { $$ = new NHexadecimal($1->c_str()); }
        | TOCTAL                   { $$ = new NOctal($1->c_str()); }
        ;

%%
