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
		log::warn("%d: ret(%d) != retval(%d)", line, ret, retval);
		return false;
	}

	if (calc_result != result) {
		log::warn("%d: test_result(%d) != result(%d)", line, calc_result, result);
		return false;
	}

	log::info("%d: pass\n", line);
	return true;
}

int main()
{
	log::set_level(log::LL_DEBUG);

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

	// ?:
	ret = ret && test(1 ? 1 : 0);
	ret = ret && test(0 ? 1 : 0);

	ret = ret && test(1 + 1 ? 1 : 0);
	ret = ret && test(c = 1 ? 1 : 0);

	ret = ret && test(1 ? 1 ? 2 : 1 : 0);
	ret = ret && test(1 ? 2 : 1 ? 1 : 0);

	// +=, -=, *=, /=, %=
	ret = ret && test(a = 1);
	ret = ret && test(a += 1);
	ret = ret && test(a *= 3);
	ret = ret && test(a /= 2);
	ret = ret && test(a -= 1);
	ret = ret && test(a %= 3);

	ret = ret && test(a = 3 / 3);
	ret = ret && test(a);
	ret = ret && test(a += 1 * 1);
	ret = ret && test(a *= 1 * 3);
	ret = ret && test(a /= 1 * 2);
	ret = ret && test(a -= 1 * 1);
	ret = ret && test(a %= 1 * 3);
	ret = ret && test_fail(a /= 0);
	ret = ret && test_fail(a %= 0);

	// &=, ^=, |=, <<=, >>=
	ret = ret && test(a = 3);
	ret = ret && test(a &= 2);
	ret = ret && test(a ^= 2);
	ret = ret && test(a |= 4);
	ret = ret && test(a <<= 5);
	ret = ret && test(a >>= 6);

	ret = ret && test(a = 3);
	ret = ret && test(a &= 1 * 2);
	ret = ret && test(a ^= 1 * 2);
	ret = ret && test(a |= 1 * 4);
	ret = ret && test(a <<= 1 * 5);
	ret = ret && test(a >>= 1 * 6);
	return ret ? 0 : 1;
}
