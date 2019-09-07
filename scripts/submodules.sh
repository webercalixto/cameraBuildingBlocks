#!/bin/bash
cd ..
git submodule init
git submodule update
cd third-party/ninjaDaemon/
git checkout v09
cd scripts/
./clean.sh
./submodules.sh
./build.sh
