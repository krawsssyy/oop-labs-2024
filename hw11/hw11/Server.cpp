#include "Server.h"

struct Position { // helper struct for traversing the grid, via a linked list
    int x, y;
    Position* next;
};

bool hasValidPath(Map& map, int startX, int startY) { // very similar implementation to dijkstra, adapted to our usecase
    int size = map.getSize();

    // keep a bool array to save positions where we've been
    bool** visited = new bool*[size];
    for (int i = 0; i < size; i++) {
        visited[i] = new bool[size];
        memset(visited[i], 0, sizeof(bool) * size);
    }

    // manual stack implementation using linked positions
    Position* list = nullptr;

    // push initial position
    Position* startPos = new Position{ startX, startY, list };
    list = startPos;
    bool foundPath = false;

    // while there are still positions we haven't visited or while a path is not yet found
    while (list != nullptr && !foundPath) {
        Position* current = list; // get current position
        list = list->next; // advance list of positions
        int x = current->x;
        int y = current->y;

        // cleanup
        delete current;

        // skip position if out of bounds or on invalid terrain or already visited - do it first to ensure next checks are within bounds
        if (0 > x || x >= size || 0 > y || y >= size) 
            continue;
        if (visited[x][y] || map.getTerrain(x, y) == CLIFF || map.getTerrain(x, y) == MOUNTAIN) 
            continue;

        visited[x][y] = true;

        if (x == size - 1 && y == map.getFinish()) {
            foundPath = true;
            break;
        }

        // all adjacent positions to our current one
        Position* positions[] = {
            new Position{x + 1, y, nullptr},
            new Position{x - 1, y, nullptr},
            new Position{x, y + 1, nullptr},
            new Position{x, y - 1, nullptr}
        };

        // link and add them to the list
        for (int i = 0; i < 4; i++) {
            positions[i]->next = list;
            list = positions[i];
        }
    }

    // cleanup
    while (list != nullptr) {
        Position* temp = list;
        list = list->next;
        delete temp;
    }
    for (int i = 0; i < size; i++) {
        delete[] visited[i];
        visited[i] = nullptr;
    }
    delete[] visited;
    visited = nullptr;

    return foundPath;
}

std::string generateRandomMap(int size) {
    srand(time(NULL)); // initialize and seed random generator with the current time
    int startPos = 1 + (rand() % (size - 2)); // generate a random number between 0 and size - 3, and add 1 to it, to be between 1 and size - 2, as to avoid corners
    int finishPos = 1 + (rand() % (size - 2));
    Map map(size, startPos, finishPos);

    for (int i = 0; i < size; i++) { // border the map with CLIFFs
        map.setTerrain(0, i, CLIFF);
        map.setTerrain(size - 1, i, CLIFF);
        map.setTerrain(i, 0, CLIFF);
        map.setTerrain(i, size - 1, CLIFF);
    }

    map.setTerrain(0, startPos, START);
    map.setTerrain(size - 1, finishPos, FINISH);
    map.setTerrain(1, startPos, PATH); // ensure PATH below START and above FINISH
    map.setTerrain(size - 2, finishPos, PATH);

    for (int i = 1; i < size - 1; i++) {
        for (int j = 1; j < size - 1; j++) {
            if ((i == 1 && j == startPos) || (i == size - 2 && j == finishPos)) // skip generation for the terrain below START and above FINISH
                continue;
            int terrain = rand() % 3; // generate random number between 0 and 2
            map.setTerrain(i, j, terrain < 2 ? PATH : MOUNTAIN); // if it's 0 or 1 it's PATH, else it is MOUNTAIN, thus the 2:1 ratio for PATHs
        }
    }

    bool pathExists = hasValidPath(map, 1, startPos); // check for a valid path, starting from below START
    if (!pathExists) { // if no path, regenerate
        return generateRandomMap(size);
    }

    std::string filename = "map.bin"; // if we reached this point, it means we have a map with a path, thus, serialize and return
    map.serialize(filename);
    return filename;
}