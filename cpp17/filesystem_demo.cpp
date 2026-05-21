/**
 * C++17 std::filesystem示例
 *
 * 演示内容：
 * - std::filesystem用于文件和目录操作
 * - 路径操作
 * - 目录遍历
 * - 文件属性和状态
 */

#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

int main() {
    std::cout << "=== C++17 std::filesystem示例 ===\n\n";

    // 1. 基本路径操作
    std::cout << "1. 基本路径操作:\n";
    fs::path p1("/home/user/documents/file.txt");
    fs::path p2("C:\\Users\\Documents\\file.txt");

    std::cout << "路径1: " << p1 << "\n";
    std::cout << "路径2: " << p2 << "\n";

    // 路径组件
    std::cout << "文件名: " << p1.filename() << "\n";
    std::cout << "扩展名: " << p1.extension() << "\n";
    std::cout << "父路径: " << p1.parent_path() << "\n";
    std::cout << "不带扩展的文件名: " << p1.stem() << "\n\n";

    // 2. 路径操作
    std::cout << "2. 路径操作:\n";
    fs::path base("/home/user");
    fs::path relative("documents/report.pdf");

    auto combined = base / relative;  // 路径拼接（使用/运算符）
    std::cout << "拼接后的路径: " << combined << "\n";

    // 追加操作
    fs::path path_append = base;
    path_append /= "pictures";      // 追加目录
    path_append /= "vacation.jpg";  // 追加文件名
    std::cout << "追加后的路径: " << path_append << "\n\n";

    // 3. 当前路径和目录操作
    std::cout << "3. 当前路径操作:\n";
    fs::path current = fs::current_path();
    std::cout << "当前路径: " << current << "\n";

    // 检查路径是否存在
    std::cout << "当前路径是否存在: " << fs::exists(current) << "\n";
    std::cout << "是否是目录: " << fs::is_directory(current) << "\n";
    std::cout << "是否是普通文件: " << fs::is_regular_file(current) << "\n\n";

    // 4. 目录遍历
    std::cout << "4. 目录遍历:\n";
    try {
        // 遍历当前目录
        for (const auto& entry : fs::directory_iterator(current)) {
            std::cout << (entry.is_directory() ? "目录 " : "文件 ")
                      << entry.path().filename() << "\n";

            // 限制输出以便阅读
            static int count = 0;
            if (++count > 10) {
                std::cout << "... (输出受限)\n";
                break;
            }
        }
    } catch (const fs::filesystem_error& ex) {
        std::cout << "文件系统错误: " << ex.what() << "\n";
    }
    std::cout << "\n";

    // 5. 文件状态和属性
    std::cout << "5. 文件属性:\n";
    try {
        auto status = fs::status(current);
        std::cout << "权限: " << static_cast<int>(status.permissions()) << "\n";

        // 文件大小（如果是普通文件）
        if (fs::is_regular_file(current)) {
            auto size = fs::file_size(current);
            std::cout << "文件大小: " << size << " 字节\n";
        }
    } catch (const fs::filesystem_error& ex) {
        std::cout << "状态错误: " << ex.what() << "\n";
    }
    std::cout << "\n";

    // 6. 路径比较和规范化
    std::cout << "6. 路径比较:\n";
    fs::path path1("/home/user/../user/documents");
    fs::path path2("/home/user/documents");

    std::cout << "路径1: " << path1 << "\n";
    std::cout << "路径2: " << path2 << "\n";
    std::cout << "相等: " << (path1 == path2) << "\n";

    // 规范化路径
    auto normalized = fs::canonical(path1);
    std::cout << "规范化后的路径: " << normalized << "\n\n";

    // 7. 临时目录和文件
    std::cout << "7. 临时路径:\n";
    fs::path temp_dir = fs::temp_directory_path();
    std::cout << "临时目录: " << temp_dir << "\n";

    // 创建临时文件路径（不实际创建文件）
    fs::path temp_file = temp_dir / "example.tmp";
    std::cout << "临时文件路径: " << temp_file << "\n\n";

    return 0;
}