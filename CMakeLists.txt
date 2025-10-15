cmake_minimum_required(VERSION 3.16)

project(TinyRedis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(tinyredis_lib
    src/datastore.cpp
    src/server.cpp
    src/resp.cpp
    src/command_router.cpp
)

target_include_directories(tinyredis_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(tinyredis_lib PUBLIC cxx_std_17)

add_executable(tinyredis
    src/main.cpp
)

target_link_libraries(tinyredis PRIVATE tinyredis_lib)
