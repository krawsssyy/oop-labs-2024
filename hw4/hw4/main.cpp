#include "Console.h"

int main() {
	Repository r;
	Service s(r);
	Console c(s);
	c.run();

	return 0;
}