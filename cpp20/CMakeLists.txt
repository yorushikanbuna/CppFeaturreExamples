# Configure C++20 standard
# C++20 standard requirements\ntarget_compile_features(concepts PRIVATE cxx_std_20)\ntarget_compile_features(three_way_comparison PRIVATE cxx_std_20)\ntarget_compile_features(ranges PRIVATE cxx_std_20)\ntarget_compile_features(designated_initializers PRIVATE cxx_std_20)\ntarget_compile_features(explicit_bool PRIVATE cxx_std_20)

# List of example targets
set(CPP20_TARGETS)

# Concepts example
add_executable(concepts concepts.cpp)
list(APPEND CPP20_TARGETS concepts)

# Three-way comparison example
add_executable(three_way_comparison three_way_comparison.cpp)
list(APPEND CPP20_TARGETS three_way_comparison)

# Ranges example
add_executable(ranges ranges.cpp)
list(APPEND CPP20_TARGETS ranges)

# Designated initializers example
add_executable(designated_initializers designated_initializers.cpp)
list(APPEND CPP20_TARGETS designated_initializers)

# Explicit(bool) example
add_executable(explicit_bool explicit_bool.cpp)
list(APPEND CPP20_TARGETS explicit_bool)