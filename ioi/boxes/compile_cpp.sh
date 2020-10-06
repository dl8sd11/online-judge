#!/bin/bash

problem=boxes

g++ -Dtmd -DEVAL -O2 -std=c++11 -o $problem -Wall -Wshadow -Wextra -Wconversion -fsanitize=address -fsanitize=undefined grader.cpp $problem.cpp
