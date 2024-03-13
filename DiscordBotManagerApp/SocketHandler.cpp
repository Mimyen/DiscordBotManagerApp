#include "SocketHandler.h"

SocketHandler::SocketHandler(PCWSTR ip, unsigned int port)
    : token(""), m_ip(ip), m_port(port)
{

}

std::string SocketHandler::Message(std::string message)
{

    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return "";
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(m_port);

    if (InetPton(AF_INET, m_ip, &serverAddress.sin_addr) != 1) {
        closesocket(clientSocket);
        WSACleanup();
        return "";
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) != 0) {
        closesocket(clientSocket);
        WSACleanup();
        return "";
    }

    char bufferS[4096];
    strcpy_s(bufferS, message.c_str());

    // Send the message to the server
    send(clientSocket, bufferS, strlen(bufferS), 0);

    // Receive and print the response from the server
    char buffer[4096];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

    closesocket(clientSocket);
    WSACleanup();

    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        return buffer;
    }

    return "";
}

wxString SocketHandler::Handle(CALL callId, std::vector<std::string> data)
{
    std::string message;
    std::string returnValue = "false";

    nlohmann::json bufferMessage;
    nlohmann::json output;

    switch (callId) {
    case authorize:
        bufferMessage["message"] = "authorize";
        bufferMessage["id"] = login = data[0];
        bufferMessage["password"] = data[1];

        message = bufferMessage.dump();
        wxLogDebug(message.c_str());

        message = Message(message);
        wxLogDebug(message.c_str());
        
        output = nlohmann::json::parse(message);
        if (output["response"] == "Error") break;

        token = output["Token"];
        wxLogDebug(token.c_str());
        
        returnValue = "true";
        break;
    default: break;
    }

    return returnValue;
}
