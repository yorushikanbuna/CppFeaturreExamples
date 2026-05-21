/**
 * C++11 auto类型推导示例
 *
 * 演示内容：
 * - 基本auto类型推导
 * - auto与迭代器配合使用
 * - auto与函数返回类型（尾随返回类型）
 * - decltype用于精确类型保留
 */

#include <iostream>
#include <vector>
#include <map>

// 使用尾随返回类型（trailing return type）的函数模板
// -> decltype(t * u)表示返回类型为t * u的结果类型
template<typename T, typename U>
auto multiply(T t, U u) -> decltype(t * u) {
    return t * u;
}

int main() {
    std::cout << "=== C++11 auto类型推导示例 ===\n\n";

    // 1. 基本auto推导
    // 编译器根据初始化值自动推导变量类型
    auto i = 42;               // 推导为int
    auto d = 3.14;             // 推导为double
    auto s = "Hello";          // 推导为const char*
    auto v = std::vector<int>(); // 推导为std::vector<int>

    std::cout << "auto推导的类型:\n";
    std::cout << "i = " << i << " (类型: int)\n";
    std::cout << "d = " << d << " (类型: double)\n";
    std::cout << "s = " << s << " (类型: const char*)\n";

    // 2. auto与迭代器配合
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "\nVector元素 (使用迭代器): ";
    // 使用auto自动推导迭代器类型
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // 3. 范围for与auto配合
    std::cout << "Vector元素 (范围for): ";
    for (const auto& num : numbers) {
        // const auto&表示常量引用，避免拷贝
        std::cout << num << " ";
    }
    std::cout << "\n";

    // 4. auto与复杂表达式
    std::cout << "\nauto与复杂表达式:\n";
    std::map<std::string, int> scores = {{"Alice", 90}, {"Bob", 85}};
    for (const auto& pair : scores) {
        // pair是std::pair<const std::string, int>
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    // 5. decltype用于精确类型保留
    std::cout << "\ndec typeof示例:\n";
    int x = 10;
    int y = 20;
    // decltype返回变量的精确类型（包括引用、const等限定符）
    decltype(x) z = x + y;  // z的类型精确为int
    std::cout << "z (使用decltype声明): " << z << "\n";

    // 6. 尾随返回类型函数
    std::cout << "\n尾随返回类型函数:\n";
    auto result = multiply(5, 3.14);
    // multiply返回类型被推导为double
    std::cout << "multiply(5, 3.14) = " << result << "\n";

    return 0;
}