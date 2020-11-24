#include "header.h"

std::map<std::string, int> variables;
int result;

void yyerror(const char *s) {
	printf("error: %s\n", s);
}
