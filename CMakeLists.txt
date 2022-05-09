cmake_minimum_required(VERSION 3.5)
project(curl_crawler)

set(CMAKE_CXX_STANDARD 20)

add_executable(testbinary main.cpp src/pool.cpp src/bounded_buffer.cpp)

target_compile_features(testbinary PRIVATE cxx_std_20)
target_include_directories(testbinary PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)
