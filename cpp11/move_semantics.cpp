/**
 * C++11 移动语义示例
 *
 * 演示内容：
 * - 右值引用（&&）
 * - 移动构造函数和移动赋值运算符
 * - std::move工具函数
 * - 移动与拷贝的性能对比
 */

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

// 资源类，演示移动语义
class Resource {
private:
    std::vector<int> data;  // 模拟大型资源
    std::string name;

public:
    // 构造函数
    Resource(const std::string& n, size_t size) : name(n), data(size, 42) {
        std::cout << "构造资源 '" << name << "'，包含 " << size << " 个元素\n";
    }

    // 拷贝构造函数：深拷贝所有数据
    Resource(const Resource& other) : data(other.data), name(other.name) {
        std::cout << "拷贝资源 '" << name << "'\n";
    }

    // 移动构造函数： transfers ownership without copying
    // noexcept表示不会抛出异常，有助于编译器优化
    Resource(Resource&& other) noexcept
        : data(std::move(other.data)), name(std::move(other.name)) {
        std::cout << "移动资源 '" << name << "'\n";
    }

    // 拷贝赋值运算符
    Resource& operator=(const Resource& other) {
        if (this != &other) {
            data = other.data;
            name = other.name;
            std::cout << "拷贝赋值资源 '" << name << "'\n";
        }
        return *this;
    }

    // 移动赋值运算符
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);  // 移动vector，不拷贝
            name = std::move(other.name);  // 移动string，不拷贝
            std::cout << "移动赋值资源 '" << name << "'\n";
        }
        return *this;
    }

    // 析构函数
    ~Resource() {
        std::cout << "析构资源 '" << name << "'\n";
    }

    // 模拟处理数据
    void processData() {
        std::for_each(data.begin(), data.end(), [](int& n) { n *= 2; });
    }

    const std::string& getName() const { return name; }
    size_t getSize() const { return data.size(); }
};

// 函数返回Resource对象（触发RVO或移动语义）
Resource createResource(const std::string& name, size_t size) {
    return Resource(name, size);  // RVO或移动语义
}

// 接受Resource值参数的函数（演示移动语义）
void consumeResource(Resource res) {
    std::cout << "消费资源: '" << res.getName() << "'\n";
    res.processData();
}  // res在这里析构

int main() {
    std::cout << "=== C++11 移动语义示例 ===\n\n";

    // 1. 直接构造
    std::cout << "1. 直接构造:\n";
    Resource r1("Direct", 1000);
    std::cout << "\n";

    // 2. 拷贝构造
    std::cout << "2. 拷贝构造:\n";
    Resource r2 = r1;  // 调用拷贝构造函数
    std::cout << "\n";

    // 3. 移动构造
    std::cout << "3. 移动构造:\n";
    // 使用std::move将左值转换为右值引用
    Resource r3 = std::move(r1);  // 调用移动构造函数，r1变为"空"状态
    std::cout << "\n";

    // 4. 函数返回值优化（RVO/NRVO）
    std::cout << "4. 函数返回 (RVO):\n";
    Resource r4 = createResource("Returned", 1000);
    // 现代编译器会优化，直接在r4位置构造，不发生拷贝或移动
    std::cout << "\n";

    // 5. 函数参数移动
    std::cout << "5. 移动到函数参数:\n";
    consumeResource(std::move(r4));  // 将r4移动到函数中
    std::cout << "\n";

    // 6. 性能对比：移动 vs 拷贝
    std::cout << "6. 性能对比 - 移动 vs 拷贝:\n";

    // 拷贝操作
    Resource bigCopy("BigCopy", 100000);
    auto start = std::chrono::high_resolution_clock::now();
    Resource copyDest = bigCopy;  // 拷贝构造
    auto end = std::chrono::high_resolution_clock::now();
    auto copyTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // 移动操作
    Resource bigMove("BigMove", 100000);
    start = std::chrono::high_resolution_clock::now();
    Resource moveDest = std::move(bigMove);  // 移动构造
    end = std::chrono::high_resolution_clock::now();
    auto moveTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "拷贝耗时: " << copyTime.count() << " 微秒\n";
    std::cout << "移动耗时: " << moveTime.count() << " 微秒\n";
    if (moveTime.count() > 0) {
        std::cout << "移动比拷贝快约 "
                  << (copyTime.count() / moveTime.count()) << " 倍\n";
    }

    return 0;
}