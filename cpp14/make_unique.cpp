/**
 * C++14 std::make_unique示例
 *
 * 演示内容：
 * - std::make_unique用于安全创建对象
 * - 异常安全性改进
 * - 与手动new/delete的比较
 * - 使用模式和最佳实践
 */

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>

class Resource {
private:
    std::string name_;
    int* data_;

public:
    Resource(const std::string& name, size_t size)
        : name_(name), data_(new int[size]) {
        std::cout << "Resource '" << name_ << "' 已获取\n";
    }

    ~Resource() {
        delete[] data_;
        std::cout << "Resource '" << name_ << "' 已释放\n";
    }

    // 删除拷贝构造函数和赋值运算符
    Resource(const Resource&) = delete;
    Resource& operator=(const Resource&) = delete;

    // 移动构造函数和移动赋值运算符
    Resource(Resource&& other) noexcept
        : name_(std::move(other.name_)), data_(other.data_) {
        other.data_ = nullptr;
        std::cout << "Resource '" << name_ << "' 已移动\n";
    }

    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            name_ = std::move(other.name_);
            data_ = other.data_;
            other.data_ = nullptr;
            std::cout << "Resource '" << name_ << "' 已移动赋值\n";
        }
        return *this;
    }

    const std::string& getName() const { return name_; }
};

// 可能抛出异常的函数
void riskyFunction(bool shouldThrow) {
    if (shouldThrow) {
        throw std::runtime_error("出错了！");
    }
}

// 接受Resource所有权的函数
void consumeResource(std::unique_ptr<Resource> resource) {
    if (resource) {
        std::cout << "正在消费Resource: " << resource->getName() << "\n";
    }
}

int main() {
    std::cout << "=== C++14 std::make_unique示例 ===\n\n";

    // 1. make_unique的基本用法
    std::cout << "1. make_unique基本用法:\n";
    auto resource1 = std::make_unique<Resource>("Basic", 100);
    std::cout << "创建的Resource: " << resource1->getName() << "\n\n";

    // 2. 异常安全性比较
    std::cout << "2. 异常安全性:\n";

    try {
        // 安全的方式 - 使用make_unique
        auto safe_resource = std::make_unique<Resource>("Safe", 100);
        riskyFunction(false);  // 不会抛出异常
        std::cout << "安全Resource已创建: " << safe_resource->getName() << "\n";
    } catch (const std::exception& e) {
        std::cout << "捕获异常: " << e.what() << "\n";
    }
    std::cout << "\n";

    // 3. make_unique与数组
    std::cout << "3. make_unique与数组:\n";
    auto int_array = std::make_unique<int[]>(10);
    for (int i = 0; i < 10; ++i) {
        int_array[i] = i * i;
    }

    std::cout << "数组内容: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << int_array[i] << " ";
    }
    std::cout << "\n\n";

    // 4. make_unique与初始化
    std::cout << "4. make_unique与初始化:\n";
    auto vec = std::make_unique<std::vector<int>>(std::initializer_list<int>{1, 2, 3, 4, 5});
    std::cout << "Vector大小: " << vec->size() << "\n";
    std::cout << "Vector内容: ";
    for (const auto& item : *vec) {
        std::cout << item << " ";
    }
    std::cout << "\n\n";

    // 5. 函数参数和返回值
    std::cout << "5. 函数参数和返回值:\n";

    // 传递给函数（转移所有权）
    auto resource2 = std::make_unique<Resource>("ForFunction", 50);
    consumeResource(std::move(resource2));  // 所有权转移
    // resource2现在是nullptr

    // 从函数返回
    auto factory = []() -> std::unique_ptr<Resource> {
        return std::make_unique<Resource>("FactoryMade", 75);
    };

    auto resource3 = factory();
    std::cout << "工厂创建的Resource: " << resource3->getName() << "\n\n";

    // 6. make_unique vs new比较
    std::cout << "6. make_unique vs new:\n";

    // 旧方式（C++11）
    std::unique_ptr<Resource> old_way(new Resource("OldWay", 25));

    // 新方式（C++14）
    auto new_way = std::make_unique<Resource>("NewWay", 25);

    std::cout << "两个Resource都成功创建\n\n";

    // 7. make_unique与自定义类型
    std::cout << "7. make_unique与自定义类型:\n";
    struct Point {
        double x, y;
        Point(double x, double y) : x(x), y(y) {}
    };

    auto point = std::make_unique<Point>(3.14, 2.71);
    std::cout << "Point: (" << point->x << ", " << point->y << ")\n\n";

    // 8. unique_ptr容器
    std::cout << "8. unique_ptr容器:\n";
    std::vector<std::unique_ptr<Resource>> resources;
    resources.push_back(std::make_unique<Resource>("Vector1", 10));
    resources.push_back(std::make_unique<Resource>("Vector2", 20));
    resources.push_back(std::make_unique<Resource>("Vector3", 30));

    std::cout << "在vector中创建了 " << resources.size() << " 个Resource\n";

    return 0;
}