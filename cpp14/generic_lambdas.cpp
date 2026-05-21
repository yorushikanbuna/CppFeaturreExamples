/**
 * C++14 泛型Lambda示例
 *
 * 演示内容：
 * - 泛型Lambda（auto参数）
 * - 完美转发与std::forward
 * - 无需显式模板的模板行为
 * - decltype(auto)的使用
 */

#include <iostream>
#include <string>
#include <utility>

int main() {
    std::cout << "=== C++14 泛型Lambda示例 ===\n\n";

    // 1. 基本泛型Lambda
    std::cout << "1. 基本泛型Lambda:\n";
    // auto参数使Lambda成为模板
    auto print = [](auto value) {
        std::cout << "值: " << value << ", 类型: " << typeid(value).name() << "\n";
    };

    print(42);                // int
    print(3.14);              // double
    print(std::string("C++")); // std::string
    std::cout << "\n";

    // 2. 多个auto参数的泛型Lambda
    std::cout << "2. 多参数泛型Lambda:\n";
    auto add = [](auto a, auto b) {
        return a + b;
    };

    std::cout << "add(42, 3.14) = " << add(42, 3.14) << "\n";
    std::cout << "add(std::string(\"Hello\"), std::string(\" World\")) = "
              << add(std::string("Hello"), std::string(" World")) << "\n\n";

    // 3. 完美转发的泛型Lambda
    std::cout << "3. 完美转发的泛型Lambda:\n";
    auto forwarder = [](auto&& arg) {
        return std::forward<decltype(arg)>(arg);
    };

    int x = 10;
    int& ref = x;
    auto&& forwarded = forwarder(ref);

    std::cout << "原始x: " << x << "\n";
    forwarded = 20;  // 由于转发的是引用，这里修改会影响原变量
    std::cout << "通过转发修改后的x: " << x << "\n\n";

    // 4. 作为比较函数的泛型Lambda
    std::cout << "4. 作为比较函数的泛型Lambda:\n";
    auto compare = [](auto a, auto b) {
        return a < b;
    };

    std::cout << "5 < 10? " << (compare(5, 10) ? "是" : "否") << "\n";
    std::cout << "\"apple\" < \"banana\"? "
              << (compare("apple", "banana") ? "是" : "否") << "\n\n";

    // 5. 捕获变量的泛型Lambda
    std::cout << "5. 捕获变量的泛型Lambda:\n";
    int multiplier = 2;
    auto scale = [multiplier](auto value) {
        return value * multiplier;
    };

    std::cout << "scale(5) = " << scale(5) << "\n";
    std::cout << "scale(3.14) = " << scale(3.14) << "\n\n";

    return 0;
}