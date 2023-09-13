#pragma once

#include <string>

namespace chat {
	using std::string;

	class User {
	private:
		string username;
		string username_color;
	public:
		User(string username);
	};
}
