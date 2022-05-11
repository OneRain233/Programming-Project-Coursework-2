#!/bin/sh

# This script will install SDL2
# check if SDL2 is already installed
if [ -d /usr/include/SDL2 ]; then
  echo "SDL2 is already installed"
  exit 0
fi

# install SDL2
echo "Installing SDL2"
wget -O SDL2.tar.gz https://www.libsdl.org/release/SDL2-2.0.8.tar.gz
tar -xzf SDL2.tar.gz

cd SDL2-2.0.8 || exit
./configure --prefix=/usr/local
make
make install


