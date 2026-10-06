#include <iostream>
#include <atomic>
#include <vector>
#include <thread>

namespace
{
	constexpr int THREAD_COUNT = 4;
	constexpr int REPEAT_COUNT = 100'000;

	std::atomic<int> counter{0};
	void Worker()
	{
		for (int i = 0; i < REPEAT_COUNT; ++i)
		{
			counter.fetch_add(1);
		}
	}
}

void RunLab02() {
	std::vector<std::thread> threads;

	for (int i = 0; i < THREAD_COUNT; ++i)
	{
		threads.push_back(std::thread(Worker));
	}

	for (std::thread& thread : threads)
	{
		thread.join();
	}

	const int expected = THREAD_COUNT * REPEAT_COUNT;

	std::cout << "expected: " << expected << std::endl;
	std::cout << "actual: " << counter.load() << std::endl;
}
