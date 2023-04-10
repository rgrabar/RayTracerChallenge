#!/bin/bash
#clang++ RayTracerChallenge/*.cpp -o RayTracer -O2 -std=gnu++17 -IRayTracerChallenge -pthread -Wall -pedantic -Wextra
#read -n 1 -s -r -p "Press any key to continue..."


if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    make='make'
    linkflags="-lGL -lm -lpthread -ldl -lrt -lX11"
else # I'm not rich so I can't and categorically refuse to even attempt to test on a mac so this assumes the only other option is windows
    make='mingw32-make'
    linkflags="-lopengl32 -lgdi32 -lwinmm"
fi

pushd raylib/src
$make PLATFORM=PLATFORM_DESKTOP
popd

clang++ RayTracerChallenge/*.cpp -o RayTracer -O2 -std=c++17 -IRayTracerChallenge -Iraylib/src -Lraylib/src -lraylib $linkflags
