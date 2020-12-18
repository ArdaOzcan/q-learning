#! /usr/bin/bash
cd obj
g++ -c ../src/*.cpp
cd ../bin
g++ ../obj/* -o main -lsfml-graphics -lsfml-window -lsfml-system