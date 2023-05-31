#include "../LevelLoader.h"
#include <fstream>
#include <sstream>
#include "../ElementType.h"

using namespace sfAkitsu;

std::vector<Brick> LevelLoader::loadLevel(const std::string& filename) {
    std::vector<Brick> bricks;

    std::ifstream file(filename);
    if (!file.is_open()) {
        // Error opening file
        return bricks;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        float x,y;
        int element_type;
        if (!(iss >> x >> y >> element_type)) {
            // Error parsing line
            continue;
        }
        sf::Vector2f position = sf::Vector2f(x, y);
        Brick brick(position, static_cast<ElementType>(element_type));
        bricks.push_back(brick);
    }
    return bricks;
}