%{
#include "header.h"
%}

%token<str>IDENTIFIER
%token<integer>INTEGER

%token<op>'+' '-' '*' '/' '=' '(' ')'

%type<integer> expression
%type<str> statement
%type file

%right '='
%left '+' '-'
%left '*' '/'
%left '(' ')'

%%

file: statement {
	printf("%s, %d: over %s (%d)\n", __FILE__, __LINE__, $1.c_str(), variables[$1]);
};

statement: IDENTIFIER '=' expression {
	variables[$1] = $3;
	printf("%s, %d: %s %c %d\n", __FILE__, __LINE__, $1.c_str(), $2, $3);
};
statement: expression {
	printf("%s, %d: statement %d\n", __FILE__, __LINE__, $1);
};

expression: expression '+' expression {
	$$ = $1 + $3;
	printf("%s, %d: %d %c %d\n", __FILE__, __LINE__, $1, $2, $3);
};
expression: expression '-' expression {
	$$ = $1 - $3;
	printf("%s, %d: %d %c %d\n", __FILE__, __LINE__, $1, $2, $3);
};
expression: expression '*' expression {
	$$ = $1 * $3;
	printf("%s, %d: %d %c %d\n", __FILE__, __LINE__, $1, $2, $3);
};
expression: expression '/' expression {
	if ($3 == 0) {
		printf("%s, %d: div 0 error\n", __FILE__, __LINE__);
		$$ = 0;
	} else {
		$$ = $1 / $3;
	}
	printf("%s, %d: %d %c %d\n", __FILE__, __LINE__, $1, $2, $3);
};
expression: '-' expression {
	$$ = -$2;
	printf("%s, %d: %c %d\n", __FILE__, __LINE__, $1, $2);
};
expression: '(' expression ')' {
	$$ = $2;
	printf("%s, %d: %c %d %c\n", __FILE__, __LINE__, $1, $2, $3);
};
expression: INTEGER {
	$$ = $1;
	printf("%s, %d: %d\n", __FILE__, __LINE__, $1);
};
expression: IDENTIFIER {
	$$ = variables[$1];
	printf("%s, %d: IDENTIFIER %s %d\n", __FILE__, __LINE__, $1.c_str(), variables[$1]);
};

%%
