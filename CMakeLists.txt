cmake_minimum_required (VERSION 3.16)
project (zadaca)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED) 

add_subdirectory (third_party)

add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
)

set(STUDENTS_FOLDER "${PROJECT_SOURCE_DIR}/studenti/" CACHE PATH "students location")

add_subdirectory(studenti)


