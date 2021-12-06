#include "server.h"
#include "serversession.h"
#include "serversettings.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sign.h>
#include <error.h>
#include <cmdopt.h>

#include <sys/socket.h>
#include <arpa/inet.h>

int terminate_status = 0; // the flag indicates the process termination

void terminate_server(int sig) {
  terminate_status = 1; // set terminate_status on terminate
}

void setup_server(int argc, char* argv[]) {
  int signals[] = { SIGINT, SIGTERM }; // signals for redefine
  options_t* options = create_options(); // the structure keeps all options of the process
  
  add_option(options, 'p', switch_server_to_process_mode); // the option to set the program into process mode
  add_option(options, 't', switch_server_to_threads_mode); // the option to set the program into threads mode

  handle_options(options, argc, argv, "pt"); // parse and handle command line arguments
  set_signal(signals, 2, terminate_server); // redefine signals of the process
  
  free_options(options);
}

int read_all_file(const char* filename, char* buffer, size_t size) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    return -1;
  }

  fseek(file, 0, SEEK_END);
  int file_size = ftell(file);
  fseek(file, 0, SEEK_SET);
  
  fread(buffer, size, file_size, file);
  fclose(file);

  buffer[file_size] = 0;
  
  return 0;
}

int open_server_port(int port) {
  struct sockaddr_in server;

  int socket_server = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_server < -1) {
    throw_error("Server socket creation failed.", -1);
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(port);

  if (bind(socket_server, (struct sockaddr*)&server, sizeof(server)) < 0) {
    throw_error("Server socket binding failed.", -1);
  }

  listen(socket_server, 3);
  return socket_server;
}

int wait_connection_to_server(int socket_server) {
  struct sockaddr_in client;

  int socklen = sizeof(struct sockaddr_in);
  int socket_client = accept(socket_server, (struct sockaddr*)&client, (socklen_t*)&socklen);

  if (socket_client < 0) {
    throw_error("Client socket acception failed.", -1);
  }

  return socket_client;
}

void* session_entry(void* args) {
  int socket_client = *((int*)args);
  int read_size = 0;

  char client_message[128];
  char client_command[258];
  char client_output[128];

  char* command_result = (char*)malloc(sizeof(char) * 160000);

  sprintf(client_output, "/tmp/%d.txt", socket_client);
  while ((read_size = recv(socket_client, client_message, sizeof(client_message), 0)) > 0) {
    sprintf(client_command, "%s > %s", client_message, client_output);
    if (system(client_command) < 0) {
      sprintf(client_command, "Command not found - %s", client_message);
      write(socket_client, client_command, strlen(client_command) + 1);
    } else {
      read_all_file(client_output, command_result, 160000);
      write(socket_client, command_result, strlen(command_result) + 1);
    }
  }

  free(command_result);
}

void start_server(int port) {
  int socket_server = open_server_port(port);
  while (!terminate_status) {
    int socket_client = wait_connection_to_server(socket_server);
    create_session(session_entry, &socket_client);
  }
}
