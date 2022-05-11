#!/bin/sh

SDL2_FLAG=0
LIBUI_FLAG=0
# This script will install SDL2 and libui for the current user.
# check if SDL2 is already installed
if [ -d /usr/local/include/SDL2 ]; then
  echo "SDL2 is already installed"
  SDL2_FLAG=1
fi

# install SDL2
if [ $SDL2_FLAG = 0 ]; then
  echo "Installing SDL2"
  wget -O SDL2.tar.gz https://www.libsdl.org/release/SDL2-2.0.8.tar.gz
  tar -xzf SDL2.tar.gz

  cd SDL2-2.0.8 || exit
  ./configure --prefix=/usr/local
  make
  make install
  cd .. || exit
  rm -rf SDL2-2.0.8
  rm SDL2.tar.gz
fi



#check if libuir is already installed
if [ -d /usr/local/include/ui.h ]; then
  echo "libui is already installed"
  LIBUI_FLAG=1
fi

if [ $LIBUI_FLAG = 0 ]; then

  echo "Installing libui"
  git clone https://github.com/andlabs/libui.git
  cd libui || exit
  meson setup build
  ninja -C build
  cd build/meson-out
  ln -sf libui.so.0 libui.so
  cd ../.. || exit
  install build/meson-out/libui.so /usr/lib/
  install build/meson-out/libui.so.0 /usr/lib/
  install ui.h /usr/include/
  install ui_unix.h /usr/include/
  cd .. || exit
  #rm -rf libui
fi
