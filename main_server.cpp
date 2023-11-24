#include <assert.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>


void* th1(void* arg) {
	
		char buf[64];
		int id_client = *static_cast<int*>(arg);
		while(1) 
		{
			int count_bytes = recv(id_client, buf, 64, 0);
			if (count_bytes > 0) {
				std::cout << std::hex << id_client << " : " << count_bytes << " - " << buf << std::endl;
				memset(buf, 0x00, 64);
				send(id_client, "OK", 2, 0);
			}
			else if (count_bytes < 0) {
				std::cout << " error " << std::endl;
				break;
			}
			std::cout << "new messages were accepted" << std::endl;
		}

		std::cout << "-------------------client " << id_client << " error  " << std::endl;
		close(id_client);

		std::cout << "end thread------------------------------------" << std::endl;
	

	return 0;
}


int main() {
	std::cout << "my not full server... v3.0 not to much secret " << std::endl;


	pthread_t id_thread;

	int id_socket = socket(AF_INET, SOCK_STREAM, 0);
	assert(id_socket > 0);

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(33001);
	addr.sin_addr.s_addr = INADDR_ANY;

	int res = bind(id_socket, (sockaddr*)&addr, sizeof(addr));
	assert(res == 0);

	res = listen(id_socket, 32);

	while(1) {
		int id_client = accept(id_socket, nullptr, nullptr);
		pthread_create(&id_thread, nullptr, th1, &id_client);
		assert(id_client > 0);
	}

	close(id_socket);

	return 0;
}
