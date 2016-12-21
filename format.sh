#!/bin/sh

find ./modules/attribute -iname *.hpp -o -iname *.cpp | xargs clang-format -i
find ./modules/core -iname *.hpp -o -iname *.cpp | xargs clang-format -i
find ./modules/event -iname *.hpp -o -iname *.cpp | xargs clang-format -i
# find ./modules/graphic -iname *.hpp -o -iname *.cpp | xargs clang-format -i
find ./modules/os -iname *.hpp -o -iname *.cpp | xargs clang-format -i
find ./modules/util -iname *.hpp -o -iname *.cpp | xargs clang-format -i
find ./modules/widget -iname *.hpp -o -iname *.cpp | xargs clang-format -i