#include <Formatter.hpp>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	Formatter fmtr;
	fmtr.pump(stdin);
	fmtr.upperCase().baloon().tuxSay().baloon().sink(stdout);
	return 0;
}
