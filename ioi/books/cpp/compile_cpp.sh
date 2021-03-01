#!/bin/bash

problem=books

g++ -std=gnu++14 -Wall -Wextra -Wshadow -Wconversion -fsanitize=address -fsanitize=undefined -Dtmd -O2 -pipe -o $problem grader.cpp $problem.cpp
