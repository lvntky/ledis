
#include <asm-generic/socket.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>
#include <arpa/inet.h>
#include "../include/ledis.h"
#include "../include/ledis_commnads.h"

pthread_mutex_t server_mutex;

char *idnetify_client(int client_socket_fd)
{
	char *client_ip = (char *)malloc(INET_ADDRSTRLEN);
	struct sockaddr_in client_sock_addr;
	socklen_t client_sock_addr_len = sizeof(client_sock_addr);

	getpeername(client_socket_fd, (struct sockaddr *)&client_sock_addr,
		    &client_sock_addr_len);

	inet_ntop(AF_INET, &(client_sock_addr.sin_addr), client_ip,
		  INET_ADDRSTRLEN);

	return client_ip;
}

void *handle_client(void *client_socket_fd_ptr)
{
	int client_socket_fd = *((int *)client_socket_fd_ptr);
	char *client_ip = idnetify_client(client_socket_fd);
	char server_read_buffer[MAX_SERVER_BUFFER_SIZE] = { 0 };
	char client_read_buffer[MAX_SERVER_BUFFER_SIZE] = { 0 };

	int server_read_status = read(client_socket_fd, server_read_buffer,
				      (MAX_SERVER_BUFFER_SIZE - 1));

	if (server_read_status < 0) {
		perror("Ledis can't read from client to its buffer ");
	} else {
		printf("[CLIENT - %s] %s\n", client_ip, server_read_buffer);
		if (strncmp(server_read_buffer, LEDIS_PING,
			    strlen(LEDIS_PING)) == 0) {
			strncpy(client_read_buffer, "PONG", strlen("PONG"));
			send(client_socket_fd, client_read_buffer,
			     strlen(client_read_buffer), 0);
		}
	}

	close(client_socket_fd);
	free(client_socket_fd_ptr);
	free(client_ip);
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
#ifdef CONCURRENT_POOLING
	printf("TODO: implement optional pooling\n");
#endif
#ifdef CONCURRENT_THREADS
	printf("Threads implemented but not set as optional\n");
#endif

	int server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sockaddr;

	/**
   * Socket conf for re-using port imidiately
   */
	int option = 1;
	setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &option,
		   sizeof(option));

	/**
    * Socket configurations
    */
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = htons(PORT_ADDR);
	sockaddr.sin_family = AF_INET;

	socklen_t socket_len = sizeof(sockaddr);

	if (server_socket_fd < 0) {
		perror("Unable to run server ");
	}

	if (bind(server_socket_fd, (const struct sockaddr *)&sockaddr,
		 socket_len) != 0) {
		perror("Can't bind the server socket");
		exit(-1);
	} else {
		printf("Ledis bind on localhost!\n");
	}

	/**
     Set socket to the passive(server) status
     Listen incoming connections
   */

	if (listen(server_socket_fd, MAX_BACKLOG) != 0) {
		perror("Server socket can't listen new connection ");
		exit(1);
	} else {
		printf("Ledis listening port %d\n", PORT_ADDR);
	}

	pthread_t tid; // Thread ID

	/**
     Listen from client
     TODO: make it concurrent
   */
	while (1) {
		int *client_socket_fd_ptr = (int *)malloc(sizeof(int));
		*client_socket_fd_ptr = accept(server_socket_fd,
					       (struct sockaddr *)&sockaddr,
					       &socket_len);

		if (*client_socket_fd_ptr < 0) {
			perror("Socket can't accept any new connection ");
			free(client_socket_fd_ptr);
			exit(1);
		}

		pthread_mutex_lock(&server_mutex);

		/**
     * Create a new thread 
     * to handle new client
    */
		if (pthread_create(&tid, NULL, handle_client,
				   (void *)client_socket_fd_ptr) != 0) {
			perror("Failed to create a new thread for client ");
			close(*client_socket_fd_ptr);
			free(client_socket_fd_ptr);
			pthread_mutex_unlock(&server_mutex);
			exit(1);
		}

		pthread_mutex_unlock(&server_mutex);
	}

	pthread_mutex_destroy(&server_mutex);

	return 0;
}
