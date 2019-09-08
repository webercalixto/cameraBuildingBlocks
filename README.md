### * Keep in mind this is a work in progress  

Author: weber calixto (webersouzacalixto at gmail)

# Table of contents
1. [About this project](#about)  
  1.1 [Git workflow ](#git_workflow)  
  1.1 [Dependencies ](#dependencies)  
2. [Prebuilt packages](#prebuilt_packages)
3. [Build Instructions](#build_instructions)  
  3.1 [First Build](#first_build)  
  3.2 [Subsequent Builds](#subsequent_builds)  
  3.2 [Clean](#clean) 

# About this project <a name="about"></a>

This repo will contain several processing blocks, necessary to build a functional IP camera.  
It is build upon several other projects (ninjadaemon, opencv, rapidjson, pistache, etc)  

My goal is to make easier for others to build their own IP camera devices.

## Exception handling

Some lines with potential exceptions are left un-try-catched intentionally so the ugly runtime error can be seen.

## Git workflow <a name="git_workflow"></a>

I've chosen to work with GitHubflow (i.e Only a master branch with feature branches, no master/develop branching scheme, versioning with git tags).

Convention: Every master commit must be stable.

## Dependencies <a name="dependencies"></a>

0. This project is built and tested with GCC 8.3 on a raspberry pi 3 running raspbian 10. Feel free to build/test on other platforms.  

1. Must have <a href="https://git-lfs.github.com/" target="_blank" >git-lfs</a> installed and enabled to fetch the prebuilt packages on this repo

2. You will need GCC 8+ or clang 7+ to compile this project, as it makes extensive use of C++17

3. You must install clang-formatter to edit code following this project's code style.

4. Whenever possible, the blocks use NEON optimizations, targetting for the raspberry pi 3 and similar platforms.  
For each block, I am trying my best to mantain at least 1 platform-indepent version.  

## Prebuilt packages <a name="prebuilt_packages"></a>

I have prebuilt OpenCV 4.1 for raspbian 10 with NEON, TBB and VFPV3.  
It's such a pain to build with optimizations that I commited to LFS a .deb package. Enjoy  

## Build instructions <a name="build_instructions"></a>

### First Build <a name="first_build"></a>

cd scripts/

./submodules.sh

./build.sh

### Subsequent builds <a name="subsequent_builds"></a>

cd scripts/

./build.sh

### To clean <a name="clean"></a>

cd scripts/

./clean.sh
