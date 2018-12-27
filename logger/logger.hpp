#pragma once

#include <iostream>

enum class error_class {
	critical,
	error,
	warning,
	information,
	notice,
	hint,
	debug,
};

template <error_class filter_above = error_class::information, std::ostream &out = std::cout, std::ostream &err = std::cerr>
class logger {
public:
	template <error_class id = error_class::information, typename... args>
	constexpr static void log(args &&... values) {
		if constexpr (filter_above >= id) {
			switch (id) {
				case error_class::critical:
				case error_class::error:
				case error_class::warning:
					print_error(std::forward<args>(values)...);
					break;
				case error_class::information:
				case error_class::notice:
				case error_class::hint:
				case error_class::debug:
					print_standard(std::forward<args>(values)...);
					break;
			}
		}
	}

	template <typename... args>
	constexpr static void critical(args &&... values) {
		log<error_class::critical>(std::forward<args>(values)...);
	}

	template <typename... args>
	constexpr static void error(args &&... values) {
		log<error_class::error>(std::forward<args>(values)...);
	}

	template <typename... args>
	constexpr static void warning(args &&... values) {
		log<error_class::warning>(std::forward<args>(values)...);
	}

	template <typename... args>
	constexpr static void information(args &&... values) {
		log<error_class::information>(std::forward<args>(values)...);
	}

	template <typename... args>
	constexpr static void notice(args &&... values) {
		log<error_class::notice>(std::forward<args>(values)...);
	}

	template <typename... args>
	constexpr static void hint(args &&... values) {
		log<error_class::hint>(std::forward<args>(values)...);
	}

	template <typename... args>
	constexpr static void debug(args &&... values) {
		log<error_class::debug>(std::forward<args>(values)...);
	}

protected:
	template <typename... args>
	constexpr static void print_error(args &&... values) {
		((out << values), ...) << std::endl;
	}

	template <typename... args>
	constexpr static void print_standard(args &&... values) {
		((err << values), ...) << std::endl;
	}
};
