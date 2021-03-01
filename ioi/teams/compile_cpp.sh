#!/bin/bash

problem=teams

g++ -DEVAL -O2 -std=c++11 -o $problem -Wall -Wshadow -Wextra -Wconversion -Dtmd -fsanitize=address -fsanitize=undefined grader.cpp $problem.cpp
