#!/bin/bash

problem=walk

g++ -std=gnu++14 -O2 -Wall -pipe -o "${problem}" "grader.cpp" "${problem}.cpp" -Dtmd -fsanitize=address -fsanitize=undefined -fno-sanitize-recover
