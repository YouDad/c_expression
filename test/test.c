#include "header.h"

#define test(calc_expression, result, retval) \
	_test(calc_expression, sizeof(calc_expression), result, retval, __LINE__);

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
	ret = ret && test("0",     0, 0);
	ret = ret && test("0/0",   0, 1);
	ret = ret && test("0/1",   0, 0);
	ret = ret && test("1+8*3", 25, 0);
	ret = ret && test("1-8*3", -23, 0);
	ret = ret && test("1+8/3", 3, 0);
	ret = ret && test("1-8/3", -1, 0);
	ret = ret && test("1+(2+3)*4", 21, 0);
	ret = ret && test("a=1", 1, 0);
	ret = ret && test("a", 1, 0);
	ret = ret && test("b=(a=a*2)+2", 4, 0);
	ret = ret && test("a", 2, 0);
	ret = ret && test("b", 4, 0);
	ret = ret && test("c=-a", -2, 0);
	ret = ret && test("c", -2, 0);
	ret = ret && test("(a+b)/(c)", -3, 0);

	// !, +, -, ~, ++, --
	ret = ret && test("!2", 0, 0);
	ret = ret && test("!+2", 0, 0);
	ret = ret && test("!-2", 0, 0);
	ret = ret && test("!0", 1, 0);
	ret = ret && test("~0", -1, 0);
	ret = ret && test("++c", -1, 0);
	ret = ret && test("--c", -2, 0);

	ret = ret && test("!2 * 0", 0, 0);
	ret = ret && test("!+2 * 0", 0, 0);
	ret = ret && test("!-2 * 0", 0, 0);
	ret = ret && test("!0 + 1", 2, 0);
	ret = ret && test("~1 + 1", -1, 0);
	ret = ret && test("++c + 1", 0, 0);
	ret = ret && test("--c + 1", -1, 0);

	// %
	ret = ret && test("1%2", 1, 0);
	ret = ret && test("3%2", 1, 0);
	ret = ret && test("3%0", 0, 1);
	ret = ret && test("c%3", -2, 0);
	ret = ret && test("c%3 + 2", 0, 0);
	ret = ret && test("c%~1 + 2", 2, 0);

	// <<, >>
	ret = ret && test("1<<0", 1 << 0, 0);
	ret = ret && test("1<<20", 1 << 20, 0);
	ret = ret && test("100>>0", 100 >> 0, 0);
	ret = ret && test("100>>4", 100 >> 4, 0);

	ret = ret && test("c = 1<<0", 1 << 0, 0);
	ret = ret && test("c + 1<<20", 2 << 20, 0);
	ret = ret && test("c + 100>>0", 101 >> 0, 0);
	ret = ret && test("c = 100>>4", 100 >> 4, 0);

	// <, <=, >, >=
	ret = ret && test("1 < 1", 1 < 1, 0);
	ret = ret && test("1 <= 1", 1 <= 1, 0);
	ret = ret && test("1 > 1", 1 > 1, 0);
	ret = ret && test("1 >= 1", 1 >= 1, 0);

	ret = ret && test("1 << 1 < 1", 1 << 1 < 1, 0);
	ret = ret && test("1 << 1 <= 1", 1 << 1 <= 1, 0);
	ret = ret && test("1 << 1 > 1", 1 << 1 > 1, 0);
	ret = ret && test("1 << 1 >= 1", 1 << 1 >= 1, 0);

	ret = ret && test("c = 1 < 1", 1 < 1, 0);
	ret = ret && test("c = 1 <= 1", 1 <= 1, 0);
	ret = ret && test("c = 1 > 1", 1 > 1, 0);
	ret = ret && test("c = 1 >= 1", 1 >= 1, 0);

	// ==, !=
	ret = ret && test("1 == 1", 1 == 1, 0);
	ret = ret && test("1 != 1", 1 != 1, 0);

	ret = ret && test("1 << 1 == 1", 1 << 1 == 1, 0);
	ret = ret && test("1 << 1 != 1", 1 << 1 != 1, 0);
	ret = ret && test("c = 1 == 1", 1 == 1, 0);
	ret = ret && test("c = 1 != 1", 1 != 1, 0);

	// &, ^, |
	ret = ret && test("5 & 3", 5 & 3, 0);
	ret = ret && test("1 + 4 & 3", 5 & 3, 0);
	ret = ret && test("c = 5 & 3", 5 & 3, 0);

	ret = ret && test("5 ^ 3", 5 ^ 3, 0);
	ret = ret && test("1 + 4 ^ 3", 5 ^ 3, 0);
	ret = ret && test("c = 5 ^ 3", 5 ^ 3, 0);

	ret = ret && test("1 + 4 | 3", 5 | 3, 0);
	ret = ret && test("5 | 3", 5 | 3, 0);
	ret = ret && test("c = 5 | 3", 5 | 3, 0);

	ret = ret && test("1 ^ 3 & 2", 1 ^ 3 & 2, 0);
	ret = ret && test("4 | 3 & 2", 4 | 3 & 2, 0);
	ret = ret && test("1 | 1 ^ 1", 1 | 1 ^ 1, 0);

	// &&, ||
	ret = ret && test("1 && 1", 1 && 1, 0);
	ret = ret && test("0 && 1", 0 && 1, 0);
	ret = ret && test("0 && 0", 0 && 0, 0);
	ret = ret && test("1 || 1", 1 || 1, 0);
	ret = ret && test("0 || 1", 0 || 1, 0);
	ret = ret && test("0 || 0", 0 || 0, 0);

	ret = ret && test("1 ^ 1 && 1", 1 ^ 1 && 1, 0);
	ret = ret && test("1 ^ 0 && 1", 1 ^ 0 && 1, 0);
	ret = ret && test("1 ^ 0 && 0", 1 ^ 0 && 0, 0);
	ret = ret && test("1 ^ 1 || 1", 1 ^ 1 || 1, 0);
	ret = ret && test("1 ^ 0 || 1", 1 ^ 0 || 1, 0);
	ret = ret && test("1 ^ 0 || 0", 1 ^ 0 || 0, 0);

	ret = ret && test("c = 1 && 1", 1 && 1, 0);
	ret = ret && test("c = 0 && 1", 0 && 1, 0);
	ret = ret && test("c = 0 && 0", 0 && 0, 0);
	ret = ret && test("c = 1 || 1", 1 || 1, 0);
	ret = ret && test("c = 0 || 1", 0 || 1, 0);
	ret = ret && test("c = 0 || 0", 0 || 0, 0);

	ret = ret && test("1 || 1 && 0", 1 || 1 && 0, 0);
	return ret ? 0 : 1;
}
