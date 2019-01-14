#pragma once

class raii_painter {
public:
	raii_painter(QPainter *painter)
			: m_painter(painter) {
		m_painter->save();
	};

	raii_painter(raii_painter const &) = delete;
	raii_painter(raii_painter &&) noexcept = delete;

	raii_painter &operator=(raii_painter const &) = delete;
	raii_painter &operator=(raii_painter &&) noexcept = delete;

	~raii_painter() {
		m_painter->restore();
	}

private:
	QPainter *m_painter{nullptr};
};
