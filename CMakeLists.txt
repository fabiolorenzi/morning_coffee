cmake_minimum_required(VERSION 3.16)

project(MorningCoffee LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

list(APPEND CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/Qt6")
find_package(Qt6 COMPONENTS Core Gui Widgets Sql Network REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/classes/AddSourceWidget.cpp
    src/classes/Button.cpp
    src/classes/DatabaseManager.cpp
    src/classes/DefaultWidget.cpp
    src/classes/FormMessage.cpp
    src/classes/MainWindow.cpp
    src/classes/ManageSourcesWidget.cpp
    src/classes/MenuBar.cpp
    src/classes/Spinner.cpp
    src/classes/ViewNewBlogsWidget.cpp
    src/functions/WidgetHelper.cpp
    assets/resources.qrc
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Sql Qt6::Network)