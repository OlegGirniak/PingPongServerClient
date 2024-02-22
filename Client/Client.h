#pragma once
#include <iostream>
#include <assert.h>
#include <vector>
#include <WinSock2.h>
#include <string>
//#include <unordered_map>
//#include <thread>


#pragma comment(lib, "Ws2_32.lib")

#define SIZE (1024)

using std::string;
using std::cout;
using std::cin;
using std::getline;
using std::endl;


namespace Net
{
	class Client
	{
		WSADATA wsa;
		SOCKET clientSocket;
		string ipAddress;
		int port;
		char buffer[SIZE];
		string message;
		struct sockaddr_in info;
		int infoLength;
		int recvLength;

	public:

		Client(int, string);
		~Client();

		void connect();
		//void stop();

	private:

		void init();
		void receive();
		void proccess();
		void send();
	};
}
