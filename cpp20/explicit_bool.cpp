/**
 * C++20 explicit(bool)示例
 *
 * 演示内容：
 * - 条件性explicit构造函数
 * - 类型安全性改进
 * - 上下文敏感的转换
 * - 与现有代码的集成
 */

#include <iostream>
#include <string>
#include <type_traits>

// 带有条件explicit构造函数的类
class Distance {
private:
    double meters_;

public:
    // 条件性explicit构造函数
    // 从int转换时explicit，防止意外转换
    // 从double转换时implicit，方便使用
    template<typename T>
    explicit(!std::is_same_v<T, double>)
    Distance(T meters) : meters_(static_cast<double>(meters)) {}

    // 拷贝构造函数
    Distance(const Distance&) = default;

    // 获取器
    double getMeters() const { return meters_; }
    double getFeet() const { return meters_ * 3.28084; }

    // 算术运算符
    Distance operator+(const Distance& other) const {
        return Distance(meters_ + other.meters_);
    }

    // 比较运算符
    bool operator==(const Distance& other) const {
        return meters_ == other.meters_;
    }

    // 流输出
    friend std::ostream& operator<<(std::ostream& os, const Distance& d) {
        os << d.meters_ << " 米";
        return os;
    }
};

// 演示explicit(bool)与concepts结合的类
template<typename T>
class Container {
private:
    T value_;

public:
    // T不是算术类型时explicit（防止意外转换）
    // T是算术类型时implicit（方便使用）
    explicit(!std::is_arithmetic_v<T>)
    Container(T value) : value_(value) {}

    T getValue() const { return value_; }
};

// 接受Distance的函数
void printDistance(Distance d) {
    std::cout << "距离: " << d << "\n";
}

int main() {
    std::cout << "=== C++20 explicit(bool) ===\n\n";

    // 1. 基本用法
    std::cout << "1. 基本用法:\n";

    // 从double隐式转换（不explicit）
    Distance d1 = 5.5;  // OK - 隐式转换
    printDistance(d1);

    // 从int显式转换（explicit）
    Distance d2{10};    // OK - 显式构造
    printDistance(d2);

    // 这会导致编译错误：
    // Distance d3 = 10;  // 错误 - 需要显式转换

    std::cout << "\n";

    // 2. 算术运算
    std::cout << "2. 算术运算:\n";
    Distance sum = d1 + d2;
    std::cout << "和: " << sum << "\n";
    std::cout << "换算为英尺: " << sum.getFeet() << " 英尺\n\n";

    // 3. 带有explicit(bool)的容器类
    std::cout << "3. 容器类:\n";

    // 算术类型可以隐式构造
    Container<int> c1 = 42;        // OK - 隐式
    Container<double> c2 = 3.14;   // OK - 隐式

    // 非算术类型需要显式构造
    Container<std::string> c3{std::string("Hello")};  // OK - 需要显式

    std::cout << "Container<int>: " << c1.getValue() << "\n";
    std::cout << "Container<double>: " << c2.getValue() << "\n";
    std::cout << "Container<string>: " << c3.getValue() << "\n\n";

    // 4. 类型安全性优势
    std::cout << "4. 类型安全性:\n";

    // 防止可能导致错误的意外转换
    auto calculateArea = [](Distance length, Distance width) {
        return length.getMeters() * width.getMeters();
    };

    // 这些工作正常：
    double area1 = calculateArea(Distance{5.0}, Distance{3.0});  // 显式double
    double area2 = calculateArea(5.0, 3.0);                      // 隐式double

    std::cout << "面积1: " << area1 << " 平方米\n";
    std::cout << "面积2: " << area2 << " 平方米\n";

    // 这会被防止：
    // int length = 5, width = 3;
    // double area3 = calculateArea(length, width);  // 错误 - 需要显式构造

    std::cout << "\n";

    // 5. 与传统方法比较
    std::cout << "5. 与传统方法比较:\n";

    // 传统explicit构造函数（始终explicit）
    class TraditionalDistance {
        double meters_;
    public:
        explicit TraditionalDistance(double m) : meters_(m) {}
        double getMeters() const { return meters_; }
    };

    // 传统implicit构造函数（始终implicit）
    class ImplicitDistance {
        double meters_;
    public:
        ImplicitDistance(double m) : meters_(m) {}
        double getMeters() const { return meters_; }
    };

    // 使用explicit(bool)，我们获得两全其美的效果
    std::cout << "explicit(bool)提供上下文敏感的explicit控制\n";
    std::cout << "- double转换时隐式：方便使用\n";
    std::cout << "- int转换时显式：防止错误\n";

    return 0;
}