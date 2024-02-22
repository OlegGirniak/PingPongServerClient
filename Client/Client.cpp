#include "Client.h"

#pragma warning(disable: 4996)

Net::Client::Client(int port, string ipAddress)
	:
	wsa{ 0 },
	port(port),
	ipAddress(ipAddress),
	clientSocket(INVALID_SOCKET),
	info{ 0 },
	infoLength(sizeof(info)),
	message{} { }


Net::Client::~Client()
{
	WSACleanup();
	closesocket(clientSocket);
}

void Net::Client::init()
{
	info.sin_family = AF_INET; // ipv4
	info.sin_port = htons(port);
	info.sin_addr.S_un.S_addr = inet_addr(ipAddress.c_str());

	cout << "WSA init" << endl;
	assert(!(WSAStartup(MAKEWORD(2, 2), &wsa)) && "Couldn't init wsa");
	cout << "WSA init success" << endl;


	cout << "Creating socket..." << endl;
	assert(!((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) == SOCKET_ERROR) && ("Couldn't create socket"));
	cout << "Success" << endl;

	cout << "Client started at " << inet_ntoa(info.sin_addr) << " : " << ntohs(info.sin_port) << endl;
}


void Net::Client::connect()
{
	init();

	for (;;)
	{
		send();
		receive();
		proccess();
	}
}



void Net::Client::send()
{
	cout << "Enter message: ";
	getline(cin, message);



	if (sendto(clientSocket, message.c_str(), message.size(), 0, (struct sockaddr*)&info, infoLength) == SOCKET_ERROR)
	{
		cout << "Send failed" << endl;
		exit(EXIT_FAILURE);
	}
}

void Net::Client::receive()
{
	if ((recvLength = recvfrom(clientSocket, buffer, SIZE, 0, (struct sockaddr*)&info, &infoLength)) == SOCKET_ERROR)
	{
		cout << "Receive failed" << endl;
		exit(EXIT_FAILURE);
	}
}

void Net::Client::proccess()
{
	cout << "Packet from: " << inet_ntoa(info.sin_addr) << " : " << ntohs(info.sin_port) << endl;

	for (size_t i = 0; i < infoLength; i++)
	{
		cout << buffer[i];
	}

	cout << endl;
}
