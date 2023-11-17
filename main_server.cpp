#include <assert.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>


int main() {
	std::cout << "my stupid server... v1.0 " << std::endl;
	int id_socket = socket(AF_INET, SOCK_STREAM, 0);
	assert(id_socket > 0);

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(33001);
	addr.sin_addr.s_addr = INADDR_ANY;

	int res = bind(id_socket, (sockaddr*)&addr, sizeof(addr));
	assert(res == 0);

	res = listen(id_socket, 5);

	while(1) {

		int id_client = accept(id_socket, nullptr, nullptr);
		assert(id_client > 0);

		char buf[64];
		//while(1) 
		{
			int count_bytes = recv(id_client, buf, 64, 0);
			if (count_bytes > 0) {
				std::cout << buf << std::endl;
				send(id_client, "OK тест 你好", 32, 0);
			}
		}
		close(id_client);
	}
	close(id_socket);

	return 0;
}
