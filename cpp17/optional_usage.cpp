/**
 * C++17 std::optional示例
 *
 * 演示内容：
 * - std::optional表示可选值
 * - 安全的值处理而不会抛出异常
 * - 与现有代码的集成
 * - 最佳实践和模式
 */

#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <map>

// 可能不返回值的函数
std::optional<int> divide(int numerator, int denominator) {
    if (denominator == 0) {
        return std::nullopt;  // 没有值
    }
    return numerator / denominator;
}

// 返回可选字符串的函数
std::optional<std::string> findUser(const std::map<int, std::string>& users, int id) {
    auto it = users.find(id);
    if (it != users.end()) {
        return it->second;  // 找到用户，返回用户名
    }
    return std::nullopt;  // 未找到，返回nullopt
}

// 拥有可选成员的类
class Configuration {
private:
    std::optional<std::string> username_;
    std::optional<int> port_;
    std::optional<bool> ssl_enabled_;

public:
    void setUsername(const std::string& username) { username_ = username; }
    void setPort(int port) { port_ = port; }
    void setSSLEnabled(bool ssl) { ssl_enabled_ = ssl; }

    std::optional<std::string> getUsername() const { return username_; }
    std::optional<int> getPort() const { return port_; }
    std::optional<bool> getSSLEnabled() const { return ssl_enabled_; }
};

int main() {
    std::cout << "=== C++17 std::optional示例 ===\n\n";

    // 1. basic optional用法
    std::cout << "1. basic optional用法:\n";
    std::optional<int> opt1;  // 空optional
    std::optional<int> opt2 = 42;  // 带值的optional
    auto opt3 = std::make_optional<int>(100);  // 使用make_optional

    std::cout << "opt1是否有值: " << opt1.has_value() << "\n";
    std::cout << "opt2是否有值: " << opt2.has_value() << " 值: " << opt2.value() << "\n";
    std::cout << "opt3是否有值: " << opt3.has_value() << " 值: " << *opt3 << "\n\n";

    // 2. 安全的值访问
    std::cout << "2. 安全的值访问:\n";
    if (opt2) {
        std::cout << "opt2的值: " << *opt2 << "\n";
    }

    // 使用value_or提供默认值
    std::cout << "opt1或默认值: " << opt1.value_or(-1) << "\n";
    std::cout << "opt2或默认值: " << opt2.value_or(-1) << "\n\n";

    // 3. 返回optional的函数
    std::cout << "3. 返回optional的函数:\n";
    auto result1 = divide(10, 2);
    auto result2 = divide(10, 0);

    if (result1) {
        std::cout << "10 / 2 = " << *result1 << "\n";
    }

    if (!result2) {
        std::cout << "除以零 - 无结果\n";
    }

    // 使用value_or处理函数结果
    std::cout << "安全除法结果: " << result1.value_or(0) << "\n";
    std::cout << "安全除以零: " << result2.value_or(-1) << "\n\n";

    // 4. 与复杂类型结合
    std::cout << "4. 与复杂类型结合:\n";
    std::optional<std::vector<int>> opt_vec;
    opt_vec = std::vector<int>{1, 2, 3, 4, 5};

    if (opt_vec) {
        std::cout << "Vector内容: ";
        for (const auto& item : *opt_vec) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }

    // 5. 容器中的optional
    std::cout << "5. 容器中的optional (map查找):\n";
    std::map<int, std::string> users = {
        {1, "Alice"},
        {2, "Bob"},
        {3, "Charlie"}
    };

    auto user1 = findUser(users, 2);
    auto user2 = findUser(users, 99);

    if (user1) {
        std::cout << "找到用户: " << *user1 << "\n";
    }

    if (!user2) {
        std::cout << "用户未找到\n";
    }

    // 使用value_or进行用户查找
    std::cout << "用户1: " << user1.value_or("Unknown") << "\n";
    std::cout << "用户99: " << user2.value_or("Unknown") << "\n\n";

    // 6. 具有可选成员的类
    std::cout << "6. 具有可选成员的类:\n";
    Configuration config;
    config.setUsername("admin");
    config.setPort(8080);

    // 检查可选值
    if (auto username = config.getUsername()) {
        std::cout << "用户名: " << *username << "\n";
    }

    if (auto port = config.getPort()) {
        std::cout << "端口: " << *port << "\n";
    }

    if (auto ssl = config.getSSLEnabled()) {
        std::cout << "SSL已启用: " << std::boolalpha << *ssl << "\n";
    } else {
        std::cout << "SSL设置未配置\n";
    }

    // 使用value_or处理类成员
    std::cout << "端口 (带默认值): " << config.getPort().value_or(80) << "\n\n";

    // 7. optional赋值和重置
    std::cout << "7. optional赋值和重置:\n";
    std::optional<std::string> opt_str = "初始值";
    std::cout << "重置前: " << opt_str.value_or("None") << "\n";

    opt_str.reset();  // 移除值
    std::cout << "重置后: " << opt_str.value_or("None") << "\n";

    opt_str = "新值";
    std::cout << "赋值后: " << opt_str.value_or("None") << "\n";

    return 0;
}