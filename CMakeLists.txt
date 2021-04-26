
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

project(MINI_SPD)

set (CMAKE_CXX_STANDARD 17)

find_package(ROOT REQUIRED)

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIRS}
${CMAKE_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/src
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES ${ROOT_LIBRARY_DIR})

link_directories( ${LINK_DIRECTORIES})

add_executable(minispd main.cpp)

target_sources(minispd PUBLIC src/DataTaking.cpp src/BmnSiliconDigit.cxx)

target_link_libraries(minispd Core RIO Tree Hist)