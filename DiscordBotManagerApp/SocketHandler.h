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
	SocketHandler();
	bool Handle(const char message[4096]);
};

