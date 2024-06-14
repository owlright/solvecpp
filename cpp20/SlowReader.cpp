#include <coroutine>
#include <iostream>
#include <memory>
#include <thread>

// 好神奇，IntReader不用继承任何东西，只要实现了await_ready, await_suspend, await_resume这3个同名函数就行了？
class IntReader {
public:
    bool await_ready() { return false; }

    void await_suspend(std::coroutine_handle<> handle)
    {

        std::thread thread([this, handle]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % 1000));
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            value_ = std::rand();
            handle.resume();
        });

        thread.detach();
    }

    unsigned int await_resume() { return value_; }

private:
    unsigned int value_ {};
};

class Task {
public:
    class promise_type {
    public:
        promise_type() : value_(std::make_shared<int>()) { }
        Task get_return_object() { return Task { value_ }; }
        void return_value(int value) { *value_ = value; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() { }
        // void return_void() { }

    private:
        std::shared_ptr<int> value_;
    };

public:
    Task(const std::shared_ptr<int>& value) : value_(value) { }

    int GetValue() const { return *value_; }

private:
    std::shared_ptr<int> value_;
};

Task PrintInt()
{

    IntReader reader1;
    int64_t total = co_await reader1;
    std::cout << "第一个数 " << total << std::endl;
    IntReader reader2;
    auto tmp_ = co_await reader2;
    std::cout << "第二个数 " << tmp_ << std::endl;
    total += tmp_;
    IntReader reader3;
    tmp_ = co_await reader3;
    std::cout << "第三个数 " << tmp_ << std::endl;
    total += tmp_;

    std::cout << total << std::endl;
}

Task GetInt()
{

    IntReader reader1;
    int64_t total = co_await reader1;

    IntReader reader2;
    total += co_await reader2;

    IntReader reader3;
    total += co_await reader3;

    co_return total;
}
int main()
{

    // PrintInt();

    // std::string line;
    // while (std::cin >> line) { }
    auto total = GetInt();
    std::cin.get();
    std::cout << "total: " << total.GetValue() << std::endl;

    return 0;
}