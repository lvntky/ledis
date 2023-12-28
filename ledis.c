
#include <asm-generic/socket.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT_ADDR 3408
#define MAX_BACKLOG 9999
#define MAX_SERVER_BUFFER_SIZE 4096

int main(int argc, char **argv) {

  int server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in sockaddr;

  /**
   * Socket conf for re-using port imidiately
   */
  int option = 1;
  setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));


  /**
    * Socket configurations
    */
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  sockaddr.sin_port = htons(PORT_ADDR);
  sockaddr.sin_family = AF_INET;

  socklen_t socket_len = sizeof(sockaddr);

  if(server_socket_fd < 0) {
    perror("Unable to run server ");
  }
  
  if(bind(server_socket_fd, (const struct sockaddr *) &sockaddr, socket_len) != 0) {
    perror("Can't bind the server socket");
    exit(-1);
  } else {
    printf("Server bind on port localhost:%d/\n", PORT_ADDR);
  
  }

  /**
     Set socket to the passive(server) status
     Listen incoming connections
   */

  if(listen(server_socket_fd, MAX_BACKLOG) != 0) {
    perror("Server socket can't listen new connection ");
    exit(1);
  } else {
    printf("Ledis listening on port %d\n", PORT_ADDR);
  }

  /**
     Listen from client
     TODO: make it concurrent
   */
  while(1) {
    int client_socket_fd = 0;
    if ((client_socket_fd = accept(
				   server_socket_fd, (struct sockaddr *)&sockaddr, &socket_len)) < 0) {
      perror("Socket can't accept any new connection ");
      //exit(1); /* TODO: Don't terminate on every accept fail */
    }
    char server_read_buffer[MAX_SERVER_BUFFER_SIZE] = {0};

    int server_read_status = read(client_socket_fd, server_read_buffer, (MAX_SERVER_BUFFER_SIZE - 1)); // -1 for NULL terminator

    if(server_read_status < 0) {
      perror("Ledis can't read from client to it's buffer ");
    }
    else {
      printf("[CLIENT] %s\n", server_read_buffer);
    }
  }

  /**
   * Todo: Concurrent Server
   */
  
  
  return 0;
}
