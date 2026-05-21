/**
 * C++11 nullptr示例
 *
 * 演示内容：
 * - NULL与nullptr的区别
 * - nullptr的类型安全性
 * - 函数重载解析
 * - nullptr_t的模板特化
 */
#include <iostream>

// 三个重载函数，演示nullptr的重载解析
void func(int arg) {
    std::cout << "调用func(int)，值为: " << arg << "\n";
}

void func(char* arg) {
    if (arg == nullptr) {
        std::cout << "调用func(char*)，参数为nullptr\n";
    } else {
        std::cout << "调用func(char*)，字符串为: " << arg << "\n";
    }
}

void func(std::nullptr_t arg) {
    std::cout << "调用func(std::nullptr_t)\n";
}

// 模板函数，演示类型推导
template<typename T>
void template_func(T&& arg) {
    std::cout << "模板函数调用，参数类型: " << typeid(T).name() << "\n";
}

// nullptr_t的模板特化
template<>
void template_func<std::nullptr_t>(std::nullptr_t&& arg) {
    std::cout << "nullptr_t的模板特化\n";
}

// 支持nullptr比较的类
class PointerLike {
public:
    // 转换为bool，用于布尔测试
    explicit operator bool() const {
        return true;  // 这个例子中始终为真
    }

    // 与nullptr的比较运算符重载
    bool operator==(std::nullptr_t) const {
        return false;  // 这个例子中始终不为nullptr
    }
};

int main() {
    std::cout << "=== C++11 nullptr示例 ===\n\n";

    // 1. NULL与nullptr的区别
    std::cout << "1. NULL vs nullptr:\n";
    // NULL通常定义为0或(void*)0，是整数类型
    func(NULL);     // 调用func(int)! 这可能不是预期的行为

    // nullptr是std::nullptr_t类型，可以隐式转换为任何指针类型
    func(nullptr);  // 调用func(std::nullptr_t) - 正确的重载

    // 普通指针
    func(static_cast<char*>(nullptr)); // 调用func(char*)
    std::cout << "\n";

    // 2. 类型安全性
    std::cout << "2. 类型安全性:\n";
    int* int_ptr = nullptr;
    char* char_ptr = nullptr;

    // 可以安全地与nullptr比较
    if (int_ptr == nullptr) {
        std::cout << "int_ptr为空指针\n";
    }

    if (char_ptr == nullptr) {
        std::cout << "char_ptr为空指针\n";
    }

    // nullptr可以隐式转换为任何指针类型
    int_ptr = nullptr;
    char_ptr = nullptr;
    std::cout << "nullptr可以安全地赋值给任何指针类型\n\n";

    // 3. 模板推导
    std::cout << "3. 模板推导:\n";
    template_func(42);           // 调用泛化模板
    template_func(nullptr);      // 调用nullptr_t特化模板
    std::cout << "\n";

    // 4. sizeof比较
    std::cout << "4. 大小比较:\n";
    std::cout << "sizeof(nullptr): " << sizeof(nullptr) << "\n";
    std::cout << "sizeof(void*): " << sizeof(void*) << "\n";
    std::cout << "sizeof(std::nullptr_t): " << sizeof(std::nullptr_t) << "\n";
    std::cout << "nullptr的大小与void*相同\n\n";

    // 5. 支持nullptr的类
    std::cout << "5. 支持nullptr的类:\n";
    PointerLike obj;
    if (obj) {
        std::cout << "对象为真值\n";
    }

    if (!(obj == nullptr)) {
        std::cout << "对象不等于nullptr\n";
    }
    std::cout << "\n";

    // 6. 标准库中的使用
    std::cout << "6. 标准库中的使用:\n";
    int* arr[3] = {nullptr, nullptr, nullptr};

    // 统计空指针数量
    int null_count = 0;
    for (const auto& ptr : arr) {
        if (ptr == nullptr) {
            ++null_count;
        }
    }
    std::cout << "找到 " << null_count << " 个空指针\n\n";

    // 7. 安全初始化
    std::cout << "7. 安全初始化:\n";
    // 这些都是安全且清晰的初始化方式
    int* safe_int_ptr = nullptr;
    char* safe_char_ptr = nullptr;
    void* safe_void_ptr = nullptr;

    std::cout << "所有指针都安全地初始化为nullptr\n";

    return 0;
}