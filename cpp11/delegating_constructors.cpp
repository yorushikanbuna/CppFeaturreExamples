/**
 * C++11 委托构造函数示例
 *
 * 演示内容：
 * - 构造函数委托以减少代码重复
 * - 带委托的成员初始化列表
 * - 构造函数委托中的异常处理
 * - 有效链接构造函数
 */

#include <iostream>
#include <string>
#include <stdexcept>

// 学生类，演示构造函数委托
class Student {
private:
    std::string name_;
    int age_;
    std::string major_;
    double gpa_;

public:
    // 主构造函数（执行实际工作）
    Student(const std::string& name, int age, const std::string& major, double gpa)
        : name_(name), age_(age), major_(major), gpa_(gpa) {
        std::cout << "主构造函数调用: " << name_ << "\n";

        // 验证
        if (age < 0 || age > 150) {
            throw std::invalid_argument("无效的年龄");
        }
        if (gpa < 0.0 || gpa > 4.0) {
            throw std::invalid_argument("无效的GPA");
        }
    }

    // 委托构造函数 - 调用主构造函数
    //冒号后面是委托给哪个构造函数
    Student(const std::string& name, int age)
        : Student(name, age, "未定专业", 0.0) {
        std::cout << "委托构造函数1调用: " << name_ << "\n";
    }

    // 另一个委托构造函数
    Student(const std::string& name)
        : Student(name, 18) {  // 委托给2参数构造函数
        std::cout << "委托构造函数2调用: " << name_ << "\n";
    }

    // 默认构造函数
    Student()
        : Student("未知") {  // 委托给name-only构造函数
        std::cout << "默认构造函数调用\n";
    }

    // 带异常处理的构造函数
    Student(const std::string& name, int age, bool validate)
        : Student([name, age]() -> Student {
            if (age < 0) {
                throw std::invalid_argument("年龄不能为负数");
            }
            return Student(name, age);
        }()) {
        std::cout << "带验证的构造函数调用: " << name_ << "\n";
    }

    // 获取器
    const std::string& getName() const { return name_; }
    int getAge() const { return age_; }
    const std::string& getMajor() const { return major_; }
    double getGPA() const { return gpa_; }

    // 打印学生信息
    void printInfo() const {
        std::cout << "姓名: " << name_
                  << ", 年龄: " << age_
                  << ", 专业: " << major_
                  << ", GPA: " << gpa_ << "\n";
    }
};

// 另一个更复杂的委托示例
class DatabaseConnection {
private:
    std::string host_;
    int port_;
    std::string username_;
    std::string password_;
    bool useSSL_;

public:
    // 主构造函数
    DatabaseConnection(const std::string& host, int port,
                      const std::string& username, const std::string& password,
                      bool useSSL)
        : host_(host), port_(port), username_(username),
          password_(password), useSSL_(useSSL) {
        std::cout << "创建数据库连接到 " << host_ << ":" << port_ << "\n";
    }

    // 带默认SSL设置的委托构造函数
    DatabaseConnection(const std::string& host, int port,
                      const std::string& username, const std::string& password)
        : DatabaseConnection(host, port, username, password, true) {
        std::cout << "使用默认SSL设置\n";
    }

    // 带默认端口的委托构造函数
    DatabaseConnection(const std::string& host,
                      const std::string& username, const std::string& password)
        : DatabaseConnection(host, 5432, username, password) {
        std::cout << "使用默认PostgreSQL端口\n";
    }

    // SQLite风格连接的委托构造函数
    explicit DatabaseConnection(const std::string& file_path)
        : DatabaseConnection("localhost", 0, "", "", false) {
        host_ = "file://" + file_path;  // 覆盖host
        std::cout << "SQLite风格连接到 " << host_ << "\n";
    }

    void printConnectionInfo() const {
        std::cout << "主机: " << host_
                  << ", 端口: " << port_
                  << ", 用户名: " << username_
                  << ", SSL: " << (useSSL_ ? "是" : "否") << "\n";
    }
};

int main() {
    std::cout << "=== C++11 委托构造函数示例 ===\n\n";

    // 1. 学生对象的不同构造方式
    std::cout << "1. 学生对象构造示例:\n";

    try {
        Student s1;  // 默认构造函数
        s1.printInfo();
        std::cout << "\n";

        Student s2("Alice");  // 仅name构造函数
        s2.printInfo();
        std::cout << "\n";

        Student s3("Bob", 20);  // name和age构造函数
        s3.printInfo();
        std::cout << "\n";

        Student s4("Charlie", 22, "计算机科学", 3.75);  // 完整构造函数
        s4.printInfo();
        std::cout << "\n";

        // 这会抛出异常
        // Student s5("Invalid", -5);
    } catch (const std::exception& e) {
        std::cout << "捕获异常: " << e.what() << "\n\n";
    }

    // 2. 数据库连接示例
    std::cout << "2. 数据库连接示例:\n";

    DatabaseConnection db1("localhost", 5432, "admin", "secret", true);
    db1.printConnectionInfo();
    std::cout << "\n";

    DatabaseConnection db2("remote.db.com", 3306, "user", "pass");
    db2.printConnectionInfo();
    std::cout << "\n";

    DatabaseConnection db3("simple.db.com", "readonly", "password");
    db3.printConnectionInfo();
    std::cout << "\n";

    DatabaseConnection db4("/path/to/local.db");
    db4.printConnectionInfo();
    std::cout << "\n";

    // 3. 委托构造函数的益处
    std::cout << "3. 委托构造函数的益处:\n";
    std::cout << "- 减少代码重复\n";
    std::cout << "- 集中验证逻辑\n";
    std::cout << "- 清晰的构造函数链\n";
    std::cout << "- 更容易维护\n";

    return 0;
}