cmake_minimum_required (VERSION 2.6)
cmake_policy(SET CMP0048 NEW)

project (nss-zero-dns VERSION 1.0)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Modules")
set (CMAKE_C_FLAGS_RELEASE "-O3")

find_package (ZeroMQ REQUIRED)

set (ALLOW_FILE "/etc/zerodns.allow" CACHE FILEPATH "Optional allow file")
set (ZDNS_SOCKET "tcp://localhost:5355" CACHE STRING "Address of ZeroDNS query endpoint")

add_subdirectory (src)
