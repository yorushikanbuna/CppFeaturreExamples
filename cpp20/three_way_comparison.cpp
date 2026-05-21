/**
 * C++20 三路比较示例
 *
 * 演示内容：
 * - 三路比较运算符（<=>），也称太空船运算符
 * - 自动生成所有比较运算符
 * - 与标准库的集成
 * - 自定义比较逻辑
 */

#include <iostream>
#include <compare>
#include <string>
#include <vector>
#include <algorithm>

// 使用默认三路比较运算符的类
class Point {
public:
    int x, y;

    // 默认三路比较运算符 - 编译器自动生成所有比较运算符
    auto operator<=>(const Point&) const = default;

    Point(int x, int y) : x(x), y(y) {}
};

// 使用自定义三路比较运算符的类
class Person {
private:
    std::string name;
    int age;

public:
    Person(const std::string& n, int a) : name(n), age(a) {}

    // 自定义三路比较运算符 - 先按姓名比较，再按年龄比较
    auto operator<=>(const Person& other) const {
        if (auto cmp = name <=> other.name; cmp != 0) {
            return cmp;  // 姓名不同，返回比较结果
        }
        return age <=> other.age;  // 姓名相同，比较年龄
    }

    // == 运算符需要单独定义（C++20中，==可以自动生成）
    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }
};

// 使用混合比较方法的类
class Product {
private:
    std::string name;
    double price;

public:
    Product(const std::string& n, double p) : name(n), price(p) {}

    // 只定义三路比较运算符
    auto operator<=>(const Product&) const = default;
};

int main() {
    std::cout << "=== C++20 三路比较运算符 (<=>) ===\n\n";

    // 1. 使用默认三路比较运算符
    std::cout << "1. Point类的默认三路比较:\n";
    Point p1(3, 4);
    Point p2(3, 5);
    Point p3(3, 4);

    // 所有比较运算符都由编译器自动生成
    std::cout << "p1 < p2: " << (p1 < p2) << "\n";
    std::cout << "p1 > p2: " << (p1 > p2) << "\n";
    std::cout << "p1 <= p2: " << (p1 <= p2) << "\n";
    std::cout << "p1 >= p2: " << (p1 >= p2) << "\n";
    std::cout << "p1 == p3: " << (p1 == p3) << "\n";
    std::cout << "p1 != p2: " << (p1 != p2) << "\n\n";

    // 2. 三路比较结果
    std::cout << "2. 三路比较结果:\n";
    auto result = p1 <=> p2;
    if (result < 0) {
        std::cout << "p1 小于 p2\n";
    } else if (result > 0) {
        std::cout << "p1 大于 p2\n";
    } else {
        std::cout << "p1 等于 p2\n";
    }

    // 强排序结果类型
    std::cout << "强排序结果类型: " << typeid(result).name() << "\n\n";

    // 3. 自定义比较逻辑
    std::cout << "3. Person类的自定义比较:\n";
    Person alice("Alice", 30);
    Person bob("Bob", 25);
    Person alice2("Alice", 30);

    std::cout << "alice < bob: " << (alice < bob) << "\n";
    std::cout << "alice == alice2: " << (alice == alice2) << "\n";
    std::cout << "alice != bob: " << (alice != bob) << "\n\n";

    // 4. 与标准库集成
    std::cout << "4. 与标准库集成:\n";
    std::vector<Point> points = {{1, 2}, {3, 4}, {0, 1}, {5, 6}};

    // 因为Point有三路比较运算符，可以直接使用std::sort
    std::sort(points.begin(), points.end());

    std::cout << "排序后的点:\n";
    for (const auto& pt : points) {
        std::cout << "(" << pt.x << ", " << pt.y << ")\n";
    }
    std::cout << "\n";

    // 5. 比较类别
    std::cout << "5. 比较类别:\n";

    // 强排序 - 值完全有序
    auto strong_result = 5 <=> 10;
    std::cout << "强排序示例: 5 <=> 10\n";
    std::cout << "类型: " << typeid(strong_result).name() << "\n";

    // 弱排序 - 值可能有等价类
    std::string s1 = "hello";
    std::string s2 = "HELLO";
    auto weak_result = s1 <=> s2;
    std::cout << "弱排序示例: 字符串比较\n";
    std::cout << "类型: " << typeid(weak_result).name() << "\n\n";

    // 6. 混合比较方法
    std::cout << "6. Product类的三路比较:\n";
    Product prod1("苹果", 1.50);
    Product prod2("香蕉", 0.75);

    std::cout << "prod1 < prod2: " << (prod1 < prod2) << "\n";
    std::cout << "prod1 == prod2: " << (prod1 == prod2) << "\n\n";

    return 0;
}