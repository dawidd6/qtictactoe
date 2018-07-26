cmake_minimum_required(VERSION 3.5)

project(qtictactoe)

file(GLOB SOURCES src/*.cpp)

find_package(PkgConfig REQUIRED)

pkg_check_modules(QT5WIDGETS REQUIRED Qt5Widgets>=5.5)
pkg_check_modules(QT5NETWORK REQUIRED Qt5Network>=5.5)

include_directories(${QT5WIDGETS_INCLUDE_DIRS} ${QT5NETWORK_INCLUDE_DIRS})

link_directories(${QT5WIDGETS_LIBRARY_DIRS} ${QT5NETWORK_LIBRARY_DIRS})

add_definitions("-std=c++11 -fPIC" ${QT5WIDGETS_CFLAGS_OTHER})

include_directories(include)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${QT5WIDGETS_LIBRARIES} ${QT5NETWORK_LIBRARIES})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES data/${PROJECT_NAME}.desktop DESTINATION share/applications RENAME ${PROJECT_NAME}.desktop)
