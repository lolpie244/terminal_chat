#pragma once

#include <string>
#include <list>
#include <memory>
#include "user.h"

namespace chat {
	using std::string;
	using std::weak_ptr;

	class Chat {
	private:
		string password;
		string name;
		std::list<User> user_list;
	public:
		Chat(string name, string password);

		bool check_access(string password);
		void add_user(std::shared_ptr<User> user);
		void new_message(string message);
	};
}
