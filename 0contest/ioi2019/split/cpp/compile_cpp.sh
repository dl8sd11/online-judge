#!/bin/bash

problem=split100

g++ -std=gnu++14 -O2 -Wall -pipe -o "${problem}" "grader.cpp" "${problem}.cpp" -Dtmd -fsanitize=address -fsanitize=undefined -Wextra -Wshadow
