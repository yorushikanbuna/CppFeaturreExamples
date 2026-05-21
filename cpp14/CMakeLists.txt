# Configure C++14 standard
# C++14 standard requirements\ntarget_compile_features(generic_lambdas PRIVATE cxx_std_14)\ntarget_compile_features(auto_return_deduction PRIVATE cxx_std_14)\ntarget_compile_features(decltype_auto PRIVATE cxx_std_14)\ntarget_compile_features(binary_literals PRIVATE cxx_std_14)\ntarget_compile_features(digit_separators PRIVATE cxx_std_14)\ntarget_compile_features(make_unique PRIVATE cxx_std_14)\ntarget_compile_features(extended_constexpr PRIVATE cxx_std_14)

# List of example targets
set(CPP14_TARGETS)

# Generic lambdas example
add_executable(generic_lambdas generic_lambdas.cpp)
list(APPEND CPP14_TARGETS generic_lambdas)

# Auto return type deduction example
add_executable(auto_return_deduction auto_return_deduction.cpp)
list(APPEND CPP14_TARGETS auto_return_deduction)

# decltype(auto) example
add_executable(decltype_auto decltype_auto.cpp)
list(APPEND CPP14_TARGETS decltype_auto)

# Binary literals example
add_executable(binary_literals binary_literals.cpp)
list(APPEND CPP14_TARGETS binary_literals)

# Digit separators example
add_executable(digit_separators digit_separators.cpp)
list(APPEND CPP14_TARGETS digit_separators)

# make_unique example
add_executable(make_unique make_unique.cpp)
list(APPEND CPP14_TARGETS make_unique)

# Extended constexpr example
add_executable(extended_constexpr extended_constexpr.cpp)
list(APPEND CPP14_TARGETS extended_constexpr)