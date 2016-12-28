#!/bin/bash

# pistache
echo 'Installing pistache.io'

git clone https://github.com/oktal/pistache.git server/externals/
cd server/externals/pistache
mkdir build
cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release .. && make && sudo make install
