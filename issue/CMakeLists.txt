cmake_minimum_required(VERSION 3.19)
project(issue)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\mingw81_64\\bin")

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Charts REQUIRED)

add_executable(issue main.cpp domain.cpp domain.h repository.h service.cpp service.h gui.cpp gui.h user_table_model.cpp user_table_model.h)

target_link_libraries(issue Qt5::Core)
target_link_libraries(issue Qt5::Widgets)
target_link_libraries(issue Qt5::Quick)
target_link_libraries(issue Qt5::Charts)