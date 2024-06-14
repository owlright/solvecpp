cmake_minimum_required(VERSION 3.10)
project(solveCpp)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()
# 发现所有子目录
file(GLOB SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*")
list(REMOVE_ITEM SUBDIRS "include")
list(REMOVE_ITEM SUBDIRS "lib")
list(REMOVE_ITEM SUBDIRS "cpp20")
list(REMOVE_ITEM SUBDIRS "cmake-build")
list(REMOVE_ITEM SUBDIRS ".vscode")
list(REMOVE_ITEM SUBDIRS ".vs")
list(REMOVE_ITEM SUBDIRS "out")
list(REMOVE_ITEM SUBDIRS ".git")
list(REMOVE_ITEM SUBDIRS "build")
# Include all .hpp files in the include/ directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(LIBRARY_NAME "${PROJECT_NAME}")
# Add source files in the lib/ directory
file(GLOB LIBSOURCES ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp)
# Create the library
add_library(${LIBRARY_NAME} ${LIBSOURCES})

add_subdirectory(lib/graph)
# 循环添加每个子目录的可执行文件
foreach(SUBDIR ${SUBDIRS})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR})
        message(SUBDIR: ${SUBDIR})
        # 设置可执行文件名称
        set(EXECUTABLE_NAME ${SUBDIR})

        # 添加子目录中的源文件
        file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR}/*.cpp)
        if (SOURCES)
            # 创建可执行文件
            add_executable(${EXECUTABLE_NAME} ${SOURCES})
            # 链接所需库(如有需要)
            target_link_libraries(${EXECUTABLE_NAME} ${LIBRARY_NAME})
        endif()
    endif()
endforeach()

# Find all .cpp files in the current directory
add_executable(topoSort topoSort.cpp)
add_executable(findMaxN findMaxN.cpp)
add_executable(employee_management employee_management.c)
add_subdirectory(cpp20)

add_executable(testgraph test-graph.cpp)
add_executable(cppmemo cppmemo.cpp)
add_executable(sharedptr sharedptr.cpp)
# target_include_directories(testgraph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/graph)
# target_link_libraries(testgraph ${LIBRARY_NAME})