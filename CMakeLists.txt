cmake_minimum_required (VERSION 3.0)
cmake_policy(SET CMP0048 NEW)
project (nss-zero-dns VERSION 1.1)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  message (FATAL_ERROR "Linux is not supported by now. Feel free to contribute.")
endif (CMAKE_SYSTEM_NAME STREQUAL "Linux")

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Modules")
set (CMAKE_C_FLAGS_RELEASE "-O3")

find_package (ZeroMQ REQUIRED)

set (ALLOW_FILE "/etc/zerodns.allow"
  CACHE FILEPATH "Optional allow file")
set (ZDNS_SOCKET "ipc:///var/run/zero-dns/zero-dns"
  CACHE STRING "Address of ZeroDNS query endpoint")

add_subdirectory (src)
