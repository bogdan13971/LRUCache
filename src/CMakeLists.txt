project(LRUCache)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "../include/*.hpp")
add_library(${PROJECT_NAME} ${SOURCES} "Source.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE "../include")

source_group(TREE "include" FILES ${SOURCES})