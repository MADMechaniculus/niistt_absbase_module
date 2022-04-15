cmake_minimum_required(VERSION 3.1)
project(niistt_absbase_module VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

add_library(${PROJECT_NAME} SHARED
    abstractbasemodule.cpp
    telemetryflow.cpp
    telemetrytypes.cpp
    )

if (WIN32)
    set(BOOST_INCLUDEDIR        C:\\include\\boost_1_76_0)
    set(BOOST_LIBRARYDIR        C:\\libs\\boost_1.76.0)
elseif (UNIX)
    set(BOOST_INCLUDEDIR        /usr/include/boostlibs/boost_1_76_0)
    set(BOOST_LIBRARYDIR        /usr/lib/boost/1_76_0)
else ()
    message( FATAL_ERROR "Unknown OS!")
endif ()

target_include_directories(${PROJECT_NAME} PUBLIC ${BOOST_INCLUDEDIR} PRIVATE .)
target_link_directories(${PROJECT_NAME} PUBLIC ${BOOST_LIBRARYDIR})

find_package(Boost COMPONENTS system thread REQUIRED)
find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
    
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
