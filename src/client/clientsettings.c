#include "clientsettings.h"
#include <stdio.h>

#define DEFAULT_SERVER_IP "127.0.0.1"
#define DEFAUKT_SERVER_PORT 4242;

char server_ip[256] = DEFAULT_SERVER_IP;
int server_port = DEFAUKT_SERVER_PORT;

void setup_server_address(void* args) {
  sscanf(args, "%[^[^:]*]", server_ip);
  sscanf(args, "%*[^:]:%d", &server_port);
}

char* get_server_ip() {
  return server_ip;
}

int get_server_port() {
  return server_port;
}

