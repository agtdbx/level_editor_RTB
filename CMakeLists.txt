cmake_minimum_required(VERSION 3.22)
project(editeur_RTB)

set(CMAKE_CXX_STANDARD 14)

add_executable(editeur_RTB src/main.cpp src/Menu.cpp include/Menu.h src/Button.cpp include/Button.h src/Functions.cpp include/Functions.h src/Select.cpp include/Select.h src/Switch.cpp include/Switch.h src/Input.cpp include/Input.h)

INCLUDE_DIRECTORIES(/usr/local)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES} jsoncpp)