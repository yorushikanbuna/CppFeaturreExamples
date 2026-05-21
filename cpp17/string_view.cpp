/**
 * C++17 std::string_view示例
 *
 * 演示内容：
 * - std::string_view用于高效字符串处理
 * - 零拷贝子字符串操作
 * - 与现有字符串API的集成
 * - 性能优势
 */

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

// 接受string_view的函数，提高效率
void printStringInfo(std::string_view sv) {
    std::cout << "长度: " << sv.length() << "\n";
    std::cout << "内容: " << sv << "\n";
    std::cout << "第一个字符: " << (sv.empty() ? ' ' : sv[0]) << "\n";
    std::cout << "最后一个字符: " << (sv.empty() ? ' ' : sv[sv.length()-1]) << "\n\n";
}

// 演示零拷贝操作的函数
std::string_view getSubstring(std::string_view sv, size_t pos, size_t len) {
    return sv.substr(pos, len);
}

// 高效比较字符串的函数
bool contains(std::string_view haystack, std::string_view needle) {
    return haystack.find(needle) != std::string_view::npos;
}

int main() {
    std::cout << "=== C++17 std::string_view示例 ===\n\n";

    // 1. 基本string_view用法
    std::cout << "1. 基本string_view用法:\n";
    std::string str = "Hello, World!";
    std::string_view sv1(str);  // 字符串的视图
    std::string_view sv2("字面量字符串");  // 字符串字面量的视图
    std::string_view sv3 = str;  // 隐式转换

    printStringInfo(sv1);
    printStringInfo(sv2);
    printStringInfo(sv3);

    // 2. 零拷贝子字符串操作
    std::cout << "2. 零拷贝子字符串操作:\n";
    std::string long_string = "The quick brown fox jumps over the lazy dog";
    std::string_view long_sv(long_string);

    auto fox = getSubstring(long_sv, 16, 3);  // "fox"
    auto dog = getSubstring(long_sv, 40, 3);  // "dog"

    std::cout << " Fox: " << fox << "\n";
    std::cout << " Dog: " << dog << "\n\n";

    // 3. 比较操作
    std::cout << "3. 比较操作:\n";
    std::string_view apple("apple");
    std::string_view Apple("Apple");

    std::cout << "apple == Apple: " << (apple == Apple) << "\n";
    std::cout << "apple < Apple: " << (apple < Apple) << "\n";  // 区分大小写
    std::cout << "\n";

    // 4. 搜索操作
    std::cout << "4. 搜索操作:\n";
    std::string_view text("Hello, this is a sample text for searching");

    std::cout << "包含'sample': " << contains(text, "sample") << "\n";
    std::cout << "包含'missing': " << contains(text, "missing") << "\n";

    auto pos = text.find("text");
    if (pos != std::string_view::npos) {
        std::cout << "找到'text'的位置: " << pos << "\n";
    }
    std::cout << "\n";

    // 5. 容器中的string_view
    std::cout << "5. 容器中的string_view:\n";
    std::vector<std::string_view> words = {
        "apple", "banana", "cherry", "date", "elderberry"
    };

    // 排序时不复制字符串
    std::sort(words.begin(), words.end());

    std::cout << "排序后的单词:\n";
    for (const auto& word : words) {
        std::cout << "- " << word << "\n";
    }
    std::cout << "\n";

    // 6. 性能优势演示
    std::cout << "6. 性能优势:\n";
    std::string large_string(1000, 'A');  // 大字符串
    large_string += "END";

    // 创建string_view是O(1) - 不复制
    std::string_view large_view(large_string);
    std::string_view end_marker = getSubstring(large_view, 1000, 3);

    std::cout << "结束标记: " << end_marker << "\n";
    std::cout << "视图长度: " << large_view.length() << "\n";
    std::cout << "这些操作中没有发生拷贝！\n\n";

    // 7. string_view与字符串字面量
    std::cout << "7. string_view与字符串字面量:\n";
    // 不创建临时字符串
    auto process_literal = [](std::string_view sv) {
        return sv.length();
    };

    size_t len = process_literal("这是一个非常长的字符串字面量");
    std::cout << "字面量长度: " << len << "\n\n";

    // 8. 移除前缀和后缀
    std::cout << "8. 移除前缀和后缀:\n";
    std::string_view path("/usr/local/bin/application.exe");

    // 移除开头的斜杠
    auto trimmed = path;
    trimmed.remove_prefix(1);
    std::cout << "移除开头斜杠: " << trimmed << "\n";

    // 移除文件扩展名
    trimmed.remove_suffix(4);  // 移除".exe"
    std::cout << "移除扩展名: " << trimmed << "\n\n";

    return 0;
}