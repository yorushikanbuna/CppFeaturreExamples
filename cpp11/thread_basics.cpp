/**
 * C++11 线程基础示例
 *
 * 演示内容：
 * - 基本线程创建和等待（join）
 * - 向线程传递参数
 * - 共享数据和互斥锁保护
 * - 条件变量
 * - 异步任务和future
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <vector>
#include <chrono>

// 全局共享数据和同步原语
int shared_counter = 0;
std::mutex counter_mutex;  // 保护共享计数器的互斥量
std::condition_variable cv;  // 条件变量
bool ready = false;  // 通知标志

// 工作线程函数
void worker(int id, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        // 使用锁保护共享数据
        {
            std::lock_guard<std::mutex> lock(counter_mutex);
            ++shared_counter;
            std::cout << "线程 " << id << " 将计数器增加到 " << shared_counter << "\n";
        } // 锁在此处自动释放

        // 模拟工作
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// 条件变量等待函数
void waiter(int id) {
    std::unique_lock<std::mutex> lock(counter_mutex);
    std::cout << "线程 " << id << " 开始等待...\n";
    // 等待条件变量，直到ready为true
    cv.wait(lock, []{ return ready; });
    std::cout << "线程 " << id << " 收到通知!\n";
}

// 异步计算函数
int compute_square(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(1));  // 模拟耗时计算
    return x * x;
}

int main() {
    std::cout << "=== C++11 线程基础示例 ===\n\n";

    // 1. 基本线程创建
    std::cout << "1. 基本线程创建:\n";
    std::thread t1(worker, 1, 3);  // 线程1，执行3次
    std::thread t2(worker, 2, 3);  // 线程2，执行3次

    // 等待线程完成（join）
    t1.join();
    t2.join();
    std::cout << "最终计数器值: " << shared_counter << "\n";
    std::cout << "注意：由于线程竞争，输出顺序可能不同\n\n";

    // 2. 条件变量使用
    std::cout << "2. 条件变量使用:\n";
    std::thread notifier([](){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        {
            std::lock_guard<std::mutex> lock(counter_mutex);
            ready = true;
            std::cout << "通知线程设置 ready = true\n";
        }
        cv.notify_all();  // 通知所有等待的线程
    });

    std::thread waiter1(waiter, 3);
    std::thread waiter2(waiter, 4);

    notifier.join();
    waiter1.join();
    waiter2.join();
    std::cout << "\n";

    // 3. 异步和future
    std::cout << "3. 异步任务和future:\n";
    auto start = std::chrono::high_resolution_clock::now();

    // 启动异步任务
    std::future<int> f1 = std::async(std::launch::async, compute_square, 5);
    std::future<int> f2 = std::async(std::launch::async, compute_square, 8);
    std::future<int> f3 = std::async(std::launch::async, compute_square, 12);

    // 获取结果（会阻塞直到计算完成）
    int result1 = f1.get();
    int result2 = f2.get();
    int result3 = f3.get();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "结果: " << result1 << ", " << result2 << ", " << result3 << "\n";
    std::cout << "总耗时: " << duration.count() << " 毫秒\n";
    std::cout << "注意：由于并行执行，耗时少于3秒（3个1秒计算同时进行）\n\n";

    // 4. 线程安全的容器操作
    std::cout << "4. 线程安全的vector操作:\n";
    std::vector<int> safe_vector;
    std::mutex vector_mutex;

    // 启动多个线程修改vector
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&safe_vector, &vector_mutex, i]() {
            for (int j = 0; j < 3; ++j) {
                std::lock_guard<std::mutex> lock(vector_mutex);
                safe_vector.push_back(i * 10 + j);
                std::cout << "线程 " << i << " 添加 " << (i * 10 + j) << "\n";
            }
        });
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Vector最终内容: ";
    for (int val : safe_vector) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    return 0;
}