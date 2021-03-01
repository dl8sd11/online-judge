#!/bin/bash

problem=rect

g++ -std=gnu++14 -O2 -Wall -pipe -o "${problem}" "grader.cpp" "${problem}.cpp"
