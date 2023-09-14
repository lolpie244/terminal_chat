#pragma once

#include <string>

namespace user
{
using std::string;

class User
{
private:
	string username;
	string username_color;

public:
	User(string username);
	string current_text;

	static User create_from_input();


friend std::ostream& operator<<(std::ostream& os, const User& user);
};

std::ostream& operator<<(std::ostream& os, const User& user);

} // namespace user
