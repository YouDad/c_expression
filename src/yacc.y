%{
#include "header.h"
%}

%token<str>IDENTIFIER
%token<integer>INTEGER

%token<op>  '+' '-' '=' '(' ')'
%token<op>  '!' '~'
%token<str> OP_INC OP_DEC OP_LSL OP_LSR
%token<str> OP_LT OP_LE OP_GT OP_GE
%token<str> OP_EQ OP_NE
%token<str> OP_AND OP_OR
%token<op>  '*' '/' '%'
%token<op>  '&' '^' '|'
%token<op>  '?' ':'
%token<str> OP_ASSIGN

%type<integer> expression
%type<integer> statement

%right '=' OP_ASSIGN
%right '?' ':'
%left OP_OR
%left OP_AND
%left '|'
%left '^'
%left '&'
%left OP_EQ OP_NE
%left OP_LT OP_LE OP_GT OP_GE
%left OP_LSL OP_LSR
%left '+' '-'
%left '*' '/' '%'
%right '!' '~' OP_INC OP_DEC
%left '(' ')'

%%

statement: {
	return 2;
}

statement: expression {
	$$ = $1;
	result = $$;
	log::debug("statement %d", $1);
};

expression: IDENTIFIER '=' expression {
	variables[$1] = $3;
	$$ = $3;
	log::debug("%s %c %d", $1.c_str(), $2, $3);
};
expression: IDENTIFIER OP_ASSIGN expression {
	switch ($2[0]) {
		case '+':
			variables[$1] += $3;
			break;

		case '-':
			variables[$1] -= $3;
			break;

		case '*':
			variables[$1] *= $3;
			break;

		case '/':
			if ($3 == 0) {
				log::warn("div 0 error");
				$$ = 0;
				result = $$;
				return 1;
			}
			variables[$1] /= $3;
			break;

		case '%':
			if ($3 == 0) {
				log::warn("div 0 error");
				$$ = 0;
				result = $$;
				return 1;
			}
			variables[$1] %= $3;
			break;

		case '&':
			variables[$1] &= $3;
			break;

		case '|':
			variables[$1] |= $3;
			break;

		case '^':
			variables[$1] ^= $3;
			break;

		case '<':
			variables[$1] <<= $3;
			break;

		case '>':
			variables[$1] >>= $3;
			break;

	}
	$$ = variables[$1];
	log::debug("%s %s %d", $1.c_str(), $2.c_str(), $3);
};
expression: expression '?' expression ':' expression {
	$$ = $1 ? $3 : $5;
	log::debug("%d %c %d %c %d", $1, $2, $3, $4, $5);
};
expression: expression OP_AND expression {
	$$ = $1 && $3;
	log::debug("%d %s %d", $1, $2.c_str(), $3);
};
expression: expression OP_OR expression {
	$$ = $1 || $3;
	log::debug("%d %s %d", $1, $2.c_str(), $3);
};
expression: expression '&' expression {
	$$ = $1 & $3;
	log::debug("%d %c %d", $1, $2, $3);
};
expression: expression '^' expression {
	$$ = $1 ^ $3;
	log::debug("%d %c %d", $1, $2, $3);
};
expression: expression '|' expression {
	$$ = $1 | $3;
	log::debug("%d %c %d", $1, $2, $3);
};
expression: expression OP_EQ expression {
	$$ = $1 == $3;
	log::debug("%d %s %d", $1, $2.c_str(), $3);
};
expression: expression OP_NE expression {
	$$ = $1 != $3;
	log::debug("%d %s %d", $1, $2.c_str(), $3);
};
expression: expression OP_LT expression {
	$$ = $1 < $3;
	log::debug("%d %s %d", $1, $2.c_str(), $3);
};
expression: expression OP_LE expression {
	$$ = $1 <= $3;
	log::debug("%d %s %d", $1, $2.c_str(), $3);
};
expression: expression OP_GT expression {
	$$ = $1 > $3;
	log::debug("%d %s %d", $1, $2.c_str(), $3);
};
expression: expression OP_GE expression {
	$$ = $1 >= $3;
	log::debug("%d %s %d", $1, $2.c_str(), $3);
};
expression: expression OP_LSL expression {
	$$ = $1 << $3;
	log::debug("%d %s %d", $1, $2.c_str(), $3);
};
expression: expression OP_LSR expression {
	$$ = $1 >> $3;
	log::debug("%d %s %d", $1, $2.c_str(), $3);
};
expression: expression '+' expression {
	$$ = $1 + $3;
	log::debug("%d %c %d", $1, $2, $3);
};
expression: expression '-' expression {
	$$ = $1 - $3;
	log::debug("%d %c %d", $1, $2, $3);
};
expression: expression '*' expression {
	$$ = $1 * $3;
	log::debug("%d %c %d", $1, $2, $3);
};
expression: expression '/' expression {
	if ($3 == 0) {
		log::warn("div 0 error");
		$$ = 0;
		result = $$;
		return 1;
	} else {
		$$ = $1 / $3;
	}
	log::debug("%d %c %d", $1, $2, $3);
};
expression: expression '%' expression {
	if ($3 == 0) {
		log::warn("div 0 error");
		$$ = 0;
		result = $$;
		return 1;
	} else {
		$$ = $1 % $3;
	}
	log::debug("%d %c %d", $1, $2, $3);
};
expression: '!' expression {
	$$ = !$2;
	log::debug("%c %d", $1, $2);
};
expression: '~' expression {
	$$ = ~$2;
	log::debug("%c %d", $1, $2);
};
expression: OP_INC IDENTIFIER {
	$$ = ++variables[$2];
	log::debug("%s %s", $1.c_str(), $2.c_str());
};
expression: OP_DEC IDENTIFIER {
	$$ = --variables[$2];
	log::debug("%s %s", $1.c_str(), $2.c_str());
};
expression: '+' expression %prec '!' {
	$$ = $2;
	log::debug("%c %d", $1, $2);
};
expression: '-' expression %prec '!' {
	$$ = -$2;
	log::debug("%c %d", $1, $2);
};
expression: '(' expression ')' {
	$$ = $2;
	log::debug("%c %d %c", $1, $2, $3);
};
expression: INTEGER {
	$$ = $1;
	log::debug("INTEGER %d", $1);
};
expression: IDENTIFIER {
	$$ = variables[$1];
	log::debug("IDENTIFIER get %s, val = %d", $1.c_str(), variables[$1]);
};

%%
