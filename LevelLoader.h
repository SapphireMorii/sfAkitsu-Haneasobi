#pragma once

#include <vector>
#include <string>
#include "Brick.h"


namespace sfAkitsu {
    class LevelLoader {
    public:
        static std::vector<Brick> loadLevel(const std::string& filename);
    };
}

