#pragma once
#include "Map.h"
#include <time.h>
#include <string>

// use header file with function signatures for server to avoid multiple redefinitions of functions (once in here, and once in client, by including server.h)

bool hasValidPath(Map& map, int startX, int startY);
std::string generateRandomMap(int size);