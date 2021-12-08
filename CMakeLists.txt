cmake_minimum_required(VERSION 3.11)
project(PocoServiceExample)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MACOSX_RPATH OFF)


##include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
##conan_basic_setup()

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /usr/local/Cellar/poco/1.11.1/lib/cmake/Poco)
find_package(Poco REQUIRED ActiveRecord Data Foundation)


set(TARGET poco_service_example)

add_subdirectory(persistence)

add_executable(${TARGET})
target_sources(${TARGET} PRIVATE main.cpp)
target_link_libraries(${TARGET} PRIVATE ${CONAN_LIBS} persistence)
