cmake_minimum_required(VERSION 3.10)
project(cpp20)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            target_compile_options(${EXECUTABLE_NAME} PRIVATE -fcoroutines)
        endif()
        if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            target_compile_options(${EXECUTABLE_NAME} PRIVATE /await)
        endif()
    endif()
endforeach()