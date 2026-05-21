/**
 * C++11 范围for循环示例
 *
 * 演示内容：
 * - 基本范围for循环语法
 * - 遍历数组、vector和map
 * - 使用const auto&提高效率
 * - 为自定义类型实现begin/end
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <initializer_list>

// 自定义容器类，演示自定义begin/end
class MyContainer {
private:
    std::vector<int> data;

public:
    // 使用initializer_list构造
    MyContainer(std::initializer_list<int> init) : data(init) {}

    // 提供迭代器接口
    std::vector<int>::iterator begin() { return data.begin(); }
    std::vector<int>::iterator end() { return data.end(); }
    std::vector<int>::const_iterator begin() const { return data.begin(); }
    std::vector<int>::const_iterator end() const { return data.end(); }
};

int main() {
    std::cout << "=== C++11 范围for循环示例 ===\n\n";

    // 1. 数组遍历
    std::cout << "1. 数组遍历:\n";
    int arr[] = {1, 2, 3, 4, 5};
    for (int value : arr) {
        std::cout << value << " ";
    }
    std::cout << "\n\n";

    // 2. vector遍历
    std::cout << "2. vector遍历:\n";
    std::vector<std::string> names = {"Alice", "Bob", "Charlie", "David"};
    // 使用const auto&避免字符串拷贝
    for (const auto& name : names) {
        std::cout << "你好, " << name << "!\n";
    }
    std::cout << "\n";

    // 3. map遍历
    std::cout << "3. map遍历:\n";
    std::map<std::string, int> scores = {
        {"Alice", 95},
        {"Bob", 87},
        {"Charlie", 92}
    };

    // 遍历键值对，pair.first是key，pair.second是value
    for (const auto& pair : scores) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }
    std::cout << "\n";

    // 4. 遍历中修改元素
    std::cout << "4. 遍历中修改元素:\n";
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "修改前: ";
    for (const auto& n : numbers) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    // 使用auto&可以修改元素
    for (auto& n : numbers) {
        n *= 2;  // 每个元素乘以2
    }

    std::cout << "修改后: ";
    for (const auto& n : numbers) {
        std::cout << n << " ";
    }
    std::cout << "\n\n";

    // 5. 自定义容器遍历
    std::cout << "5. 自定义容器遍历:\n";
    MyContainer container = {10, 20, 30, 40, 50};
    for (const auto& value : container) {
        std::cout << value << " ";
    }
    std::cout << "\n\n";

    // 6. 性能注意事项
    std::cout << "6. 性能注意事项:\n";
    std::vector<std::string> words = {"C++", "范围for", "循环", "很", "高效"};

    // 高效：const auto&避免拷贝
    std::cout << "使用const auto&: ";
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << "\n";

    // 低效：每次都会拷贝元素
    std::cout << "使用auto (拷贝): ";
    for (auto word : words) {
        std::cout << word << " ";
    }
    std::cout << "\n\n";

    // 7. initializer_list使用
    std::cout << "7. initializer_list使用:\n";
    for (const auto& value : {100, 200, 300, 400}) {
        std::cout << value << " ";
    }
    std::cout << "\n\n";

    // 8. 嵌套容器
    std::cout << "8. 嵌套容器:\n";
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    for (const auto& row : matrix) {
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    return 0;
}