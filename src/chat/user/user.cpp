#include "user.h"
#include "colors.h"

namespace user
{
	User::User(string username) : username(username)
	{
		username_color = get_random_color();
	}

	std::ostream& operator<<(std::ostream& os, const User& user)
	{
		os << user.username_color << user.username << default_color;
		return os;
	}
	// std::istream& operator>>(std::istream& is, User& user);
} // namespace user
