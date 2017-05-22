#!/bin/bash

echo -n "Building for win32..."
export PATH=/home/dawidd6/git/mxe/usr/bin:$PATH
make clean > /dev/null
i686-w64-mingw32.static-qmake-qt5 > /dev/null
make > /dev/null

cd server
make clean > /dev/null
i686-w64-mingw32.static-qmake-qt5 > /dev/null
make > /dev/null
cd ..
echo "done"

echo -n "Building for linux..."
make clean > /dev/null
qmake > /dev/null
make > /dev/null

cd server
make clean > /dev/null
qmake > /dev/null
make > /dev/null
cd ..
echo "done"
