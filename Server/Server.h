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
using std::endl;

namespace Net
{
	class Server
	{
		WSADATA wsa;
		SOCKET serverSocket;
		string ipAddress;
		int port;
		char buffer[SIZE];
		struct sockaddr_in info;
		int infoLength;
		int recvLength;

	public:

		Server(int, string);
		~Server();

		void start();
		//void stop();

	private:
		
		void init();
		void receive();
		void proccess();
		void send();
	};
}
