#include <string>
#include <termios.h>
#include <unistd.h>

namespace terminal
{
class BufferToggle
{
private:
	struct termios t;

public:
	void off(void)
	{
		tcgetattr(STDIN_FILENO, &t); // get the current terminal I/O structure
		t.c_lflag &=
		    ~ICANON; // Manipulate the flag bits to do what you want it to do
		tcsetattr(STDIN_FILENO, TCSANOW, &t); // Apply the new settings
	}

	void on(void)
	{
		tcgetattr(STDIN_FILENO, &t); // get the current terminal I/O structure
		t.c_lflag |= ICANON; // Manipulate the flag bits to do what you want it to
		// do
		tcsetattr(STDIN_FILENO, TCSANOW, &t); // Apply the new settings
	}
};

constexpr std::string LINE_UP = "\x1b[A";
constexpr std::string BEGIN = "\r";
constexpr std::string CLEAR_LINE = "\x1b[2K";

}
