#pragma once

#include <utility>

template <typename type, auto initial_state, auto final_state>
class raii_value_assigment {
public:
	raii_value_assigment()
			: m_value(initial_state) {}

	raii_value_assigment(const raii_value_assigment &) = delete;
	raii_value_assigment &operator=(const raii_value_assigment &) = delete;

	raii_value_assigment(raii_value_assigment &&rhs) noexcept
			: m_value(std::move(rhs.m_value)) {
		rhs.m_moved = true;
	}

	raii_value_assigment &operator=(raii_value_assigment &&rhs) noexcept {
		rhs.m_value = std::move(rhs);
		rhs.m_moved = true;
	}

	~raii_value_assigment() {
		if (!m_moved)
			m_value = final_state;
	}

	constexpr operator type &() noexcept {
		return m_value;
	}

private:
	type m_value;
	bool m_moved{false};
};
