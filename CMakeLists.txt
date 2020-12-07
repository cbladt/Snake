cmake_minimum_required(VERSION 3.5)

project(Snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(PNG REQUIRED)
find_package(X11 REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)


add_executable(Snake main.cpp)

target_include_directories(Snake PUBLIC ${PNG_INCLUDE_DIR})

target_link_libraries(
    Snake
    ${OPENGL_gl_LIBRARY}
    ${GLUT_LIBRARIES}
    ${PNG_LIBRARY}
    ${X11_LIBRARIES}
    Threads::Threads
)
