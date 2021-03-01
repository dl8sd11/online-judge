#!/bin/bash

problem=books

g++ -Wall -Wextra -Wshadow -Wconversion -fsanitize=address -fsanitize=undefined -Dtmd -std=gnu++14 -O2 -pipe -o $problem grader.cpp $problem.cpp
