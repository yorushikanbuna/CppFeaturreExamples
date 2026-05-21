cmake_minimum_required(VERSION 3.10)
project(CppFeatureExamples LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add subdirectories for each C++ standard
add_subdirectory(cpp11)
add_subdirectory(cpp14)
add_subdirectory(cpp17)
add_subdirectory(cpp20)

# Create a target that builds all examples
add_custom_target(all_examples DEPENDS
    ${CPP11_TARGETS}
    ${CPP14_TARGETS}
    ${CPP17_TARGETS}
    ${CPP20_TARGETS}
)