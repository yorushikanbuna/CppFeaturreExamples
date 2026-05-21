# Configure C++11 standard
# C++11 standard requirements\ntarget_compile_features(auto_type PRIVATE cxx_std_11)\ntarget_compile_features(range_based_for PRIVATE cxx_std_11)\ntarget_compile_features(lambda_expressions PRIVATE cxx_std_11)\ntarget_compile_features(smart_pointers PRIVATE cxx_std_11)\ntarget_compile_features(nullptr_usage PRIVATE cxx_std_11)\ntarget_compile_features(move_semantics PRIVATE cxx_std_11)\ntarget_compile_features(thread_basics PRIVATE cxx_std_11)\ntarget_compile_features(constexpr_usage PRIVATE cxx_std_11)\ntarget_compile_features(delegating_constructors PRIVATE cxx_std_11)\ntarget_compile_features(override_final PRIVATE cxx_std_11)

# List of example targets
set(CPP11_TARGETS)

# Auto type deduction example
add_executable(auto_type auto_type.cpp)
list(APPEND CPP11_TARGETS auto_type)

# Range-based for loop example
add_executable(range_based_for range_based_for.cpp)
list(APPEND CPP11_TARGETS range_based_for)

# Lambda expressions example
add_executable(lambda_expressions lambda_expressions.cpp)
list(APPEND CPP11_TARGETS lambda_expressions)

# Smart pointers example
add_executable(smart_pointers smart_pointers.cpp)
list(APPEND CPP11_TARGETS smart_pointers)

# nullptr usage example
add_executable(nullptr_usage nullptr_usage.cpp)
list(APPEND CPP11_TARGETS nullptr_usage)

# Move semantics example
add_executable(move_semantics move_semantics.cpp)
list(APPEND CPP11_TARGETS move_semantics)

# Thread basics example
add_executable(thread_basics thread_basics.cpp)
list(APPEND CPP11_TARGETS thread_basics)

# constexpr usage example
add_executable(constexpr_usage constexpr_usage.cpp)
list(APPEND CPP11_TARGETS constexpr_usage)

# Delegating constructors example
add_executable(delegating_constructors delegating_constructors.cpp)
list(APPEND CPP11_TARGETS delegating_constructors)

# override/final example
add_executable(override_final override_final.cpp)
list(APPEND CPP11_TARGETS override_final)