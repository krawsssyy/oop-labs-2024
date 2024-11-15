#include "Console.h"

int main() {
	RepositoryAnimal rAnimal = RepositoryAnimal();
	RepositoryCage rCage = RepositoryCage();
	RepositorySupervisor rSupervisor = RepositorySupervisor();
	Service s = Service(rAnimal, rCage, rSupervisor);
	Console c = Console(s);
	c.run();
	return 0;
}