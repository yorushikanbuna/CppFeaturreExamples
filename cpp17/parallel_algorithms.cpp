/**
 * C++17 并行算法示例
 *
 * 演示内容：
 * - 并行执行策略
 * - 使用并行执行的标准算法
 * - 性能比较
 * - 线程安全考虑
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <execution>
#include <random>

// 辅助函数：生成测试数据
std::vector<int> generateRandomData(size_t size) {
    std::vector<int> data(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);

    for (auto& val : data) {
        val = dis(gen);
    }
    return data;
}

// 计时辅助函数
template<typename Func>
auto timeExecution(Func&& func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

int main() {
    std::cout << "=== C++17 并行算法示例 ===\n\n";

    // 生成测试数据
    const size_t dataSize = 1000000;
    auto data = generateRandomData(dataSize);
    std::cout << "生成了 " << dataSize << " 个随机数\n\n";

    // 1. 顺序 vs 并行排序
    std::cout << "1. 排序性能对比:\n";
    auto seq_data = data;
    auto par_data = data;

    auto seq_sort_time = timeExecution([&seq_data]() {
        std::sort(seq_data.begin(), seq_data.end());  // 顺序排序
    });

    auto par_sort_time = timeExecution([&par_data]() {
        std::sort(std::execution::par, par_data.begin(), par_data.end());  // 并行排序
    });

    std::cout << "顺序排序耗时: " << seq_sort_time.count() << " 毫秒\n";
    std::cout << "并行排序耗时: " << par_sort_time.count() << " 毫秒\n";
    if (par_sort_time.count() > 0) {
        std::cout << "加速比: " << static_cast<double>(seq_sort_time.count()) / par_sort_time.count() << "x\n\n";
    }

    // 2. 并行归约
    std::cout << "2. 并行归约:\n";
    auto seq_sum_time = timeExecution([&seq_data]() {
        auto sum = std::accumulate(seq_data.begin(), seq_data.end(), 0LL);
        std::cout << "顺序求和: " << sum << "\n";
    });

    auto par_sum_time = timeExecution([&par_data]() {
        auto sum = std::reduce(std::execution::par, par_data.begin(), par_data.end(), 0LL);
        std::cout << "并行求和: " << sum << "\n";
    });

    std::cout << "顺序求和耗时: " << seq_sum_time.count() << " 毫秒\n";
    std::cout << "并行求和耗时: " << par_sum_time.count() << " 毫秒\n\n";

    // 3. 并行变换
    std::cout << "3. 并行变换:\n";
    auto transform_data = data;

    auto seq_transform_time = timeExecution([&transform_data]() {
        std::transform(transform_data.begin(), transform_data.end(), transform_data.begin(),
                      [](int x) { return x * 2; });
    });

    auto par_transform_time = timeExecution([&transform_data]() {
        std::transform(std::execution::par, transform_data.begin(), transform_data.end(),
                      transform_data.begin(), [](int x) { return x * 2; });
    });

    std::cout << "顺序变换耗时: " << seq_transform_time.count() << " 毫秒\n";
    std::cout << "并行变换耗时: " << par_transform_time.count() << " 毫秒\n\n";

    // 4. 并行搜索操作
    std::cout << "4. 并行搜索:\n";
    int search_value = 500;

    auto seq_find_time = timeExecution([&seq_data, search_value]() {
        auto it = std::find(seq_data.begin(), seq_data.end(), search_value);
        bool found = (it != seq_data.end());
        std::cout << "顺序搜索找到: " << std::boolalpha << found << "\n";
    });

    auto par_find_time = timeExecution([&par_data, search_value]() {
        auto it = std::find(std::execution::par, par_data.begin(), par_data.end(), search_value);
        bool found = (it != par_data.end());
        std::cout << "并行搜索找到: " << std::boolalpha << found << "\n";
    });

    std::cout << "顺序查找耗时: " << seq_find_time.count() << " 毫秒\n";
    std::cout << "并行查找耗时: " << par_find_time.count() << " 毫秒\n\n";

    // 5. 执行策略
    std::cout << "5. 执行策略:\n";
    std::vector<int> small_data = {5, 2, 8, 1, 9, 3, 7, 4, 6};

    // 顺序执行 - 单线程，不向量化
    std::sort(std::execution::seq, small_data.begin(), small_data.end());
    std::cout << "顺序排序结果: ";
    for (const auto& val : small_data) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // 并行执行 - 多线程
    std::sort(std::execution::par, small_data.begin(), small_data.end());
    std::cout << "并行排序结果: ";
    for (const auto& val : small_data) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // 并行无序执行 - 可能使用SIMD指令
    std::sort(std::execution::par_unseq, small_data.begin(), small_data.end());
    std::cout << "并行无序排序结果: ";
    for (const auto& val : small_data) {
        std::cout << val << " ";
    }
    std::cout << "\n\n";

    // 6. 线程安全考虑
    std::cout << "6. 线程安全:\n";
    std::vector<int> shared_data(1000, 1);
    std::vector<int> result(1000);

    // 安全的并行操作 - 没有共享的可变状态
    std::transform(std::execution::par, shared_data.begin(), shared_data.end(),
                  result.begin(), [](int x) { return x * 2; });

    // 统计结果
    auto count = std::count(std::execution::par, result.begin(), result.end(), 2);
    std::cout << "结果中2的个数: " << count << "\n";

    return 0;
}