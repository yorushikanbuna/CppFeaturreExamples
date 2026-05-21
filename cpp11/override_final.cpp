/**
 * C++11 override和final说明符示例
 *
 * 演示内容：
 * - override说明符用于虚函数重写
 * - final说明符用于防止继承/重写
 * - 明确说明符对代码安全性的益处
 * - 错误使用时的编译器诊断
 */

#include <iostream>
#include <memory>

// 基类，包含虚函数
class Shape {
public:
    virtual ~Shape() = default;  // 虚析构函数

    // 纯虚函数，必须被重写
    virtual double area() const = 0;

    // 带实现的虚函数，可以被重写
    virtual void print() const {
        std::cout << "这是一个形状\n";
    }

    // 不应该被重写的虚函数
    virtual void fixedMethod() const {
        std::cout << "此方法不应被重写\n";
    }
};

// 正确使用override的派生类
class Circle : public Shape {
private:
    double radius_;

public:
    Circle(double radius) : radius_(radius) {}

    // 正确重写纯虚函数
    double area() const override {
        return 3.14159 * radius_ * radius_;
    }

    // 正确重写虚函数
    void print() const override {
        std::cout << "圆形，半径为 " << radius_ << "\n";
    }

    // 故意不重写fixedMethod（这是好的）
};

// 另一个派生类
class Rectangle : public Shape {
private:
    double width_, height_;

public:
    Rectangle(double width, double height) : width_(width), height_(height) {}

    // 正确重写纯虚函数
    double area() const override {
        return width_ * height_;
    }

    // 正确重写虚函数
    void print() const override {
        std::cout << "矩形 " << width_ << " x " << height_ << "\n";
    }
};

// 使用final说明符的类
class SealedShape final : public Shape {
private:
    double value_;

public:
    SealedShape(double value) : value_(value) {}

    double area() const override {
        return value_;
    }

    void print() const override {
        std::cout << "密封形状，值为 " << value_ << "\n";
    }
    // final表示这个类不能被继承
    // 尝试继承 SealedShape 会导致编译错误
};

// 演示方法级别的final说明符
class BaseWithFinal {
public:
    virtual ~BaseWithFinal() = default;

    // 不能被重写的虚函数
    virtual void sealedMethod() const final {
        std::cout << "此方法不能被重写\n";
    }

    // 可以被重写的普通虚函数
    virtual void normalMethod() const {
        std::cout << "此方法可以被重写\n";
    }
};

// BaseWithFinal的派生类
class DerivedFromFinal : public BaseWithFinal {
public:
    // 这会导致编译错误：
    // void sealedMethod() const override { }  // 错误：不能重写final方法

    // 这是允许的 - 重写非final方法
    void normalMethod() const override {
        std::cout << "重写的普通方法\n";
    }
};

int main() {
    std::cout << "=== C++11 override和final说明符示例 ===\n\n";

    // 1. 使用override的多态
    std::cout << "1. 使用override的多态:\n";
    std::unique_ptr<Shape> shapes[] = {
        std::make_unique<Circle>(5.0),
        std::make_unique<Rectangle>(4.0, 6.0),
        std::make_unique<SealedShape>(42.0)
    };

    for (const auto& shape : shapes) {
        shape->print();  // 虚函数调用
        std::cout << "面积: " << shape->area() << "\n\n";
    }

    // 2. override说明符的益处
    std::cout << "2. override说明符的益处:\n";
    std::cout << "如果拼写错误或签名不对，\n";
    std::cout << "编译器会捕获错误因为有'override'\n\n";

    // 会导致编译错误的示例：
    /*
    class BadCircle : public Shape {
    public:
        // 这会导致编译错误，因为没有匹配的虚函数：
        // double area(int) const override { return 0; }  // 错误：没有匹配的虚函数

        // 这也会导致错误：
        // double areax() const override { return 0; }    // 错误：没有名为'areax'的虚函数

        // 正确的重写：
        double area() const override { return 3.14; }
    };
    */

    // 3. final说明符演示
    std::cout << "3. final说明符演示:\n";
    BaseWithFinal base;
    DerivedFromFinal derived;

    base.sealedMethod();    // 调用基类实现
    base.normalMethod();    // 调用基类实现

    derived.sealedMethod(); // 仍然调用基类实现（不能被重写）
    derived.normalMethod(); // 调用派生类实现

    std::cout << "\n";

    // 4. final说明符的益处
    std::cout << "4. final说明符的益处:\n";
    std::cout << "- 防止意外继承而破坏设计假设\n";
    std::cout << "- 使编译器能够进行优化（去虚化）\n";
    std::cout << "- 清晰地记录设计意图\n\n";

    // 5. 性能考虑
    std::cout << "5. 性能方面:\n";
    std::cout << "final方法和类可以被编译器更好地优化\n";
    std::cout << "因为编译器知道它们不会被重写。\n";

    return 0;
}