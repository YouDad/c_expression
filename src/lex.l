%{
#include "header.h"
%}

%x COMMENT

digit         ([0-9])
alpha         ([A-Za-z_])

integer       ({digit}+)
identifier    ({alpha}({alpha}|{digit})*)
op_assign     (([+*/%&|^-]|<<|>>)=)

%%

{identifier} {
	yylval.str = yytext;
	return IDENTIFIER;
}

{integer} {
	yylval.integer = atoi(yytext);
	return INTEGER;
}

"//" {
	BEGIN COMMENT;
}

"++" {
	yylval.str = yytext;
	return OP_INC;
}

"--" {
	yylval.str = yytext;
	return OP_DEC;
}

">>" {
	yylval.str = yytext;
	return OP_LSR;
}

"<<" {
	yylval.str = yytext;
	return OP_LSL;
}

"<" {
	yylval.str = yytext;
	return OP_LT;
}

"<=" {
	yylval.str = yytext;
	return OP_LE;
}

">" {
	yylval.str = yytext;
	return OP_GT;
}

">=" {
	yylval.str = yytext;
	return OP_GE;
}

"==" {
	yylval.str = yytext;
	return OP_EQ;
}

"!=" {
	yylval.str = yytext;
	return OP_NE;
}

"&&" {
	yylval.str = yytext;
	return OP_AND;
}

"||" {
	yylval.str = yytext;
	return OP_OR;
}

{op_assign} {
	yylval.str = yytext;
	return OP_ASSIGN;
}

([()+*/%=!~&^|?:-]) {
	yylval.op = yytext[0];
	return yytext[0];
}

"\n" {}
. {}

<COMMENT>\n {
	BEGIN INITIAL;
}

<COMMENT>. {}

%%
