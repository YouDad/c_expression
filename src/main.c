#include "header.h"


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
		int parse_ret = yyparse();
		fclose(yyin);

		if (parse_ret) {
			printf("occur error!\n\n");
		} else {
			printf("calc result: %d\n\n", result);
		}
	}
	return 0;
}