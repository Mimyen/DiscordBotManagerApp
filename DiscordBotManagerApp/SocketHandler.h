#pragma once

#include "libs.h"
#include "libs/json.hpp"

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
	std::string Message(std::string message);
	wxString Handle(CALL callId, std::vector<std::string> data = std::vector<std::string>());

private:
	SOCKET clientSocket;
	PCWSTR m_ip;
	unsigned int m_port;
	std::string token;
	std::string login;
};

