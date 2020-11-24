#include "header.h"

#define test(calc_expression) \
	_test(#calc_expression, sizeof(#calc_expression), calc_expression, 0, __LINE__)

#define test_fail(calc_expression) \
	_test(#calc_expression, sizeof(#calc_expression), 0, 1, __LINE__)

bool _test(const char *calc, int calc_len, int calc_result, int retval, int line)
{
	yyin = fmemopen((void *)calc, calc_len, "r");
	int ret = yyparse();
	fclose(yyin);

	if (ret != retval) {
		printf("%d: ret(%d) != retval(%d)\n", line, ret, retval);
		return false;
	}

	if (calc_result != result) {
		printf("%d: test_result(%d) != result(%d)\n", line, calc_result, result);
		return false;
	}

	printf("%d: pass\n", line);
	return true;
}

int main()
{
	bool ret = true;
	int a, b, c;
	ret = ret && test(0);
	ret = ret && test_fail(0/0);
	ret = ret && test(0/1);
	ret = ret && test(1+8*3);
	ret = ret && test(1-8*3);
	ret = ret && test(1+8/3);
	ret = ret && test(1-8/3);
	ret = ret && test(1+(2+3)*4);
	ret = ret && test(a=1);
	ret = ret && test(a);
	ret = ret && test(b=(a=a*2)+2);
	ret = ret && test(a);
	ret = ret && test(b);
	ret = ret && test(c=-a);
	ret = ret && test(c);
	ret = ret && test((a+b)/(c));

	// !, +, -, ~, ++, --
	ret = ret && test(!2);
	ret = ret && test(!+2);
	ret = ret && test(!-2);
	ret = ret && test(!0);
	ret = ret && test(~0);
	ret = ret && test(++c);
	ret = ret && test(--c);

	ret = ret && test(!2 * 0);
	ret = ret && test(!+2 * 0);
	ret = ret && test(!-2 * 0);
	ret = ret && test(!0 + 1);
	ret = ret && test(~1 + 1);
	ret = ret && test(++c + 1);
	ret = ret && test(--c + 1);

	// %
	ret = ret && test(1%2);
	ret = ret && test(3%2);
	ret = ret && test_fail(3%0);
	ret = ret && test(c%3);
	ret = ret && test(c%3 + 2);
	ret = ret && test(c%~1 + 2);

	// <<, >>
	ret = ret && test(1<<0);
	ret = ret && test(1<<20);
	ret = ret && test(100>>0);
	ret = ret && test(100>>4);

	ret = ret && test(c = 1<<0);
	ret = ret && test(c + 1<<20);
	ret = ret && test(c + 100>>0);
	ret = ret && test(c = 100>>4);

	// <, <=, >, >=
	ret = ret && test(1 < 1);
	ret = ret && test(1 <= 1);
	ret = ret && test(1 > 1);
	ret = ret && test(1 >= 1);

	ret = ret && test(1 << 1 < 1);
	ret = ret && test(1 << 1 <= 1);
	ret = ret && test(1 << 1 > 1);
	ret = ret && test(1 << 1 >= 1);

	ret = ret && test(c = 1 < 1);
	ret = ret && test(c = 1 <= 1);
	ret = ret && test(c = 1 > 1);
	ret = ret && test(c = 1 >= 1);

	// ==, !=
	ret = ret && test(1 == 1);
	ret = ret && test(1 != 1);

	ret = ret && test(1 << 1 == 1);
	ret = ret && test(1 << 1 != 1);
	ret = ret && test(c = 1 == 1);
	ret = ret && test(c = 1 != 1);

	// &, ^, |
	ret = ret && test(5 & 3);
	ret = ret && test(1 + 4 & 3);
	ret = ret && test(c = 5 & 3);

	ret = ret && test(5 ^ 3);
	ret = ret && test(1 + 4 ^ 3);
	ret = ret && test(c = 5 ^ 3);

	ret = ret && test(1 + 4 | 3);
	ret = ret && test(5 | 3);
	ret = ret && test(c = 5 | 3);

	ret = ret && test(1 ^ 3 & 2);
	ret = ret && test(4 | 3 & 2);
	ret = ret && test(1 | 1 ^ 1);

	// &&, ||
	ret = ret && test(1 && 1);
	ret = ret && test(0 && 1);
	ret = ret && test(0 && 0);
	ret = ret && test(1 || 1);
	ret = ret && test(0 || 1);
	ret = ret && test(0 || 0);

	ret = ret && test(1 ^ 1 && 1);
	ret = ret && test(1 ^ 0 && 1);
	ret = ret && test(1 ^ 0 && 0);
	ret = ret && test(1 ^ 1 || 1);
	ret = ret && test(1 ^ 0 || 1);
	ret = ret && test(1 ^ 0 || 0);

	ret = ret && test(c = 1 && 1);
	ret = ret && test(c = 0 && 1);
	ret = ret && test(c = 0 && 0);
	ret = ret && test(c = 1 || 1);
	ret = ret && test(c = 0 || 1);
	ret = ret && test(c = 0 || 0);

	ret = ret && test(1 || 1 && 0);
	return ret ? 0 : 1;
}
