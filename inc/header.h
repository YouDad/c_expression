#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <string.h>

#include <map>

#include "types.h"
#include "yacc.tab.h"
#include "modules/log.h"

extern "C" {
	void yyerror(const char *s);
	int yylex(void);
	int yywrap();
}

extern std::map<std::string, int> variables;
extern FILE *yyin;
extern int result;

#endif
