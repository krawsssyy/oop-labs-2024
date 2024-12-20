#include "Server.h"

int main() {
    int size;
    std::cout << "Enter size of the map: ";
    std::cin >> size; std::cout << std::endl;

    std::cout << "Initializing server and generating map..." << std::endl;
    std::string filename = generateRandomMap(size);
    Map map;
    map.deserialize(filename);
    std::cout << "Map loaded!" << std::endl;
    
    // initialize game variables
    int playerX = 0;
    int playerY = map.getStart();
    int score = 0;
    std::string input;

    // main game loop
    std::cout << "Starting game..." << std::endl << std::endl;
    while (true) {
        std::cout << "Score: " << score << std::endl << std::endl;
        map.print(playerX, playerY);

        std::cout << std::endl << "\nEnter move (UP/DOWN/LEFT/RIGHT/EXIT): ";
        std::cin >> input; std::cout << std::endl;

        // save last valid position
        int prevX = playerX;
        int prevY = playerY;

        // process input
        if (input == "EXIT") {
            std::cout << std::endl << "Goodbye!";
            break;
        }
        else if (input == "UP") 
            playerX--;
        else if (input == "DOWN") 
            playerX++;
        else if (input == "LEFT") 
            playerY--;
        else if (input == "RIGHT") 
            playerY++;
        else {
            std::cout << "Invalid input! Try again." << std::endl;
            continue;
        }
        
        // check for bounds conditions (can be achieved by going UP when at start) - still it is good to ensure both are within bounds
        if (0 > playerX || playerX >= size || 0 > playerY || playerY >= size) {
            std::cout << "You've somehow fell outside the map! Game over!" << std::endl;
            break;
        }

        Terrain current = map.getTerrain(playerX, playerY);
        // check terrain conditions
        if (current == CLIFF) {
            std::cout << "You fell into a cliff! Game over!" << std::endl;
            break;
        }
        else if (current == MOUNTAIN) {
            std::cout << "You cannot move into mountains! Try again." << std::endl;
            playerX = prevX;
            playerY = prevY;
            continue;
        }
        else if (current == FINISH) {
            std::cout << "Congratulations! You reached the finish!" << std::endl;
            std::cout << "Final score: " << score + 1 << std::endl;
            break;
        }

        score++;
    }

    std::remove(filename.c_str()); // delete the file with the map - requires arg to be const char*, thus the .c_str() usage
    return 0;
}