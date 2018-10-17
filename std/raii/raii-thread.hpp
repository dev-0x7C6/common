#pragma once

#include <atomic>
#include <functional>
#include <thread>

class raii_thread {
public:
	raii_thread(std::function<void(const std::atomic_bool &interrupted)> &&callable)
			: m_thread([this, callable{std::move(callable)}]() { callable(m_interrupted); }) {
	}

	~raii_thread() {
		m_interrupted = true;
		m_thread.join();
	}

private:
	std::thread m_thread;
	std::atomic_bool m_interrupted{false};
};
