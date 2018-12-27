#pragma once

#include <function>

class raii_tail_call {
public:
	raii_tail_call(std::function<void()> &&callable)
			: m_callable(std::move(callable)) {}

	raii_tail_call(raii_tail_call &&rhs) noexcept = default;
	raii_tail_call(raii_tail_call const &) = delete;

	raii_tail_call &operator=(raii_tail_call &&) noexcept = default;
	raii_tail_call &operator=(raii_tail_call const &) = delete;
	raii_tail_call &operator=(std::function<void()> &&callable) noexcept {
		m_callable = callable;
		return *this;
	}

	~raii_tail_call() {
		if (m_callable)
			m_callable();
	}

private:
	std::function<void()> m_callable;
}; 
