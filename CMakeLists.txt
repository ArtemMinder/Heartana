cmake_minimum_required(VERSION 3.14)
project(Heartana)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Charts)
find_package(Qt5PrintSupport)

include_directories (${PROJECT_SOURCE_DIR})
  ADD_LIBRARY(Qcustomplot
   qcustomplot.cpp
   qcustomplot.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND THIRD_PARTY_LIBS Qcustomplot Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Charts Qt5::PrintSupport)

add_executable(${PROJECT_NAME} qcustomplot main.cpp logic.cpp mainwindow.cpp
     registration.cpp settings.cpp logic.h mainwindow.h patient.h
     registration.h settings.h dialog.ui mainwindow.ui
     registration.ui settings.ui qcustomplot.h qcustomplot.cpp)

target_link_libraries(${PROJECT_NAME}
        Qcustomplot
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        Qt5::Charts
        Qt5::PrintSupport
        )
