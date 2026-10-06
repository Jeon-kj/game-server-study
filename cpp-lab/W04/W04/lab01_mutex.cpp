#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

namespace
{
    constexpr int THREAD_COUNT = 4;
    constexpr int REPEAT_COUNT = 100'000;

    int counter = 0;
    std::mutex counterMutex;

    void Worker()
    {
        for (int i = 0; i < REPEAT_COUNT; ++i)
        {
            // TODO 1: counterMutex를 RAII 방식으로 잠그기
            std::lock_guard<std::mutex> lock(counterMutex);

            // TODO 2: counter를 1 증가시키기
            counter++;
        }
    }
}

void RunLab01()
{
    std::vector<std::thread> threads;

    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        threads.emplace_back(Worker);
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    const int expected = THREAD_COUNT * REPEAT_COUNT;

    std::cout << "expected: " << expected << '\n';
    std::cout << "actual:   " << counter << '\n';
}
