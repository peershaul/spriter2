#!/bin/env bash

g++ unity.cpp -o out -lGL -lSDL2 -lGLEW

echo ""
echo ""
if [ ! -z $1 ] && [ $1 = 'r' ]
then
    ./out
fi
