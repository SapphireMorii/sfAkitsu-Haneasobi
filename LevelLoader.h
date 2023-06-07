#pragma once

#include <vector>
#include <string>
#include "Brick.h"
#include <map>


namespace sfAkitsu {
    class LevelLoader {
    public:
        static void loadLevel(const std::string& filename,std::vector<Brick> &bricks);
    };
}

