#include "Server.h"

#pragma warning(disable: 4996)

Net::Server::Server(int port, string ipAddress)
	:
	wsa{ 0 },
	port(port),
	ipAddress(ipAddress),
	serverSocket(INVALID_SOCKET),
	info{ 0 },
	infoLength(sizeof(info)) { }


Net::Server::~Server()
{
	WSACleanup();
	closesocket(serverSocket);
}

void Net::Server::init()
{
	info.sin_family = AF_INET; // ipv4
	info.sin_port = htons(port);
	info.sin_addr.S_un.S_addr = inet_addr(ipAddress.c_str()); 

	cout << "WSA init" << endl;
	assert(!(WSAStartup(MAKEWORD(2, 2), &wsa)) && "Couldn't init wsa");
	cout << "WSA init success" << endl;


	cout << "Creating socket..." << endl;
	assert(!((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) == SOCKET_ERROR) && ("Couldn't create socket"));
	cout << "Success" << endl;

	cout << "Bind socket" << endl;
	assert(!((bind(serverSocket, (struct sockaddr*)&info, infoLength))) && "Cound't bind socket");
	cout << "Socket is binded success" << endl;

	cout << "Server started at " << inet_ntoa(info.sin_addr) << " : " << ntohs(info.sin_port) << endl;
}


void Net::Server::start()
{
	init();

	for (;;)
	{
		receive();
		proccess();
		send();
	}
}


void Net::Server::receive()
{
	if ((recvLength = recvfrom(serverSocket, buffer, SIZE, 0, (struct sockaddr*)&info, &infoLength)) == SOCKET_ERROR)
	{
		cout << "Receive failed" << endl;
		exit(EXIT_FAILURE);
	}
}

void Net::Server::proccess()
{
	cout << "Packet from: " << inet_ntoa(info.sin_addr) << " : " << ntohs(info.sin_port) << endl;

	for (size_t i = 0; i < recvLength; i++)
	{
		cout << buffer[i];
	}
	
	cout << endl;
}


void Net::Server::send()
{
	if (sendto(serverSocket, buffer, SIZE, 0, (struct sockaddr*)&info, infoLength) == SOCKET_ERROR)
	{
		cout << "Send failed" << endl;
		exit(EXIT_FAILURE);
	}
}