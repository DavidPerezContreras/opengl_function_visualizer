cmake_minimum_required(VERSION 3.10)

project(hello_world VERSION 0.1.0 LANGUAGES C CXX)

# ✅ C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} src/main.cpp)


find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)


target_link_libraries(${PROJECT_NAME} PRIVATE
    glad::glad
    glfw
    glm::glm
)


# 🗂️ Source files (optional if you expand later)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})


# move shaders folder to build/
file(GLOB SHADERS "${CMAKE_SOURCE_DIR}/shaders/*.glsl")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/shaders)


# Enable sanitizers or runtime checks based on compiler
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    message(STATUS "Clang/GCC detected — enabling AddressSanitizer")
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address -g)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
elseif(MSVC)
    message(STATUS "MSVC detected — enabling runtime checks")
    target_compile_options(${PROJECT_NAME} PRIVATE /Zi /Od /RTC1)
    target_link_options(${PROJECT_NAME} PRIVATE /DEBUG)
endif()

if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
    )
endif()
