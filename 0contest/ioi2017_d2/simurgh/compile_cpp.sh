#!/bin/bash

problem=simurgh

#g++ -Wall -Wshadow -Wconversion -Wextra -Dtmd -fsanitize=address -fsanitize=undefined -std=gnu++14 -O2 -pipe -o $problem grader.cpp $problem.cpp
g++  -std=gnu++14 -O2 -pipe -o $problem grader.cpp $problem.cpp
