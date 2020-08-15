#!/bin/sh

wget https://github.com/glfw/glfw/releases/download/3.3.2/glfw-3.3.2.zip -P ./vendor
cd vendor
unzip glfw-3.3.2.zip
cd glfw-3.3.2
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../../../
make
make install
cd ../../../ && touch src/env.hpp
ENV_CODE="#ifndef ENV_H\n#define ENV_H\n\n#define PROJECT_ROOT \"$PWD/\"\n\n#endif"
echo "$ENV_CODE" > src/env.hpp
mkdir build