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


friend std::ostream& operator<<(std::ostream& os, const User& user);
// friend std::istream& operator>>(std::istream& is, User& user);
};

std::ostream& operator<<(std::ostream& os, const User& user);
// std::istream& operator>>(std::istream& is, User& user);

} // namespace user
