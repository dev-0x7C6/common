#pragma once

class resolution {
public:
	using resolution_unit = int;

	enum class aspect_ratio {
		_16_9,
		_16_10,
		_4_3,
		other
	};

	constexpr resolution(resolution_unit w, resolution_unit h)
			: m_w(w)
			, m_h(h) {}
	constexpr auto width() const noexcept { return m_w; }
	constexpr auto height() const noexcept { return m_h; }

	constexpr auto aspect() const noexcept {
		if ((m_w * 9) / 16 == m_h)
			return aspect_ratio::_16_9;

		if ((m_w * 3) / 4 == m_h)
			return aspect_ratio::_4_3;

		if ((m_w * 10) / 16 == m_h)
			return aspect_ratio::_16_10;

		return aspect_ratio::other;
	}

	constexpr auto is_aspect_16_9() const noexcept {
		return aspect_ratio::_16_9 == aspect();
	}

	constexpr auto is_aspect_16_10() const noexcept {
		return aspect_ratio::_16_10 == aspect();
	}

	constexpr auto is_aspect_4_3() const noexcept {
		return aspect_ratio::_4_3 == aspect();
	}

	constexpr auto is_valid() const noexcept {
		return (m_w == 0) && (m_h == 0);
	}

	friend constexpr auto operator==(const resolution &lhs, const resolution &rhs) noexcept {
		return lhs.m_w == rhs.m_w && lhs.m_h == rhs.m_h;
	}

	friend constexpr auto operator!=(const resolution &lhs, const resolution &rhs) noexcept {
		return !operator==(lhs, rhs);
	}

	friend constexpr auto operator<(const resolution &lhs, const resolution &rhs) noexcept {
		return (lhs.m_w * lhs.m_h) < (rhs.m_w * rhs.m_h);
	}

private:
	resolution_unit m_w{};
	resolution_unit m_h{};
};
