cmake_minimum_required(VERSION 2.8.9)
project(xmltohtmltable)

set(XMLToHTMLTable_SRCS XMLToHTMLTable.cpp main.cpp)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Xml REQUIRED)
find_package(Qt5Core REQUIRED)

add_executable(xmltohtmltable ${XMLToHTMLTable_SRCS})
qt5_use_modules(xmltohtmltable Xml)
target_link_libraries(xmltohtmltable ${QT_QTCORE_LIBRARY})
