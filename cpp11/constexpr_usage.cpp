/**
 * C++11 constexpr示例
 *
 * 演示内容：
 * - 基本constexpr函数
 * - constexpr构造函数和对象
 * - 编译时计算
 * - C++11中constexpr的限制和能力
 */

#include <iostream>
#include <array>

// 基本constexpr函数（C++11规则 - 非常有限）
// constexpr函数必须在编译时能够求值
constexpr int square(int x) {
    return x * x;  // C++11中是单表达式函数
}

// 更复杂的constexpr函数（仍受C++11限制）
// 使用递归实现阶乘，因为C++11不允许循环
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

// constexpr类
class Point {
private:
    int x_, y_;

public:
    // constexpr构造函数
    constexpr Point(int x, int y) : x_(x), y_(y) {}

    // constexpr成员函数
    constexpr int getX() const { return x_; }
    constexpr int getY() const { return y_; }
    constexpr int distanceSquared() const {
        return x_ * x_ + y_ * y_;
    }
};

// 模板来演示编译时数组初始化
// 使用模板递归计算斐波那契数列
template<int N>
struct Fibonacci {
    static constexpr int value = Fibonacci<N-1>::value + Fibonacci<N-2>::value;
};

// 模板特化
template<>
struct Fibonacci<0> {
    static constexpr int value = 0;
};

template<>
struct Fibonacci<1> {
    static constexpr int value = 1;
};

int main() {
    std::cout << "=== C++11 constexpr示例 ===\n\n";

    // 1. 基本constexpr函数用法
    std::cout << "1. 基本constexpr函数:\n";
    // 这些计算在编译时完成，结果直接嵌入到可执行文件中
    constexpr int result1 = square(5);
    std::cout << "square(5) = " << result1 << " (编译时计算)\n";

    constexpr int result2 = factorial(6);
    std::cout << "factorial(6) = " << result2 << " (编译时计算)\n";
    std::cout << "\n";

    // 2. constexpr对象
    std::cout << "2. constexpr对象:\n";
    constexpr Point p(3, 4);
    constexpr int dist_sq = p.distanceSquared();  // 编译时计算
    std::cout << "Point(3, 4) 到原点距离的平方: " << dist_sq << "\n";
    std::cout << "Point x: " << p.getX() << ", y: " << p.getY() << "\n\n";

    // 3. 编译时数组初始化
    std::cout << "3. 编译时数组初始化:\n";
    // 斐波那契数列在编译时计算并初始化数组
    constexpr std::array<int, 6> fib_sequence = {{
        Fibonacci<0>::value,   // 0
        Fibonacci<1>::value,   // 1
        Fibonacci<2>::value,   // 1
        Fibonacci<3>::value,   // 2
        Fibonacci<4>::value,   // 3
        Fibonacci<5>::value    // 5
    }};

    std::cout << "斐波那契数列: ";
    for (const auto& value : fib_sequence) {
        std::cout << value << " ";
    }
    std::cout << "\n\n";

    // 4. 条件constexpr用法
    std::cout << "4. 条件constexpr:\n";
    constexpr int size = 10;
    constexpr bool is_large = size > 5;  // 编译时计算

    if (is_large) {
        std::cout << "尺寸 " << size << " 被认为是大的\n";
    } else {
        std::cout << "尺寸 " << size << " 被认为是小的\n";
    }
    std::cout << "\n";

    // 5. constexpr数组索引
    std::cout << "5. constexpr数组索引:\n";
    constexpr int indices[] = {0, 1, 2, 3, 4};
    constexpr int lookup_table[] = {1, 4, 9, 16, 25};  // 平方数表

    // 在C++11中，不能直接在 constexpr 上使用范围for
    // 需要使用传统的for循环
    std::cout << "查表结果:\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "lookup_table[" << i << "] = " << lookup_table[i] << "\n";
    }
    std::cout << "\n";

    // 6. 限制演示
    std::cout << "6. constexpr限制 (C++11):\n";
    // 在C++11中，constexpr函数只能包含单个返回语句
    // 不允许循环、try-catch等

    // 在C++14中这是有效的，但在C++11中不行：
    /*
    constexpr int sum_up_to(int n) {
        int sum = 0;
        for (int i = 1; i <= n; ++i) {  // C++11不允许循环
            sum += i;
        }
        return sum;
    }
    */

    // 因此，在C++11中必须使用递归：
    std::cout << "C++11中递归计算必须在编译时完成\n";
    // 实际的递归constexpr调用在编译时发生
    constexpr int sum_result = 10 + 9 + 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1; // 预计算
    std::cout << "1到10的和 (预计算): " << sum_result << "\n";

    return 0;
}