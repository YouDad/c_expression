#include "header.h"

std::map<std::string, int> variables;

void yyerror(const char *s) {
	printf("error: %s\n", s);
}

extern FILE *yyin;

int main() {
	char buf[1 << 12];
	while (1) {
		printf("calc > ");
		memset(buf, 0, sizeof(buf));
		char *ret = fgets(buf, sizeof(buf), stdin);
		if (ret == 0) {
			break;
		}

		yyin = fmemopen(buf, sizeof(buf), "r");
		yyparse();
		fclose(yyin);
	}
	return 0;
}
