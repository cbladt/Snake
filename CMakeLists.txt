# Setup project.
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(Snake LANGUAGES CXX)
SET(CMAKE_VERBOSE_MAKEFILE ON)

# Some compiler options.
set(CMAKE_CXX_STANDARD 14)
add_definitions(-DGTEST_LANGUAGE_CXX11)

# Include dirs.
include_directories(
    .
    )

# Sources.
list(APPEND SRC_LIST
        main.cpp
        Position.cpp
    )

# Sources.
list(APPEND SRC_LIST
        Snake/Snake.cpp
    )

# Setup exe file.
add_executable(${PROJECT_NAME}
        ${SRC_LIST}
    )
