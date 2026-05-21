/**
 * C++17 if constexpr示例
 *
 * 演示内容：
 * - 使用if constexpr进行编译时分支
 * - 无需显式特化的模板
 * - 基于类型特征的决策
 * - SFINAE的替代方案
 */

#include <iostream>
#include <type_traits>
#include <string>
#include <vector>

// 使用if constexpr处理不同类型的模板函数
template<typename T>
void printType(const T& value) {
    if constexpr (std::is_integral_v<T>) {
        // 编译时检查：如果是整数类型
        std::cout << "整数值: " << value << "\n";
    } else if constexpr (std::is_floating_point_v<T>) {
        // 编译时检查：如果是浮点类型
        std::cout << "浮点值: " << value << "\n";
    } else if constexpr (std::is_same_v<T, std::string>) {
        // 编译时检查：如果是string类型
        std::cout << "字符串值: " << value << "\n";
    } else {
        // 其他类型
        std::cout << "其他类型值: " << value << "\n";
    }
}

// 根据类型计算大小的函数
template<typename T>
size_t getSize(const T& container) {
    if constexpr (std::is_arithmetic_v<T>) {
        // 如果是算术类型，返回sizeof
        return sizeof(T);
    } else {
        // 否则调用size()方法
        return container.size();
    }
}

// 演示复杂类型检查的模板函数
template<typename T>
void processValue(T&& value) {
    if constexpr (std::is_pointer_v<std::decay_t<T>>) {
        std::cout << "正在处理指针\n";
        if constexpr (std::is_same_v<std::decay_t<T>, char*>) {
            std::cout << "C字符串: " << value << "\n";
        } else {
            std::cout << "其他指针类型\n";
        }
    } else if constexpr (std::is_class_v<std::decay_t<T>>) {
        std::cout << "正在处理类类型\n";
        if constexpr (std::is_same_v<std::decay_t<T>, std::string>) {
            std::cout << "字符串长度: " << value.length() << "\n";
        } else {
            std::cout << "其他类类型\n";
        }
    } else {
        std::cout << "正在处理基本类型: " << value << "\n";
    }
}

int main() {
    std::cout << "=== C++17 if constexpr示例 ===\n\n";

    // 1. 基于类型的基础分发
    std::cout << "1. 基于类型的基础分发:\n";
    printType(42);                    // 整数
    printType(3.14);                  // 浮点数
    printType(std::string("Hello"));  // 字符串
    printType('A');                   // 整数(char也是整数类型)
    std::cout << "\n";

    // 2. 基于类型的大小计算
    std::cout << "2. 基于类型的大小计算:\n";
    int intValue = 100;
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::string str = "Hello";

    std::cout << "int大小: " << getSize(intValue) << " 字节\n";
    std::cout << "vector大小: " << getSize(vec) << " 个元素\n";
    std::cout << "string大小: " << getSize(str) << " 个字符\n\n";

    // 3. 复杂类型处理
    std::cout << "3. 复杂类型处理:\n";
    int number = 42;
    int* ptr = &number;
    const char* cstr = "Hello";
    std::string cppStr = "World";

    processValue(number);    // 基本类型
    processValue(ptr);       // 指针
    processValue(cstr);      // C字符串
    processValue(cppStr);    // 字符串类
    std::cout << "\n";

    // 4. 编译时数组处理
    std::cout << "4. 编译时数组处理:\n";
    auto processArray = [](const auto& arr) {
        if constexpr (std::rank_v<std::decay_t<decltype(arr)>> > 0) {
            // 如果是数组
            std::cout << "数组包含 " << std::extent_v<std::decay_t<decltype(arr)>> << " 个元素\n";
        } else {
            std::cout << "不是数组\n";
        }
    };

    int simpleArray[5] = {1, 2, 3, 4, 5};
    int singleValue = 42;

    processArray(simpleArray);
    processArray(singleValue);
    std::cout << "\n";

    return 0;
}