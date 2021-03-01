#!/bin/bash

NAME=holiday

/usr/bin/g++ -Wall -Wextra -Wconversion -Dtmd -fsanitize=address -fsanitize=undefined -DEVAL -O2 -std=c++11 -o $NAME grader.cpp $NAME.cpp
