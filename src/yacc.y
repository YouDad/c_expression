%{
#include "header.h"
%}

%token<str>IDENTIFIER
%token<integer>INTEGER

%token<op>  '+' '-' '=' '(' ')'
%token<op>  '!' '~'
%token<str> PLUSPLUS MINUSMINUS
%token<str> OP_LSL OP_LSR
%token<op>  '*' '/' '%'

%type<integer> expression
%type<integer> statement

%right '='
%left OP_LSL OP_LSR
%left '+' '-'
%left '*' '/' '%'
%right '!' '~' PLUSPLUS MINUSMINUS
%left '(' ')'

%%

statement: expression {
	$$ = $1;
	result = $$;
	printf("%s, %d: statement %d\n", __FILE__, __LINE__, $1);
};

expression: IDENTIFIER '=' expression {
	variables[$1] = $3;
	$$ = $3;
	printf("%s, %d: %s %c %d\n", __FILE__, __LINE__, $1.c_str(), $2, $3);
};
expression: expression OP_LSL expression {
	$$ = $1 << $3;
	printf("%s, %d: %d %s %d\n", __FILE__, __LINE__, $1, $2.c_str(), $3);
};
expression: expression OP_LSR expression {
	$$ = $1 >> $3;
	printf("%s, %d: %d %s %d\n", __FILE__, __LINE__, $1, $2.c_str(), $3);
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
		result = $$;
		return 1;
	} else {
		$$ = $1 / $3;
	}
	printf("%s, %d: %d %c %d\n", __FILE__, __LINE__, $1, $2, $3);
};
expression: expression '%' expression {
	if ($3 == 0) {
		printf("%s, %d: div 0 error\n", __FILE__, __LINE__);
		$$ = 0;
		result = $$;
		return 1;
	} else {
		$$ = $1 % $3;
	}
	printf("%s, %d: %d %c %d\n", __FILE__, __LINE__, $1, $2, $3);
};
expression: '!' expression {
	$$ = !$2;
	printf("%s, %d: %c %d\n", __FILE__, __LINE__, $1, $2);
};
expression: '~' expression {
	$$ = ~$2;
	printf("%s, %d: %c %d\n", __FILE__, __LINE__, $1, $2);
};
expression: PLUSPLUS IDENTIFIER {
	$$ = ++variables[$2];
	printf("%s, %d: %s %s\n", __FILE__, __LINE__, $1.c_str(), $2.c_str());
};
expression: MINUSMINUS IDENTIFIER {
	$$ = --variables[$2];
	printf("%s, %d: %s %s\n", __FILE__, __LINE__, $1.c_str(), $2.c_str());
};
expression: '+' expression %prec '!' {
	$$ = $2;
	printf("%s, %d: %c %d\n", __FILE__, __LINE__, $1, $2);
};
expression: '-' expression %prec '!' {
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
