/**
 * C++11 Lambda表达式示例
 *
 * 演示内容：
 * - 基本lambda语法
 * - 值捕获和引用捕获
 * - lambda与STL算法的配合使用
 * - 使用auto进行类型推导
 */

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // 1. 基本lambda：两个整数的求和
    // []是lambda引入符，():=参数列表，{}是函数体，->类型是返回类型（可选）
    auto sum = [](int a, int b) { return a + b; };
    std::cout << "5 + 7 = " << sum(5, 7) << "\n";

    // 2. 值捕获：将外部变量x的值拷贝到lambda中
    // [x]表示按值捕获变量x
    int x = 10;
    auto add_x = [x](int y) { return x + y; };
    std::cout << "add_x(5) = " << add_x(5) << "\n";

    // 3. 引用捕获：捕获外部变量z的引用，可以修改原变量
    // [&z]表示按引用捕获变量z
    int z = 20;
    auto add_to_z = [&z](int y) { z += y; };
    add_to_z(10);
    std::cout << "add_to_z(10)后z的值: " << z << "\n";

    // 4. 显式指定返回类型的lambda
    // -> double表示返回类型为double
    auto divide = [](double a, double b) -> double {
        if (b == 0) return 0;
        return a / b;
    };
    std::cout << "10 / 3 = " << divide(10, 3) << "\n";

    // 5. lambda与STL算法配合使用（降序排序）
    // [](int a, int b) { return a > b; }是一个比较函数
    std::vector<int> numbers = {5, 2, 8, 1, 9};
    std::sort(numbers.begin(), numbers.end(), [](int a, int b) {
        return a > b;  // 大于号表示降序
    });

    std::cout << "降序排序结果: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    // 6. 可变捕获：使用mutable关键字可以修改按值捕获的变量
    // 注意：mutable修改的是拷贝，不会影响原变量
    int counter = 0;
    auto increment = [counter]() mutable {
        return ++counter;
    };
    std::cout << "第一次调用increment: " << increment() << "\n";
    std::cout << "第二次调用increment: " << increment() << "\n";
    std::cout << "原变量counter的值: " << counter << " (未被修改)\n";

    return 0;
}