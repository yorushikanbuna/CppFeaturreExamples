/**
 * C++11 智能指针示例
 *
 * 演示内容：
 * - std::unique_ptr：独占所有权，一个资源只能有一个拥有者
 * - std::shared_ptr：共享所有权，多个指针可以共享同一个资源
 * - std::weak_ptr：弱引用，用于打破循环引用
 * - 自定义删除器
 */

#include <iostream>
#include <memory>

// 资源类，模拟需要管理的资源
class Resource {
public:
    Resource() { std::cout << "资源已获取\n"; }
    ~Resource() { std::cout << "资源已释放\n"; }
    void use() const { std::cout << "使用资源\n"; }
};

// 使用unique_ptr作为参数的类，演示所有权转移
class Processor {
public:
    // explicit防止隐式转换，使用unique_ptr表示获取资源所有权
    explicit Processor(std::unique_ptr<Resource> res)
        : resource(std::move(res)) {}

    void process() {
        if (resource) {
            resource->use();
        }
    }

private:
    std::unique_ptr<Resource> resource;
};

int main() {
    std::cout << "=== C++11 智能指针示例 ===\n\n";

    // 1. unique_ptr示例 - 独占所有权
    std::cout << "1. unique_ptr示例 - 独占所有权:\n";
    {
        // make_unique是创建unique_ptr的安全方式
        std::unique_ptr<Resource> res1 = std::make_unique<Resource>();
        res1->use();  // 使用资源

        // 所有权转移：使用std::move将res1的所有权转移给res2
        // 转移后res1变为nullptr，不能再使用
        std::unique_ptr<Resource> res2 = std::move(res1);
        // res1->use();  // 错误！res1已经是nullptr

        Processor processor(std::move(res2));
        processor.process();
    } // 在这里资源被自动释放，因为processor析构时会释放unique_ptr
    std::cout << "\n";

    // 2. shared_ptr示例 - 共享所有权
    std::cout << "2. shared_ptr示例 - 共享所有权:\n";
    {
        // make_shared是创建shared_ptr的安全方式
        auto sharedRes = std::make_shared<Resource>();

        // 多个shared_ptr可以指向同一个资源
        std::shared_ptr<Resource> s1 = sharedRes;  // 引用计数+1
        std::shared_ptr<Resource> s2 = sharedRes;  // 引用计数+1

        std::cout << "当前引用计数: " << sharedRes.use_count() << "\n";

        s1->use();
        s2->use();

        // 当shared_ptr离开作用域时，引用计数减少
        // 当引用计数为0时，资源被自动释放
    } // 在这里引用计数变为0，资源被释放
    std::cout << "\n";

    // 3. weak_ptr示例 - 打破循环引用
    std::cout << "3. weak_ptr示例 - 打破循环引用:\n";
    {
        auto shared = std::make_shared<Resource>();
        // weak_ptr不增加引用计数，仅提供观察访问
        std::weak_ptr<Resource> weak = shared;

        // 使用lock()检查资源是否还存在，并获取shared_ptr
        if (auto locked = weak.lock()) {
            locked->use();
            std::cout << "通过weak_ptr访问，引用计数: " << locked.use_count() << "\n";
        } else {
            std::cout << "资源已被释放\n";
        }

        std::cout << "shared引用计数: " << shared.use_count() << "\n";
        std::cout << "weak_ptr不会增加引用计数，所以共享引用计数仍为1\n";
    }
    std::cout << "\n";

    // 4. 自定义删除器示例
    std::cout << "4. 自定义删除器示例:\n";
    {
        // 自定义删除器：在删除资源前执行特殊清理操作
        auto customDeleter = [](Resource* r) {
            std::cout << "删除前执行自定义清理\n";
            delete r;
        };

        // 声明unique_ptr时指定删除器类型
        std::unique_ptr<Resource, decltype(customDeleter)>
            customRes(new Resource(), customDeleter);

        customRes->use();
    }  // 这里会使用自定义删除器释放资源
    std::cout << "\n";

    return 0;
}