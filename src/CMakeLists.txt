set(SOURCES
	networking/connection_socket.cpp
	networking/communication_socket.cpp

	chat/chat/chat.cpp
	chat/user/user.cpp
	chat/messages/message.cpp
)

add_library(${LIB_NAME} ${SOURCES})
target_include_directories(${LIB_NAME} PUBLIC .)


