/**
 * C++17 std::variant示例
 *
 * 演示内容：
 * - std::variant用于类型安全的联合体
 * - 使用std::visit访问变量
 * - 在单个容器中处理多种类型
 * - 使用变量进行错误处理
 */

#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <map>

// std::visit的访问器
struct Printer {
    void operator()(int value) const {
        std::cout << "整数: " << value << "\n";
    }

    void operator()(double value) const {
        std::cout << "双精度: " << value << "\n";
    }

    void operator()(const std::string& value) const {
        std::cout << "字符串: " << value << "\n";
    }
};

// 返回variant的函数
std::variant<int, std::string> parseInput(const std::string& input) {
    // 尝试解析为整数
    try {
        return std::stoi(input);
    } catch (...) {
        // 如果解析失败，返回字符串
        return input;
    }
}

// 表示不同形状的variant
using Shape = std::variant<struct Circle, struct Rectangle, struct Triangle>;

struct Circle {
    double radius;
};

struct Rectangle {
    double width, height;
};

struct Triangle {
    double base, height;
};

// 计算面积的访问器
struct AreaCalculator {
    double operator()(const Circle& c) const {
        return 3.14159 * c.radius * c.radius;
    }

    double operator()(const Rectangle& r) const {
        return r.width * r.height;
    }

    double operator()(const Triangle& t) const {
        return 0.5 * t.base * t.height;
    }
};

int main() {
    std::cout << "=== C++17 std::variant示例 ===\n\n";

    // 1. 基本variant用法
    std::cout << "1. 基本variant用法:\n";
    std::variant<int, double, std::string> var1 = 42;
    std::variant<int, double, std::string> var2 = 3.14;
    std::variant<int, double, std::string> var3 = "Hello";

    std::visit(Printer{}, var1);
    std::visit(Printer{}, var2);
    std::visit(Printer{}, var3);
    std::cout << "\n";

    // 2. 改变variant的值
    std::cout << "2. 改变variant的值:\n";
    var1 = "现在我是字符串";
    var2 = 100;
    std::visit(Printer{}, var1);
    std::visit(Printer{}, var2);
    std::cout << "\n";

    // 3. 类型检查和访问
    std::cout << "3. 类型检查和访问:\n";
    if (std::holds_alternative<int>(var2)) {
        std::cout << "var2是int: " << std::get<int>(var2) << "\n";
    }

    // 使用get_if安全访问
    if (const auto* str = std::get_if<std::string>(&var1)) {
        std::cout << "var1是string: " << *str << "\n";
    }
    std::cout << "\n";

    // 4. 返回variant的函数
    std::cout << "4. 返回variant的函数:\n";
    auto result1 = parseInput("123");
    auto result2 = parseInput("3.14");  // 会被视为字符串，因为stoi在"."处停止
    auto result3 = parseInput("Hello");

    std::visit(Printer{}, result1);
    std::visit(Printer{}, result2);
    std::visit(Printer{}, result3);
    std::cout << "\n";

    // 5. 容器中的variant
    std::cout << "5. 容器中的variant:\n";
    std::vector<std::variant<int, double, std::string>> values = {
        42, 3.14, "Hello", 100, "World"
    };

    for (const auto& value : values) {
        std::visit(Printer{}, value);
    }
    std::cout << "\n";

    // 6. variant的数学运算
    std::cout << "6. variant的数学运算:\n";
    std::variant<int, double> num1 = 10;
    std::variant<int, double> num2 = 3.5;

    // 用于加法的lambda访问器
    auto add_visitor = [](const auto& a, const auto& b) -> std::variant<int, double> {
        if constexpr (std::is_same_v<decltype(a), int> && std::is_same_v<decltype(b), int>) {
            return a + b;
        } else {
            return static_cast<double>(a) + static_cast<double>(b);
        }
    };

    auto sum = std::visit(add_visitor, num1, num2);
    std::cout << "和: ";
    std::visit(Printer{}, sum);
    std::cout << "\n";

    // 7. 使用variant进行错误处理
    std::cout << "7. 使用variant进行错误处理:\n";
    using Result = std::variant<int, std::string>;  // 成功值或错误消息

    auto divide = [](int a, int b) -> Result {
        if (b == 0) {
            return std::string("除以零");
        }
        return a / b;
    };

    auto result_ok = divide(10, 2);
    auto result_err = divide(10, 0);

    std::visit([](const auto& value) {
        using T = std::decay_t<decltype(value)>;
        if constexpr (std::is_same_v<T, int>) {
            std::cout << "结果: " << value << "\n";
        } else {
            std::cout << "错误: " << value << "\n";
        }
    }, result_ok);

    std::visit([](const auto& value) {
        using T = std::decay_t<decltype(value)>;
        if constexpr (std::is_same_v<T, int>) {
            std::cout << "结果: " << value << "\n";
        } else {
            std::cout << "错误: " << value << "\n";
        }
    }, result_err);

    return 0;
}