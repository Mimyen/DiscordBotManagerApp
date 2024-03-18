#pragma once

#include "libs.h"
#include "libs/json.hpp"

enum {
	authorize = 0,
	getservers = 1,
	getchannels = 2,
	sendmessage = 3
};

#define CALL unsigned int

/// <summary>
/// This class is responsible for making contact with discord bot.
/// </summary>
class SocketHandler
{
public:
	/// <summary>
	/// Contructor for SocketHandler class.
	/// </summary>
	/// <param name="ip">Ip of the server.</param>
	/// <param name="port">Port of the server.</param>
	SocketHandler(PCWSTR ip, unsigned int port);

	/// <summary>
	/// Sends message to the server and returns what was recieved.
	/// </summary>
	/// <param name="message">Message that will be sent to the server.</param>
	/// <returns>Recieved message</returns>
	std::string Message(std::string message);

	/// <summary>
	/// Function that handles proper sending and recieving messages from the server.
	/// </summary>
	/// <param name="callId">Id of the call that is being made</param>
	/// <param name="data">data needed for the call</param>
	/// <returns>Important information related to sent message</returns>
	std::vector<wxString> Handle(CALL callId, std::vector<std::string> data = std::vector<std::string>());

private:
	SOCKET clientSocket;
	PCWSTR m_ip;
	unsigned int m_port;
	std::string token;
	std::string login;
};

