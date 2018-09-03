#pragma once

#include <stdio.h>

class Formatter {
public:
	Formatter();
	Formatter(char *text);
	~Formatter();
	void pump(FILE *input_stream);
	void sink(FILE *output_stream);
	Formatter upperCase();
	Formatter lowerCase();
	Formatter baloon();
	Formatter tuxSay();
private:
	char *text;
};
