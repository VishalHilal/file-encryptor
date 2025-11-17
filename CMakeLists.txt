cmake_minimum_required(VERSION 3.10)
project(file_encryptor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBSODIUM REQUIRED libsodium)

include_directories(${LIBSODIUM_INCLUDE_DIRS})
link_directories(${LIBSODIUM_LIBRARY_DIRS})

add_executable(file-encryptor
    src/main.cpp
    src/Crypto.cpp
    src/FileUtil.cpp
)

target_compile_definitions(file-encryptor PRIVATE SODIUM_STATIC=0)
target_link_libraries(file-encryptor PRIVATE ${LIBSODIUM_LIBRARIES})
