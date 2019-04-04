cmake_minimum_required(VERSION 3.12)
project(TetrisCam)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5Widgets REQUIRED)
find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLU REQUIRED)


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin)

file(GLOB_RECURSE SOURCE_FILES src/*)
add_executable(prog ${SOURCE_FILES} src/MainWindow.cpp src/main.cpp src/TetrisWidget.cpp src/TetrisWidget.hpp src/VideoWidget.cpp src/VideoWidget.hpp)


target_link_libraries(prog Qt5::Widgets)
target_link_libraries(prog ${OpenCV_LIBS})
target_link_libraries(prog OpenGL)
target_link_libraries(prog GLU)

# For autocompletion during developpement
include_directories(cmake-build-debug/prog_autogen/include)
include_directories(src)
include_directories(ui)