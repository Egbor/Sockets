#include "client.h"
#include "clientsettings.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sign.h>
#include <error.h>
#include <cmdopt.h>

#include<sys/socket.h>
#include<arpa/inet.h>	

int terminate_status = 0; // the flag indicates the process termination

void terminate_client(int sig) {
  terminate_status = 1; // set terminate_status on terminate
}

void setup_client(int argc, char* argv[]) {
  int signals[] = { SIGINT, SIGTERM }; // signals for redefine
  options_t* options = create_options(); // the structure keeps all options of the process
  
  add_option(options, 'i', setup_server_address); // the option to set the program into file input mode

  handle_options(options, argc, argv, "i:"); // parse and handle command line arguments
  set_signal(signals, 2, terminate_client); // redefine signals of the process
  
  free_options(options);
}

int connect_to_server(const char* ip, int port) {
  struct sockaddr_in server;
  
  int socket_client = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_client < 0) {
    throw_error("Client socket creation failed.", -1);
  }

  server.sin_addr.s_addr = inet_addr(ip);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);

  if (connect(socket_client, (struct sockaddr*)&server, sizeof(server)) < 0) {
    throw_error("Client connection to server failed.", -1);
  }

  return socket_client;
}

void start_client() {
  char* ip = get_server_ip();
  int port = get_server_port();
  int socket_client = connect_to_server(ip, port);

  char client_message[256];
  char* server_message = (char*)malloc(sizeof(char) * 160000);
  
  printf("Connected to %s:%d!\n", ip, port);
  while (!terminate_status) {
    printf("Command: ");
    fgets(client_message, sizeof(client_message), stdin);
    client_message[strcspn(client_message, "\n")] = 0;
    
    write(socket_client, client_message, strlen(client_message) + 1);
    recv(socket_client, server_message, 160000, 0);

    printf("%s\n", server_message);
  }

  free(server_message);
  close(socket_client);
}
