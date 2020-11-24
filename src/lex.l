%{
#include "header.h"
%}

%x COMMENT

digit         ([0-9])
alpha         ([A-Za-z_])

integer       ({digit}+)
identifier    ({alpha}({alpha}|{digit})*)

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

([()+*/%=!~&^|-]) {
	yylval.op = yytext[0];
	return yytext[0];
}

. {}

<COMMENT>\n {
	BEGIN INITIAL;
}

<COMMENT>. {}

%%
