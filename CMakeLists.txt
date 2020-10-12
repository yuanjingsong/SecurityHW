cmake_minimum_required(VERSION 3.2)

project(modern_crypto)

set (CMKAE_CXX_STANDARD 17)

add_executable(modern_crypto demo.cpp DES.cpp AES.cpp crypto.cpp)
