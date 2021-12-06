#include "serversettings.h"
#include "serveradapter.h"

#include <stddef.h>

void(*session_constructor)(session_entry_t, void*) = NULL;

void switch_server_to_process_mode(void* args) {
  session_constructor = invoke_adapted_craete_process;
}

void switch_server_to_threads_mode(void* args) {
  session_constructor = invoke_adapted_pthread_cearte;
}

void get_session_constructor(void(**func)(session_entry_t, void*)) {
  *func = session_constructor;
}
