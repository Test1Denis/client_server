#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <assert.h>
#include <unistd.h>


int main() {
	std::cout << "simple client ver 1.0...." << std::endl;

	int id_socket = socket(AF_INET, SOCK_STREAM, 0);
	assert(id_socket > 0);

	sockaddr_in addr;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	std::cout << "127.0.0.1  " << inet_addr("127.0.0.1") << std::endl;;
	addr.sin_port = htons(33001);
	addr.sin_family = AF_INET;

	int res = connect(id_socket, (sockaddr *)&addr, sizeof(addr));
	assert(res == 0);

	send(id_socket, "привет  你好  test", 64, 0);

	char buf[64];
	recv(id_socket, buf, 64, 0);
	std::cout << "accepted data : " << buf << std::endl;

	close(id_socket);

	return 0;
}

