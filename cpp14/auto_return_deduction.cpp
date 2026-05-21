/**
 * C++14 自动返回类型推导示例
 *
 * 演示内容：
 * - 使用auto推导函数返回类型
 * - 泛型Lambda（auto参数）
 * - 扩展的constexpr函数
 * - 二进制字面量和数字分隔符
 */

#include <iostream>
#include <vector>
#include <string>

// 使用自动返回类型推导的函数
auto calculate(int a, int b) {
    return a + b;  // 返回类型推导为int
}

// 使用尾随返回类型的函数模板
template<typename T, typename U>
auto multiply(T t, U u) -> decltype(t * u) {
    return t * u;  // 返回类型是t * u的结果类型
}

// 用于比较的普通函数
int traditional_add(int a, int b) {
    return a + b;
}

int main() {
    std::cout << "=== C++14 自动返回类型推导示例 ===\n\n";

    // 1. 基本自动返回类型推导
    std::cout << "1. 基本自动返回类型推导:\n";
    auto result1 = calculate(5, 3);
    std::cout << "calculate(5, 3) = " << result1 << "\n";

    auto result2 = multiply(4.5, 2);
    std::cout << "multiply(4.5, 2) = " << result2 << "\n\n";

    // 2. 自动返回类型的Lambda
    std::cout << "2. 自动返回类型的Lambda:\n";
    auto lambda = [](auto x, auto y) {
        return x + y;
    };

    std::cout << "lambda(5, 3) = " << lambda(5, 3) << "\n";
    std::cout << "lambda(3.14, 2.71) = " << lambda(3.14, 2.71) << "\n";
    std::cout << "lambda(std::string(\"Hello\"), std::string(\" World\")) = "
              << lambda(std::string("Hello"), std::string(" World")) << "\n\n";

    // 3. 自动返回类型的模板Lambda
    std::cout << "3. 自动返回类型的模板Lambda:\n";
    auto template_lambda = [](const auto& container) -> auto {
        return container.size();
    };

    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::string str = "Hello C++14";

    std::cout << "Vector大小: " << template_lambda(vec) << "\n";
    std::cout << "String长度: " << template_lambda(str) << "\n\n";

    return 0;
}