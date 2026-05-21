# Configure C++17 standard
# C++17 standard requirements\ntarget_compile_features(structured_bindings PRIVATE cxx_std_17)\ntarget_compile_features(if_constexpr PRIVATE cxx_std_17)\ntarget_compile_features(optional_usage PRIVATE cxx_std_17)\ntarget_compile_features(variant_usage PRIVATE cxx_std_17)\ntarget_compile_features(any_usage PRIVATE cxx_std_17)\ntarget_compile_features(filesystem_demo PRIVATE cxx_std_17)\ntarget_compile_features(string_view PRIVATE cxx_std_17)\ntarget_compile_features(parallel_algorithms PRIVATE cxx_std_17)

# List of example targets
set(CPP17_TARGETS)

# Structured bindings example
add_executable(structured_bindings structured_bindings.cpp)
list(APPEND CPP17_TARGETS structured_bindings)

# if constexpr example
add_executable(if_constexpr if_constexpr.cpp)
list(APPEND CPP17_TARGETS if_constexpr)

# Optional usage example
add_executable(optional_usage optional_usage.cpp)
list(APPEND CPP17_TARGETS optional_usage)

# Variant usage example
add_executable(variant_usage variant_usage.cpp)
list(APPEND CPP17_TARGETS variant_usage)

# Any usage example
add_executable(any_usage any_usage.cpp)
list(APPEND CPP17_TARGETS any_usage)

# Filesystem demo example
add_executable(filesystem_demo filesystem_demo.cpp)
list(APPEND CPP17_TARGETS filesystem_demo)

# String view example
add_executable(string_view string_view.cpp)
list(APPEND CPP17_TARGETS string_view)

# Parallel algorithms example
add_executable(parallel_algorithms parallel_algorithms.cpp)
list(APPEND CPP17_TARGETS parallel_algorithms)