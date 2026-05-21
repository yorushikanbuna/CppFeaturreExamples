/**
 * C++20 Concepts示例
 *
 * 演示内容：
 * - 定义和使用Concepts（概念）
 * - 使用Concepts约束模板
 * - 使用requires表达式
 * - 基于Concepts的函数重载
 */

#include <iostream>
#include <concepts>
#include <vector>
#include <string>
#include <type_traits>

// 1. 基本concept定义
// concept是对模板参数的约束，相当于类型谓词
template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

// 2. 受concept约束的函数
// template <Numeric T> 表示T必须满足Numeric约束
template <Numeric T>
T add(T a, T b) {
    return a + b;
}

// 3. 直接在函数参数中使用concept
void print_numeric(Numeric auto value) {
    std::cout << "数值: " << value << "\n";
}

// 4. 使用requires子句定义更复杂的concept
template <typename T>
concept Iterable = requires(T container) {
    container.begin();   // 必须有begin()方法
    container.end();     // 必须有end()方法
    { *container.begin() } -> std::convertible_to<typename T::value_type>;
};

// 5. 使用Iterable concept
template <Iterable T>
void print_container(const T& container) {
    std::cout << "容器元素: ";
    for (const auto& item : container) {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

// 6. 带嵌套需求的concept
template <typename T>
concept StringLike = requires(T a, T b) {
    { a + b } -> std::same_as<T>;  // a + b 的结果必须是T类型
    { a.size() } -> std::convertible_to<size_t>;  // a.size() 必须能转换为size_t
    requires std::same_as<decltype(a[0]), char&> ||
             std::same_as<decltype(a[0]), const char&>;  // a[0] 必须是char引用
};

// 7. 直接在模板中使用requires表达式
template <typename T>
    requires std::integral<T>  // T必须是整数类型
T square(T x) {
    return x * x;
}

// 8. 组合concept
template <typename T>
concept NumberOrString = Numeric<T> || StringLike<T>;  // Numeric或StringLike

void process(NumberOrString auto value) {
    if constexpr (Numeric<decltype(value)>) {
        std::cout << "处理数值类型: " << value << "\n";
    } else {
        std::cout << "处理字符串类型: " << value << ", 长度: " << value.size() << "\n";
    }
}

int main() {
    std::cout << "=== C++20 Concepts示例 ===\n\n";

    // Numeric concept示例
    std::cout << "1. Numeric concept:\n";
    std::cout << "5 + 7 = " << add(5, 7) << "\n";
    std::cout << "3.14 + 2.71 = " << add(3.14, 2.71) << "\n";
    print_numeric(42);
    std::cout << "\n";

    // Iterable concept示例
    std::cout << "2. Iterable concept:\n";
    std::vector<int> vec = {1, 2, 3, 4, 5};
    print_container(vec);

    std::string str = "Hello";
    print_container(str);
    std::cout << "\n";

    // requires表达式示例
    std::cout << "3. requires表达式:\n";
    std::cout << "5的平方: " << square(5) << "\n\n";

    // 组合concept示例
    std::cout << "4. 组合concept:\n";
    process(100);
    process(std::string("Concepts非常强大"));

    return 0;
}