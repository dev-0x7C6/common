#pragma once

template <typename type, auto initial_state, auto final_state>
class raii_value_assigment {
public:
	raii_value_assigment()
			: m_value(initial_state) {
	}

	~raii_value_assigment() {
		m_value = final_state;
	}

	auto &value() noexcept { return m_value; }

private:
	type m_value;
};
