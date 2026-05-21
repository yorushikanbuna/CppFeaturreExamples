/**
 * C++14 扩展constexpr示例
 *
 * 演示内容：
 * - 扩展的constexpr函数（C++14）
 * - constexpr if语句
 * - constexpr容器
 * - 实际应用
 */

#include <iostream>
#include <array>

// C++14扩展的constexpr函数 - 可以包含循环、多条语句
constexpr int factorial(int n) {
    if (n <= 1) return 1;
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// 另一个扩展的constexpr函数
constexpr int sum_array(const int* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum;
}

// 带局部变量的constexpr函数
constexpr int maximum(int a, int b) {
    int result = (a > b) ? a : b;
    return result;
}

int main() {
    std::cout << "=== C++14 扩展constexpr示例 ===\n\n";

    // 1. 编译时执行的扩展constexpr函数
    std::cout << "1. 扩展constexpr函数:\n";
    constexpr int fact5 = factorial(5);
    constexpr int max_val = maximum(42, 100);

    std::cout << "factorial(5) = " << fact5 << " (编译时计算)\n";
    std::cout << "maximum(42, 100) = " << max_val << " (编译时计算)\n\n";

    // 2. constexpr与数组
    std::cout << "2. constexpr与数组:\n";
    constexpr int numbers[] = {1, 2, 3, 4, 5};
    constexpr int array_sum = sum_array(numbers, 5);

    std::cout << "{1,2,3,4,5}的和 = " << array_sum << " (编译时计算)\n\n";

    // 3. constexpr容器
    std::cout << "3. constexpr容器:\n";
    constexpr std::array<int, 5> arr = {{10, 20, 30, 40, 50}};

    // 在编译时访问元素
    constexpr int first = arr[0];
    constexpr int last = arr[arr.size() - 1];

    std::cout << "第一个元素: " << first << " (编译时)\n";
    std::cout << "最后一个元素: " << last << " (编译时)\n\n";

    // 4. constexpr函数的运行时使用
    std::cout << "4. 运行时使用constexpr函数:\n";
    int runtime_value = 6;
    int runtime_fact = factorial(runtime_value);  // 仍在运行时计算

    std::cout << "factorial(6) = " << runtime_fact << " (运行时计算)\n\n";

    // 5. 实际应用：编译时查表
    std::cout << "5. 编译时查表:\n";

    // 在编译时生成阶乘表
    constexpr std::array<int, 8> factorial_table = {{
        factorial(0), factorial(1), factorial(2), factorial(3),
        factorial(4), factorial(5), factorial(6), factorial(7)
    }};

    std::cout << "阶乘表（编译时生成）:\n";
    for (size_t i = 0; i < factorial_table.size(); ++i) {
        std::cout << i << "! = " << factorial_table[i] << "\n";
    }
    std::cout << "\n";

    return 0;
}