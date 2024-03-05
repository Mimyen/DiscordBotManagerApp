#include "SocketHandler.h"

SocketHandler::SocketHandler(PCWSTR ip, unsigned int port)
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw("Failed to initialize Winsock");
        return;
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    if (InetPton(AF_INET, ip, &serverAddress.sin_addr) != 1) {
        closesocket(clientSocket);
        WSACleanup();
        throw("Invalid IP address");
        return;
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) != 0) {
        closesocket(clientSocket);
        WSACleanup();
        throw("Failed to connect to the server");
        return;
    }
}

SocketHandler::~SocketHandler(void)
{
    closesocket(clientSocket);
    WSACleanup();
}

char* SocketHandler::Message(const char message[4096])
{
    // Send the message to the server
    send(clientSocket, message, strlen(message), 0);

    // Receive and print the response from the server
    char buffer[4096];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        return buffer;
    }

    return nullptr;
}