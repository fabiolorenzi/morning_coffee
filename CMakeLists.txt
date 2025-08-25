cmake_minimum_required(VERSION 3.16)

project(MorningCoffee LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

list(APPEND CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/Qt6")
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/components/MainWindow.cpp
    src/components/MainWindow.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)