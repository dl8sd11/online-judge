#!/bin/bash

problem=sorting

g++ -DEVAL -O2 -fsanitize=address -fsanitize=undefined -Dtmd -std=c++11 -o $problem -Wall -Wshadow -Wextra -Wconversion grader.cpp $problem.cpp
