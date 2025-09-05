cmake_minimum_required(VERSION 3.16)

project(MorningCoffee LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets Sql Network REQUIRED)

set(SOURCES
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
    src/classes/TutorialDialog.cpp
    src/classes/ViewNewBlogsWidget.cpp
    src/classes/ViewNewPatreonsWidget.cpp
    src/classes/ViewNewVideosWidget.cpp
    src/classes/ViewSummaryWidget.cpp
    src/functions/SecurityHelper.cpp
    src/functions/WidgetHelper.cpp
    assets/resources.qrc
)

if (WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES} appicon.rc)
    set(CMAKE_WIN32_EXECUTABLE ON)
else()
    add_executable(${PROJECT_NAME} ${SOURCES})
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Sql
        Qt6::Network
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)