#pragma once

#include "libs.h"

enum {
	authorize = 0
};

#define CALL unsigned int

/// <summary>
/// This class is responsible for making contact with discord bot.
/// </summary>
class SocketHandler
{
public:
	SocketHandler(PCWSTR ip, unsigned int port);
	~SocketHandler(void);
	char* Message(const char message[4096]);

private:
	SOCKET clientSocket;
};

