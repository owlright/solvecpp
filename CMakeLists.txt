cmake_minimum_required(VERSION 3.10)
project(solveCpp)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 发现所有子目录
file(GLOB SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*")
list(REMOVE_ITEM SUBDIRS "include")
list(REMOVE_ITEM SUBDIRS "lib")

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

# 循环添加每个子目录的可执行文件
foreach(SUBDIR ${SUBDIRS})
    message(SUBDIR: ${SUBDIR})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR})

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
file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")

# Iterate over each .cpp file
foreach(SOURCE ${SOURCES})
    # 读取文件内容
    file(READ ${SOURCE} FILE_CONTENT)
    # 获取文件内容的长度
    string(LENGTH "${FILE_CONTENT}" FILE_LENGTH)
    if  (FILE_LENGTH EQUAL 0)
        message(WARNING "File ${SOURCE} is empty")
    else()
        # Get the filename without the extension
        get_filename_component(EXECUTABLE_NAME ${SOURCE} NAME_WE)

        # Create an executable for this .cpp file
        add_executable(${EXECUTABLE_NAME} ${SOURCE})

        # Link required libraries (if any)
        target_link_libraries(${EXECUTABLE_NAME} ${LIBRARY_NAME})
    endif()
endforeach()