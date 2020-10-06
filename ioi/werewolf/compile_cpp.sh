#!/bin/bash

TASK=werewolf

g++ -std=gnu++14 -O2 -Dtmd -fsanitize=address -fsanitize=undefined -Wall -Wextra -Wshadow -Wconversion -o ${TASK} grader.cpp ${TASK}.cpp
