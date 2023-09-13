#include <string>
namespace events
{
	enum ClientEvents {
		CLIENT_CONNECTION_REFUSED,
		CLIENT_CONNECTED,
		CLIENT_NEW_MESSAGE,
	};

	enum ServerEvents {
		SERVER_CONNECTION_ATTEMPT,
		SERVER_NEW_CHAT,
		SERVER_NEW_MESSAGE,
	};

	inline std::string add_event_prefix(const std::string& message, int event)
	{
		if (!message.length())
			return std::to_string(event);
		return std::to_string(event) + " " + message;
}
} // namespace events
