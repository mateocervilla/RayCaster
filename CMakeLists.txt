cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME RayCaster)

if (NOT DEFINED SFML_PATH)
    message(FATAL_ERROR "Please specify the path to SFML directory.")
endif()

project(${PROJECT_NAME})

# Set the source directory
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
# List of all .cpp files in the src directory
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")
include_directories(${OpenCV_INCLUDE_DIRS} "${CMAKE_SOURCE_DIR}/include")

if(WIN32)
    if(NOT SHARED)
        set(SFML_STATIC_LIBRARIES TRUE)
    endif()
    set(SFML_DIR ${SFML_PATH}\\lib\\cmake\\SFML)
    find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)
endif()

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_PATH}/include)
target_link_directories(${PROJECT_NAME} PUBLIC ${SFML_PATH}/lib)

if(SHARED)
    target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)
else()
    if(WIN32)
        target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics opengl32 winmm gdi32)
    else()
        target_link_libraries(${PROJECT_NAME} sfml-graphics-s sfml-graphics-s sfml-window-s sfml-system-s X11 Xrandr Xcursor udev)
    endif()
endif()
