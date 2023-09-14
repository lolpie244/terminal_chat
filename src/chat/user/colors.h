#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>

namespace user
{
	constexpr std::string colors[] = {
		"\e[0;30m", "\e[0;31m", "\e[0;32m", "\e[0;33m", "\e[0;34m", "\e[0;35m",
		"\e[0;36m", "\e[1;30m", "\e[1;31m", "\e[1;32m", "\e[1;33m", "\e[1;34m",
		"\e[1;35m", "\e[1;36m", "\e[4;30m", "\e[4;31m", "\e[4;32m", "\e[4;33m",
		"\e[4;34m", "\e[4;35m", "\e[4;36m"
	};

	constexpr std::string default_color = "\e[0m";

	inline std::string get_random_color()
	{
		srand(time(nullptr));
		int colors_count = sizeof(colors) / sizeof(colors[0]);

		return colors[rand() % colors_count];
	}
} // namespace user
