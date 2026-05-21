/**
 * C++14 数字分隔符示例
 *
 * 演示内容：
 * - 数字分隔符语法（单引号'）
 * - 改进大数字的可读性
 * - 不同进制下的使用
 * - 实际应用
 */

#include <iostream>
#include <iomanip>
#include <bitset>

int main() {
    std::cout << "=== C++14 数字分隔符示例 ===\n\n";

    // 1. 带数字分隔符的十进制数
    std::cout << "1. 十进制数字:\n";
    auto million = 1'000'000;       // 100万
    auto billion = 1'000'000'000;   // 10亿
    auto large_number = 123'456'789;

    std::cout << "百万: " << million << "\n";
    std::cout << "十亿: " << billion << "\n";
    std::cout << "大数字: " << large_number << "\n\n";

    // 2. 浮点数
    std::cout << "2. 浮点数:\n";
    auto pi = 3.141'592'653'589'793;      // 圆周率
    auto avogadro = 6.022'140'857e23;     // 阿伏伽德罗常数

    std::cout << std::fixed << std::setprecision(15);
    std::cout << "圆周率: " << pi << "\n";
    std::cout << std::scientific;
    std::cout << "阿伏伽德罗常数: " << avogadro << "\n\n";

    // 3. 十六进制数
    std::cout << "3. 十六进制数:\n";
    std::cout << std::hex << std::showbase;
    auto hex_color = 0xFF'AA'33;      // 橙色
    auto memory_address = 0xDEAD'BEEF; // 经典的调试内存标记
    auto rgb_mask = 0x00'FF'00'00;    // 红色组件掩码

    std::cout << "十六进制颜色: " << hex_color << "\n";
    std::cout << "内存地址: " << memory_address << "\n";
    std::cout << "RGB红色掩码: " << rgb_mask << "\n\n";

    // 4. 二进制数
    std::cout << "4. 二进制数:\n";
    std::cout << std::dec;  // 重置为十进制
    auto bitmask = 0b1010'0101'1100'1111;
    auto pattern = 0b1111'0000'1111'0000;

    std::cout << "位掩码: " << std::bitset<16>(bitmask) << "\n";
    std::cout << "模式: " << std::bitset<16>(pattern) << "\n\n";

    // 5. 八进制数
    std::cout << "5. 八进制数:\n";
    auto oct_permissions = 0755;  // Unix权限：rwxr-xr-x
    auto oct_file_mode = 0644;    // Unix权限：rw-r--r--

    std::cout << std::oct << std::showbase;
    std::cout << "目录权限: " << oct_permissions << "\n";
    std::cout << "文件权限: " << oct_file_mode << "\n\n";

    // 6. 金融计算示例
    std::cout << "6. 金融计算:\n";
    std::cout << std::dec << std::fixed << std::setprecision(2);

    // 大额货币金额
    auto national_debt = 28'000'000'000.00;  // 280亿美元
    auto company_revenue = 5'750'000'000.00;  // 57.5亿美元
    auto transaction_id = 123'456'789'012ULL;  // 大ID号

    std::cout << "国债: $" << national_debt << "\n";
    std::cout << "公司收入: $" << company_revenue << "\n";
    std::cout << "交易ID: " << transaction_id << "\n\n";

    // 7. 科学常数
    std::cout << "7. 科学常数:\n";
    auto speed_of_light = 299'792'458.0;  // m/s
    auto planck_constant = 6.626'070'15e-34;  // J·s

    std::cout << std::scientific;
    std::cout << "光速: " << speed_of_light << " m/s\n";
    std::cout << "普朗克常数: " << planck_constant << " J·s\n\n";

    // 8. 多个连续分隔符（允许的）
    std::cout << "8. 多个连续分隔符:\n";
    auto strange_number = 1'000'000;  // 100万（正确写法）
    std::cout << "奇怪的数字: " << strange_number << "\n\n";

    // 9. 位置限制说明
    std::cout << "9. 位置限制说明:\n";
    std::cout << "- 分隔符不能位于数字开头或结尾\n";
    std::cout << "- 分隔符不能靠近小数点\n";
    std::cout << "- 以下写法会导致编译错误:\n";
    std::cout << "  auto invalid1 = '1000;     // 错误：开头有分隔符\n";
    std::cout << "  auto invalid2 = 1000';     // 错误：结尾有分隔符\n";
    std::cout << "  auto invalid3 = 3.'14;     // 错误：靠近小数点\n";
    std::cout << "  auto invalid4 = 3.14';     // 错误：分数部分结尾有分隔符\n";

    return 0;
}