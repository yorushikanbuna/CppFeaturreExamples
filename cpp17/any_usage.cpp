/**
 * C++17 std::any示例
 *
 * 演示内容：
 * - std::any用于任何类型的类型安全容器
 * - 运行时类型信息和转换
 * - 安全的类型检查和访问
 * - 与现有代码的集成
 */

#include <iostream>
#include <any>
#include <vector>
#include <map>
#include <string>

// 打印任何值的函数，带有类型信息
void printAny(const std::any& value) {
    if (value.type() == typeid(int)) {
        std::cout << "整数: " << std::any_cast<int>(value) << "\n";
    } else if (value.type() == typeid(double)) {
        std::cout << "双精度: " << std::any_cast<double>(value) << "\n";
    } else if (value.type() == typeid(std::string)) {
        std::cout << "字符串: " << std::any_cast<std::string>(value) << "\n";
    } else {
        std::cout << "未知类型\n";
    }
}

// 带有异常处理的安全any转换
template<typename T>
void safePrint(const std::any& value) {
    try {
        std::cout << std::any_cast<T>(value) << "\n";
    } catch (const std::bad_any_cast& e) {
        std::cout << "转换失败: " << e.what() << "\n";
    }
}

int main() {
    std::cout << "=== C++17 std::any示例 ===\n\n";

    // 1. 基本any用法
    std::cout << "1. 基本any用法:\n";
    std::any any1 = 42;
    std::any any2 = 3.14;
    std::any any3 = std::string("Hello");

    printAny(any1);
    printAny(any2);
    printAny(any3);
    std::cout << "\n";

    // 2. 类型检查和安全访问
    std::cout << "2. 类型检查和安全访问:\n";
    if (any1.type() == typeid(int)) {
        std::cout << "any1是int: " << std::any_cast<int>(any1) << "\n";
    }

    // 使用any_cast安全转换
    safePrint<int>(any1);
    safePrint<double>(any1);  // 这会安全失败
    std::cout << "\n";

    // 3. 重新赋值any值
    std::cout << "3. 重新赋值any值:\n";
    any1 = std::string("现在我是字符串");
    any2 = 100;

    printAny(any1);
    printAny(any2);
    std::cout << "\n";

    // 4. 容器中的any
    std::cout << "4. 容器中的any:\n";
    std::vector<std::any> values = {
        42,
        3.14,
        std::string("Hello"),
        std::vector<int>{1, 2, 3}
    };

    for (const auto& value : values) {
        printAny(value);
    }
    std::cout << "\n";

    // 5. maps中的any
    std::cout << "5. maps中的any:\n";
    std::map<std::string, std::any> config = {
        {"port", 8080},
        {"hostname", std::string("localhost")},
        {"ssl_enabled", true},
        {"timeout", 30.0}
    };

    for (const auto& [key, value] : config) {
        std::cout << key << ": ";
        printAny(value);
    }
    std::cout << "\n";

    // 6. 指针访问
    std::cout << "6. 指针访问:\n";
    if (int* ptr = std::any_cast<int>(&any2)) {
        std::cout << "any2保存的int值: " << *ptr << "\n";
        *ptr = 200;  // 修改值
        std::cout << "修改后的值: " << std::any_cast<int>(any2) << "\n";
    }
    std::cout << "\n";

    // 7. 重置any
    std::cout << "7. 重置any:\n";
    std::cout << "重置前any1是否有值: " << !any1.has_value() << "\n";
    any1.reset();
    std::cout << "重置后any1是否有值: " << !any1.has_value() << "\n";
    std::cout << "\n";

    // 8. 创建空any
    std::cout << "8. 空any:\n";
    std::any empty_any;
    std::cout << "空any是否有值: " << !empty_any.has_value() << "\n";

    // 为空any赋值
    empty_any = 42;
    std::cout << "赋值后: ";
    printAny(empty_any);

    return 0;
}