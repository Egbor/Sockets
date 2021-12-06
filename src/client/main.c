#include <basename.h>
#include "client.h"

#include <stdlib.h>

int main(int argc, char* argv[]) {
  set_basename(argv[0]);
  setup_client(argc, argv);
  start_client();
  return 0;
}
