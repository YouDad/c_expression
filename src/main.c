#include "header.h"

int main(int argc, char **argv) {
	for (int i = 1; i < argc; i++) {
		if (strstr(argv[i], "-v")) {
			int level = 0;
			for (char *p = argv[i]; *p; p++) {
				if (*p == 'v') {
					level++;
				}
			}

			if (level > log::LL_DEBUG) {
				level = log::LL_DEBUG;
			}

			log::set_level((log::LOG_LEVEL)level);
		}
	}

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

		if (parse_ret == 1) {
			printf("occur error!\n\n");
		} else if (parse_ret == 2) {
			printf("\n");
		} else {
			printf("calc result: %d\n\n", result);
		}
	}
	return 0;
}
