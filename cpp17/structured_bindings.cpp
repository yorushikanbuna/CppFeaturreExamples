/**
 * C++17 结构化绑定示例
 *
 * 演示内容：
 * - 将tuple解包为命名变量
 * - 在范围for循环中解包map条目
 * - 解包struct成员
 * - 通过结构化绑定修改值
 */

#include <iostream>
#include <tuple>
#include <map>
#include <vector>
#include <string>

// 简单的结构体用于演示
struct Point {
    int x;
    int y;
    int z;
};

// 带有公共成员的结构体
struct Measurement {
    double value;
    std::string unit;
    int timestamp;
};

int main() {
    std::cout << "=== C++17 结构化绑定示例 ===\n\n";

    // 1. 基本tuple解包
    std::cout << "1. 基本tuple解包:\n";
    std::tuple<int, std::string, double> person = {42, "Alice", 65.5};
    // 使用auto [var1, var2, var3] = tuple 语法
    auto [id, name, weight] = person;

    std::cout << "ID: " << id
              << ", 姓名: " << name
              << ", 体重: " << weight << "\n\n";

    // 2. 带引用的tuple解包
    std::cout << "2. 带引用的tuple解包:\n";
    auto& [id_ref, name_ref, weight_ref] = person;
    id_ref = 43;  // 修改解包的变量会影响原tuple
    std::cout << "更新后的ID: " << id << "\n";
    std::cout << "原tuple的ID: " << std::get<0>(person) << "\n\n";

    // 3. 解包map
    std::cout << "3. 解包map:\n";
    std::map<std::string, int> scores = {
        {"Alice", 90},
        {"Bob", 85},
        {"Charlie", 95}
    };

    // 在范围for循环中直接解包键值对
    for (const auto& [student, score] : scores) {
        std::cout << student << "的成绩: " << score << "\n";
    }
    std::cout << "\n";

    // 4. 解包struct
    std::cout << "4. 解包struct:\n";
    Point p1 = {1, 2, 3};
    auto [x, y, z] = p1;  // 变量名必须与成员声明顺序一致
    std::cout << "点坐标: (" << x << ", " << y << ", " << z << ")\n\n";

    // 5. 解包到已存在的变量
    std::cout << "5. 解包到已存在的变量:\n";
    int a, b, c;
    std::tie(a, b, c) = std::make_tuple(10, 20, 30);
    std::cout << "a: " << a << ", b: " << b << ", c: " << c << "\n\n";

    // 6. 返回多个值的函数
    std::cout << "6. 返回多个值的函数:\n";
    auto getDimensions = []() -> std::tuple<double, double, double> {
        return {10.5, 20.3, 5.7};
    };

    auto [width, height, depth] = getDimensions();
    std::cout << "尺寸: " << width << " x " << height << " x " << depth << "\n\n";

    // 7. 与std::pair的结构化绑定
    std::cout << "7. 与std::pair的结构化绑定:\n";
    std::pair<std::string, int> user("admin", 1001);
    auto [role, uid] = user;
    std::cout << "角色: " << role << ", UID: " << uid << "\n\n";

    // 8. 包含pair的容器
    std::cout << "8. 包含pair的容器:\n";
    std::vector<std::pair<int, std::string>> items = {
        {1, "苹果"},
        {2, "香蕉"},
        {3, "樱桃"}
    };

    std::cout << "项目列表:\n";
    for (const auto& [id, name] : items) {
        std::cout << "- " << id << ": " << name << "\n";
    }
    std::cout << "\n";

    // 9. 通过结构化绑定修改
    std::cout << "9. 通过结构化绑定修改:\n";
    std::map<std::string, int> inventory = {
        {"苹果", 50},
        {"香蕉", 30}
    };

    // 增加苹果数量
    auto& [fruit, count] = *inventory.find("苹果");
    count += 10;
    std::cout << "更新后的 " << fruit << " 数量: " << count << "\n\n";

    return 0;
}