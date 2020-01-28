#set(CMAKE_C_COMPILER_WORKS)

# Define our host system
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
#set(CMAKE_SYSTEM_VERSION 1)

set(TOOLS_BASE ${CMAKE_CURRENT_LIST_DIR}/x-tools/armv6-rpi-linux-gnueabi)

set(CMAKE_SYSROOT ${TOOLS_BASE}/armv6-rpi-linux-gnueabi/sysroot)

# Define the cross compiler locations
set(CMAKE_C_COMPILER ${TOOLS_BASE}/bin/armv6-rpi-linux-gnueabi-gcc)
set(CMAKE_CXX_COMPILER ${TOOLS_BASE}/bin/armv6-rpi-linux-gnueabi-g++)

set(CMAKE_FIND_ROOT_PATH ${TOOLS_BASE}/armv6-rpi-linux-gnueabi/sysroot)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
