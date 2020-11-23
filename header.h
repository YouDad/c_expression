#ifndef HEADER_H_
#define HEADER_H_

#include <map>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "yacc.tab.h"

extern "C" {
	void yyerror(const char *s);
	int yylex(void);
	int yywrap();
}

extern std::map<std::string, int> variables;

#endif
