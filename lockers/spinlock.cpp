#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

// 利用原子锁实现自旋锁
class SpinLock {
public:
    SpinLock() : flag_(false) { }

    void lock()
    {
        bool expect = false;
        while (!flag_.compare_exchange_weak(expect, true)) {
            // 这里一定要将expect复原，执行失败时expect结果是未定的
            expect = false;
        }
    }

    void unlock() { flag_.store(false); }

private:
    std::atomic<bool> flag_;
};

// 每个线程自增次数
static const int kIncNum = 1000000;
// 线程数
static const int kWorkerNum = 10;
// 自增计数器
static int count = 0;
// 自旋锁
SpinLock spinLock;
// 每个线程的工作函数
void IncCounter()
{
    for (int i = 0; i < kIncNum; ++i) {
        spinLock.lock();
        count++;
        spinLock.unlock();
    }
}

void testSpinLock() {
    std::vector<std::thread> workers;
    std::cout << "SpinLock inc MyTest start" << std::endl;
    count = 0;

    std::cout << "start " << kWorkerNum << " workers_"
              << "every worker inc " << kIncNum << std::endl;
    std::cout << "count_: " << count << std::endl;
    // 创建10个工作线程进行自增操作
    for (int i = 0; i < kWorkerNum; ++i)
        workers.push_back(std::move(std::thread(IncCounter)));

    for (auto it = workers.begin(); it != workers.end(); it++)
        it->join();

    std::cout << "workers_ end" << std::endl;
    std::cout << "count_: " << count << std::endl;
    // 验证结果
    if (count == kIncNum * kWorkerNum) {
        std::cout << "SpinLock inc MyTest passed" << std::endl;
    } else {
        std::cout << "SpinLock inc MyTest failed" << std::endl;
    }
}