cmake_minimum_required(VERSION 3.24)
project(Bug_Project1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Bug_Project1 main.cpp Bug.cpp Bug.h Crawler.cpp Crawler.h Hopper.cpp Hopper.h Board.cpp Board.h Direction.h Utils.cpp Utils.h Bishop.cpp Bishop.h SuperBug.cpp SuperBug.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/SFML-2.5.1/include)
target_link_libraries(Bug_Project1 sfml-system sfml-window sfml-graphics sfml-audio)