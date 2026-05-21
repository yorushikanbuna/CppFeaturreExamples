/**
 * C++20 指定初始化器示例
 *
 * 演示内容：
 * - 使用指定初始化器初始化结构体
 * - 灵活的成员初始化
 * - 顺序独立性
 * - 与现有初始化方式的集成
 */

#include <iostream>
#include <string>

// 使用指定初始化器的结构体
struct Person {
    std::string name;
    int age = 0;
    std::string email;
    bool active = true;
};

// 带有默认值的配置结构体
struct Config {
    int buffer_size = 1024;
    bool debug = false;
    double threshold = 0.5;
    int max_connections = 100;
};

// 嵌套结构体
struct Address {
    std::string street;
    std::string city;
    std::string country;
};

struct Employee {
    std::string name;
    int id;
    Address address;
    double salary;
};

int main() {
    std::cout << "=== C++20 指定初始化器 ===\n\n";

    // 1. 基本指定初始化器
    std::cout << "1. 基本指定初始化器:\n";

    // 只初始化特定的成员
    Person p1{
        .name = "Alice",
        .age = 30
        // email和active使用默认值
    };

    std::cout << "Person 1: " << p1.name << ", " << p1.age
              << ", " << p1.email << ", " << std::boolalpha << p1.active << "\n";

    // 初始化所有成员
    Person p2{
        .name = "Bob",
        .age = 25,
        .email = "bob@example.com",
        .active = false
    };

    std::cout << "Person 2: " << p2.name << ", " << p2.age
              << ", " << p2.email << ", " << std::boolalpha << p2.active << "\n\n";

    // 2. 顺序独立性
    std::cout << "2. 顺序独立性:\n";

    // 成员可以以任何顺序初始化
    // 注意：C++20标准要求指定初始化器必须按照声明顺序
    // 但这里演示的是按名称指定初始化的概念
    Person p3{
        .name = "Charlie",
        .age = 35,
        .email = "charlie@example.com",
        .active = true
    };

    std::cout << "Person 3: " << p3.name << ", " << p3.age
              << ", " << p3.email << ", " << std::boolalpha << p3.active << "\n\n";

    // 3. 部分初始化
    std::cout << "3. 部分初始化:\n";

    Config config1{
        .buffer_size = 2048,
        .debug = true
        // threshold和max_connections使用默认值
    };

    std::cout << "Config 1: buffer=" << config1.buffer_size
              << ", debug=" << std::boolalpha << config1.debug
              << ", threshold=" << config1.threshold
              << ", max_conn=" << config1.max_connections << "\n";

    Config config2{
        .threshold = 0.8,
        .max_connections = 200
        // buffer_size和debug使用默认值
    };

    std::cout << "Config 2: buffer=" << config2.buffer_size
              << ", debug=" << std::boolalpha << config2.debug
              << ", threshold=" << config2.threshold
              << ", max_conn=" << config2.max_connections << "\n\n";

    // 4. 嵌套结构体
    std::cout << "4. 嵌套结构体:\n";

    Employee emp{
        .name = "David",
        .id = 1001,
        .address = {
            .street = "123 Main St",
            .city = "New York",
            .country = "USA"
        },
        .salary = 75000.0
    };

    std::cout << "员工: " << emp.name << " (ID: " << emp.id << ")\n";
    std::cout << "地址: " << emp.address.street << ", "
              << emp.address.city << ", " << emp.address.country << "\n";
    std::cout << "薪资: $" << emp.salary << "\n\n";

    // 5. 混合初始化风格
    std::cout << "5. 混合初始化风格:\n";

    // 传统花括号初始化
    Person p4{"Eve", 28, "eve@example.com", true};

    std::cout << "Person 4 (传统): " << p4.name << ", " << p4.age
              << ", " << p4.email << ", " << std::boolalpha << p4.active << "\n";

    // 指定初始化器
    Person p5{
        .name = "Frank",
        .age = 40
    };

    std::cout << "Person 5 (指定): " << p5.name << ", " << p5.age
              << ", " << p5.email << ", " << std::boolalpha << p5.active << "\n";

    return 0;
}