set(CLIENT_SOURCES
	client/main.cpp
)

set(SERVER_SOURCES
	server/main.cpp
)


add_executable(${APP_NAME}-server ${SERVER_SOURCES})
target_link_libraries(${APP_NAME}-server PRIVATE ${LIB_NAME})

add_executable(${APP_NAME}-client ${CLIENT_SOURCES})
target_link_libraries(${APP_NAME}-client PRIVATE ${LIB_NAME})
