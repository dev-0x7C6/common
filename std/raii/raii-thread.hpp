#pragma once

#include <atomic>
#include <functional>
#include <thread>

class raii_thread {
public:
	raii_thread(std::function<void(const std::atomic_bool &interrupted)> &&callable)
			: m_thread([this, callable{std::move(callable)}]() { callable(m_interrupted); }) {
	}

	void interrupt() {
		m_interrupted = true;
	}

	void join() {
		m_thread.join();
	}

	~raii_thread() {
		interrupt();
		join();
	}

private:
	std::thread m_thread;
	std::atomic_bool m_interrupted{false};
};
