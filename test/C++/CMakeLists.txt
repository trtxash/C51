cmake_minimum_required(VERSION 3.28.3) # Minimum version of CMake required
project(
    Template # Name of the project
    VERSION 0.0.1 # Version number of the project
    DESCRIPTION "A template project for C++" # Short description of the project
    HOMEPAGE_URL "https://github.com/trtxash/VS-Code-C" # Homepage URL of the project
    LANGUAGES CXX # Languages used in the project
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # 开启编译建议

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin) # Set the output directory for the executable files
set(User_Dir ${CMAKE_SOURCE_DIR}/src/user)
set(Temptest_Dir ${CMAKE_SOURCE_DIR}/temptest)

add_subdirectory(src) # Add subdirectory containing source files
add_subdirectory(temptest)