# Add all source files in the current directory to the library
file(GLOB LIB_SOURCES *.cpp)

# Create the library target
target_sources(${LIBRARY_NAME} PRIVATE ${LIB_SOURCES})
