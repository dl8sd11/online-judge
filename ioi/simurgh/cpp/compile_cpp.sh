#!/bin/bash

problem=simurgh

g++ -std=gnu++14 -O2 -Wall -Wextra -Wshadow -Wconversion -fsanitize=address -fsanitize=undefined -Dtmd -pipe -o $problem grader.cpp $problem.cpp
