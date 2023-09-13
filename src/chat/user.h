#pragma once

#include <string>

namespace chat {
	using std::string;

	class User {
	private:
		string username;
	public:
		User(string username);
	};
}
