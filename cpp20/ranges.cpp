/**
 * C++20 Ranges示例
 *
 * 演示内容：
 * - 基于范围的算法
 * - 范围适配器和视图
 * - 惰性求值
 * - 管道组合
 */

#include <iostream>
#include <vector>
#include <ranges>
#include <string>
#include <algorithm>

int main() {
    std::cout << "=== C++20 Ranges示例 ===\n\n";

    // 1. 基本范围用法
    std::cout << "1. 基本范围用法:\n";
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 传统方式
    std::cout << "传统for循环: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // 基于范围的方式
    std::cout << "基于范围的for循环: ";
    for (const auto& num : std::ranges::views::all(numbers)) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";

    // 2. 范围适配器
    std::cout << "2. 范围适配器:\n";

    // 过滤偶数
    auto evens = numbers | std::ranges::views::filter([](int n) { return n % 2 == 0; });
    std::cout << "偶数: ";
    for (const auto& num : evens) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // 变换数字（求平方）
    auto squares = numbers | std::ranges::views::transform([](int n) { return n * n; });
    std::cout << "平方数: ";
    for (const auto& num : squares) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // 取前5个元素
    auto first_five = numbers | std::ranges::views::take(5);
    std::cout << "前5个: ";
    for (const auto& num : first_five) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";

    // 3. 管道组合
    std::cout << "3. 管道组合:\n";

    // 链式操作：取前8个，过滤偶数，求平方
    // 使用 | 运算符组合多个视图，像Unix管道一样
    auto pipeline_result = numbers
        | std::ranges::views::take(8)
        | std::ranges::views::filter([](int n) { return n % 2 == 0; })
        | std::ranges::views::transform([](int n) { return n * n; });

    std::cout << "管道结果: ";
    for (const auto& num : pipeline_result) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";

    // 4. 惰性求值
    std::cout << "4. 惰性求值:\n";
    std::vector<int> lazy_numbers = {1, 2, 3, 4, 5};

    // 视图是惰性的 - 在迭代之前不会应用变换
    auto lazy_view = lazy_numbers
        | std::ranges::views::filter([](int n) {
            std::cout << "过滤 " << n << "\n";
            return n % 2 == 0;
        })
        | std::ranges::views::transform([](int n) {
            std::cout << "变换 " << n << "\n";
            return n * n;
        });

    std::cout << "遍历惰性视图:\n";
    for (const auto& num : lazy_view) {
        std::cout << "得到: " << num << "\n";
    }
    std::cout << "\n";

    // 5. 字符串范围
    std::cout << "5. 字符串范围:\n";
    std::string text = "Hello, World!";

    // 按分隔符分割字符串
    auto split_view = text | std::ranges::views::split(',');

    std::cout << "按逗号分割:\n";
    for (const auto& part : split_view) {
        // 将子范围转换为字符串以便打印
        std::string part_str(part.begin(), part.end());
        std::cout << "'" << part_str << "'\n";
    }

    // 6. 范围算法
    std::cout << "6. 范围算法:\n";
    std::vector<int> algo_numbers = {5, 2, 8, 1, 9, 3};

    // 使用范围算法排序
    std::ranges::sort(algo_numbers);
    std::cout << "排序后: ";
    for (const auto& num : algo_numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // 查找元素
    auto found = std::ranges::find(algo_numbers, 8);
    if (found != algo_numbers.end()) {
        std::cout << "找到8的位置: "
                  << std::distance(algo_numbers.begin(), found) << "\n";
    }

    return 0;
}