cmake_minimum_required(VERSION 3.1)

project(SFMLGame)

set(CMAKE_CXX_STANDARD 17)

# Find SFML library
set(SFML_DIR SFML-2.5.1/lib/cmake/SFML)

# include_directories(SFML-2.5.1/include/SFML)

find_package(SFML 2.5.1 COMPONENTS graphics window audio REQUIRED)

# Add source files
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Screen.cpp
    src/MenuScreen.cpp
    src/Button.cpp
    src/GameScreen.cpp
    src/Ball.cpp
    src/Paddle.cpp
    src/LevelLoader.cpp
    src/Brick.cpp
    src/GameOverScreen.cpp
    src/GameSuccessScreen.cpp
)

# Add header files
set(HEADERS
    Game.h
    ElementType.h
    Screen.h
    MenuScreen.h
    Button.h
    GameScreen.h
    Ball.h
    Paddle.h
    LevelLoader.h
    Brick.h
    GameOverScreen.h
    GameSuccessScreen.h
)


# Add executable
add_executable(sfAkitsu ${SOURCES} ${HEADERS})


# Link SFML libraries
target_link_libraries(sfAkitsu sfml-graphics sfml-window sfml-audio)

# target_link_libraries(snake_test sfml-graphics sfml-window sfml-audio)