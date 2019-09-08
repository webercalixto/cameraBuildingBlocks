#!/bin/bash
cd ..
git submodule init
git submodule update
cd third-party/ninjaDaemon/
git checkout v0.9.1
cd scripts/
./clean.sh
./submodules.sh
./build.sh
