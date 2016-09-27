#!/bin/bash
echo "Formatting..."
clang-format -style=file -i game/src/*.cpp
clang-format -style=file -i game/include/*.h
echo "Complete!"