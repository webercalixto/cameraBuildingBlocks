cmake_minimum_required(VERSION 3.8)
project (ninjaDaemon)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/arm-linux-gnueabihf-g++)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -mtune=cortex-a53 -mcpu=cortex-a53 -mfloat-abi=hard -mfpu=neon-fp-armv8 -mneon-for-64bits")

set(NINJADAEMON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third-party/ninjaDaemon")

set(LIBPATH_PISTACHE "${NINJADAEMON_DIR}/third-party/pistache/build/src/")
set(INC_PISTACHE "${NINJADAEMON_DIR}/third-party/pistache/include/")
set(INC_RAPIDJSON "${NINJADAEMON_DIR}/third-party/rapidjson/include/")
set(INC_INIPP "${NINJADAEMON_DIR}/third-party/inipp/")
set(INC_NINJADAEMON "${NINJADAEMON_DIR}/include/")


message(${INC_PISTACHE})
LINK_DIRECTORIES(${LIBPATH_PISTACHE})

find_package( Threads REQUIRED )
#find_package( OpenCV REQUIRED )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${INC_NINJADAEMON} ${INC_PISTACHE} ${INC_RAPIDJSON} ${INC_INIPP})

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB SRC_SHOWIMG "${CMAKE_CURRENT_SOURCE_DIR}/examples/showImg/*.cpp")

add_executable( showImg ${SOURCES} ${SRC_SHOWIMG})

target_link_libraries(showImg PUBLIC 
	Threads::Threads 
	stdc++fs
	libpistache.a)
#${OpenCV_LIBS} 