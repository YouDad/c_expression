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

([()+*/=-]) {
	yylval.op = yytext[0];
	return yytext[0];
}

. {}

<COMMENT>\n {
	BEGIN INITIAL;
}

<COMMENT>. {}

%%
