%{
#include <string>
#include "AST/node.hpp"
#include "parser.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
extern "C" int yywrap() {}
%}

%%

[ \t\n]                         ;
[+-]?[0-9,]*\.[0-9,]+           SAVE_TOKEN; return TDOUBLE;
[+-]?[0-9,]+                    SAVE_TOKEN; return TINTEGER;
0b[01,]+                        SAVE_TOKEN; return TBINARY;
0x[0-9a-fA-F,]+                 SAVE_TOKEN; return THEXADECIMAL;
0o[0-7,]+                       SAVE_TOKEN; return TOCTAL;
[a-z+-.\/*%?!|$@]+              SAVE_TOKEN; return TIDENTIFIER;
"("                             return TOKEN(TLPAREN);
")"                             return TOKEN(TRPAREN);
"{"                             return TOKEN(TLBRACE);
"}"                             return TOKEN(TRBRACE);
\b.\b                           return TOKEN(TDOT);

%%
