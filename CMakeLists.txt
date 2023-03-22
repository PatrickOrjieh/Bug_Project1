cmake_minimum_required(VERSION 3.24)
project(Bug_Project1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Bug_Project1 main.cpp Bug.cpp Bug.h Crawler.cpp Crawler.h)
