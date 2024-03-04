#include "SocketHandler.h"

SocketHandler::SocketHandler()
{
}

bool SocketHandler::Handle(const char message[4096])
{
    WSADATA wsaData;
    SOCKET clientSocket;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        // std::cerr << "Failed to initialize Winsock" << std::endl;
        return 1;
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(2222);

    if (InetPton(AF_INET, L"127.0.0.1", &serverAddress.sin_addr) != 1) {
        // std::cerr << "Invalid IP address" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) != 0) {
        // std::cerr << "Failed to connect to the server" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // Send the JSON message to the Python server
    send(clientSocket, message, strlen(message), 0);

    // Receive and print the JSON response from the Python server
    char buffer[4096];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        // std::cout << "Received from Python server: " << buffer << std::endl;
    }


    closesocket(clientSocket);
    WSACleanup();
    return true;
}
