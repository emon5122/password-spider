cmake_minimum_required(VERSION 3.10)

# Set project name and version
project(password_spider VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add source files
add_executable(password_spider main.c password_spider.c)

