#include <basename.h>
#include "server.h"

#define DEFAULT_SERVER_PORT 4242

int main(int argc, char* argv[]) {
  set_basename(argv[0]);
  setup_server(argc, argv);
  start_server(DEFAULT_SERVER_PORT);
  return 0;
}
