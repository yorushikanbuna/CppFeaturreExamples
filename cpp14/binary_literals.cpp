/**
 * C++14 二进制字面量示例
 *
 * 演示内容：
 * - 二进制字面量语法（0b前缀）
 * - 位操作中的使用
 * - 与十六进制/八进制的比较
 * - 实际应用
 */

#include <iostream>
#include <bitset>

int main() {
    std::cout << "=== C++14 二进制字面量示例 ===\n\n";

    // 1. 基本二进制字面量
    std::cout << "1. 基本二进制字面量:\n";
    auto binary1 = 0b1010;        // 10的二进制
    auto binary2 = 0b11110000;    // 240的二进制
    auto binary3 = 0b1111'1111;   // 255的二进制（带数字分隔符）

    std::cout << "0b1010 = " << binary1 << "\n";
    std::cout << "0b11110000 = " << binary2 << "\n";
    std::cout << "0b1111'1111 = " << binary3 << "\n\n";

    // 2. 使用二进制字面量进行位操作
    std::cout << "2. 位操作:\n";
    unsigned char flags = 0b00000000;  // 初始化为0

    // 设置一些位
    flags |= 0b00001111;  // 设置低4位
    std::cout << "设置低4位后: " << std::bitset<8>(flags) << "\n";

    // 清除一些位
    flags &= 0b11110000;  // 清除低4位
    std::cout << "清除低4位后: " << std::bitset<8>(flags) << "\n";

    // 翻转位
    flags ^= 0b10101010;  // 翻转交替位
    std::cout << "翻转交替位后: " << std::bitset<8>(flags) << "\n\n";

    // 3. 与其他进制的比较
    std::cout << "3. 与其他进制的比较:\n";
    auto hex_val = 0xFF;      // 十六进制
    auto oct_val = 0377;      // 八进制
    auto bin_val = 0b11111111; // 二进制

    std::cout << "十六进制 0xFF = " << hex_val << "\n";
    std::cout << "八进制 0377 = " << oct_val << "\n";
    std::cout << "二进制 0b11111111 = " << bin_val << "\n";
    std::cout << "全部相等: " << (hex_val == oct_val && oct_val == bin_val) << "\n\n";

    // 4. 实际应用：位标志
    std::cout << "4. 实际应用 - 位标志:\n";

    // 定义文件权限的位标志
    const auto READ_FLAG    = 0b001;    // 读权限
    const auto WRITE_FLAG   = 0b010;    // 写权限
    const auto EXECUTE_FLAG = 0b100;    // 执行权限

    auto user_permissions = READ_FLAG | WRITE_FLAG;        // 读+写
    auto admin_permissions = READ_FLAG | WRITE_FLAG | EXECUTE_FLAG;  // 全部权限

    std::cout << "用户权限: " << std::bitset<3>(user_permissions) << "\n";
    std::cout << "管理员权限: " << std::bitset<3>(admin_permissions) << "\n";

    // 检查权限
    bool can_read = user_permissions & READ_FLAG;
    bool can_execute = user_permissions & EXECUTE_FLAG;

    std::cout << "用户可读: " << (can_read ? "是" : "否") << "\n";
    std::cout << "用户可执行: " << (can_execute ? "是" : "否") << "\n\n";

    // 5. 位提取和操作
    std::cout << "5. 位提取和操作:\n";
    auto config_byte = 0b1010'0101;  // 配置字节
    std::cout << "配置字节: " << std::bitset<8>(config_byte) << "\n";

    // 提取特定的位
    auto lower_nibble = config_byte & 0b0000'1111;  // 低4位
    auto upper_nibble = (config_byte & 0b1111'0000) >> 4;  // 高4位

    std::cout << "低半字节: " << std::bitset<4>(lower_nibble) << " (" << lower_nibble << ")\n";
    std::cout << "高半字节: " << std::bitset<4>(upper_nibble) << " (" << upper_nibble << ")\n\n";

    return 0;
}