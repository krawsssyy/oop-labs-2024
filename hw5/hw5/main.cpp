#include "Console.h"

int main() {
	Repository r = Repository(); 
	Service s(r);
	Console c(s);
	c.run();
	return 0;
}