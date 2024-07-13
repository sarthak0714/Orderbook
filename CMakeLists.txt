cmake_minimum_required(VERSION 3.10)

project(OrderbookProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Orderbook 
    src/main.cpp
    src/Orderbook.cpp
)

target_include_directories(Orderbook PUBLIC 
    ${PROJECT_SOURCE_DIR}/src
)