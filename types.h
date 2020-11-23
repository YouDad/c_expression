#include <string>

struct compile_type {
	std::string str;
	int integer;
	char op;
};

#define YYSTYPE struct compile_type
