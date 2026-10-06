//공유 데이터: jobs
//보호하는 mutex : jobsMutex
//소비자가 기다리는 조건 : jobs가 비어 있음
//소비자가 작업을 꺼낼 수 있는 조건 : jobs가 비어 있지 않음

#include <iostream>
#include <mutex>
#include <queue>
#include <condition_variable>

namespace
{
	std::queue<int> jobs;
	std::mutex jobsMutex;
	std::condition_variable cv;

	void Producer()
	{
		while (true)
		{
			{
				std::unique_lock<std::mutex> lock(jobsMutex);
				jobs.push(std::rand() % 100);
			}
			cv.notify_one();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}

	void Consumer()
	{
		while (true)
		{
			int data;
			{
				std::unique_lock<std::mutex> lock(jobsMutex);
				cv.wait(lock, [] { return !jobs.empty(); });

				data = jobs.front();
				jobs.pop();
			}		

			std::cout << "thread ID: " <<  std::this_thread::get_id() << std::endl;
			std::cout << "data: " << data << std::endl;
		}		
	}
}

void RunLab03()
{
	std::vector<std::thread> threads;

	for (int i = 0; i < 2; ++i)
	{
		threads.emplace_back(Producer);
	}
	for (int i = 0; i < 4; ++i)
	{
		threads.emplace_back(Consumer);
	}

	for (std::thread& thread : threads)
	{
		thread.join();
	}
}