set(SOURCES
	networking/connection_socket.cpp
	networking/communication_socket.cpp
)

add_library(${LIB_NAME} ${SOURCES})
target_include_directories(${LIB_NAME} PUBLIC .)


