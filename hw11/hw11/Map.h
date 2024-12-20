#pragma once
#include <fstream>
#include <cmath>
#include <iostream>

enum Terrain { PATH, MOUNTAIN, CLIFF, START, FINISH };

class Map {
private:
    int size;
    enum Terrain** grid;
    int start;
    int finish;

public:
    Map(): size(0), grid(nullptr), start(0), finish(0) {}

    Map(int size, int start, int finish): size(size), start(start), finish(finish) {
        this->grid = new enum Terrain*[this->size];
        for (int i = 0; i < this->size; i++) {
            this->grid[i] = new enum Terrain[this->size];
        }
    }

    Map(const Map& other): size(other.size), start(other.start), finish(other.finish) {
        this->grid = new enum Terrain*[this->size];
        for (int i = 0; i < this->size; i++) {
            this->grid[i] = new enum Terrain[this->size];
            for (int j = 0; j < this->size; j++) {
                this->grid[i][j] = other.grid[i][j];
            }
        }
    }

    ~Map() {
        if (grid) {
            for (int i = 0; i < this->size; i++) {
                delete[] this->grid[i];
                this->grid[i] = nullptr;
            }
            delete[] this->grid;
            this->grid = nullptr;
        }
    }

    int getSize() const { // const to ensure no mishaps occur when dealing with the size in other functions, had to do it to fix some issues, but may be working without
        return this->size; 
    } 

    int getStart() { 
        return this->start; 
    }

    int getFinish() { 
        return this->finish; 
    }

    enum Terrain getTerrain(int x, int y) { 
        return this->grid[x][y]; 
    }

    void setTerrain(int x, int y, enum Terrain t) { 
        if (0 <= x < this->size && 0 <= y < this->size)
            this->grid[x][y] = t;
        else
            std::cout << "ERROR: Wrong coordinates for terrain set!" << std::endl;
    }

    void serialize(const std::string& filename) { // since enum elements are basically ints, we just write them to the file in continuous order
        std::ofstream file(filename, std::ios::binary | std::ios::trunc);
        for (int i = 0; i < this->size; i++) {
            for (int j = 0; j < this->size; j++) {
                file.write((char*)&this->grid[i][j], sizeof(enum Terrain));
            }
        }
        file.close();
    }

    void deserialize(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary | std::ios::ate); // std::ios::ate points the file position pointer at the end already, for usage for tellg
        int fileSize = file.tellg(); // determine filesize
        this->size = (int)(sqrt(fileSize / sizeof(enum Terrain))); // determine size of grid

        if (this->grid) { // cleanup for previous grid if it exists
            for (int i = 0; i < this->size; i++) {
                delete[] this->grid[i];
                this->grid[i] = nullptr;
            }
            delete[] this->grid;
            this->grid = nullptr;
        }

        this->grid = new enum Terrain*[this->size];
        for (int i = 0; i < this->size; i++) {
            this->grid[i] = new enum Terrain[this->size];
        }

        file.seekg(0); // set file position pointer back to 0 (tellg calculates the difference between where it is in the file now and the start)
        for (int i = 0; i < this->size; i++) {
            for (int j = 0; j < this->size; j++) {
                file.read((char*)&this->grid[i][j], sizeof(enum Terrain));
            }
        }

        for (int j = 0; j < this->size; j++) { // find start and finish positions
            if (this->grid[0][j] == START)
                this->start = j;
            if (this->grid[this->size - 1][j] == FINISH)
                this->finish = j;
        }
    }

    void print(int playerX, int playerY) {
        for (int i = 0; i < this->size; i++) {
            for (int j = 0; j < this->size; j++) {
                if (i == playerX && j == playerY) {
                    std::cout << '+';
                    continue; // skip rest of processing in the loop and jump to the next iteration
                }

                switch (this->grid[i][j]) {
                    case START: 
                        std::cout << 'S'; 
                        break;
                    case FINISH: 
                        std::cout << 'F'; 
                        break;
                    case PATH: 
                        std::cout << ' '; 
                        break;
                    case CLIFF: 
                        std::cout << '#'; 
                        break;
                    case MOUNTAIN: 
                        std::cout << '*'; 
                        break;
                }
            }
            std::cout << std::endl;
        }
    }
};
