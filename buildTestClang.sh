#!/bin/bash

pushd ToupleTest
clang++ test.cpp -o test -O2 -std=gnu++17 -I../RayTracerChallenge -pthread -lgtest -lgtest_main
./test
popd
