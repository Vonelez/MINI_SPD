
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

project(MINI_SPD)

set (CMAKE_CXX_STANDARD 17)

# This fixes a weird "invalid version number in '-mmacosx-version-min=11.1'" error
# when using Xcode.
set (CMAKE_OSX_DEPLOYMENT_TARGET 10.15)

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

ROOT_GENERATE_DICTIONARY(G__BmnSiliconDigit BmnSiliconDigit.h MODULE minispd)

target_link_libraries(minispd Core RIO Tree Hist)
