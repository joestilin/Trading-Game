cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} include src)

add_executable(TradingGame src/main.cpp src/game.cpp src/chart.cpp src/renderer.cpp 
                           src/controller.cpp src/tradelog.cpp src/dataframe.cpp 
                           src/databar.cpp src/dataparser.cpp src/trade.cpp 
                           src/symbol.cpp src/lobby.cpp src/endgame.cpp) 

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/fonts
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/python
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(TradingGame ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARY})