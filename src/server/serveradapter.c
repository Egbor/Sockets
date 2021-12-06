#include "serveradapter.h"

#include <process.h>
#include <pthread.h>

void invoke_adapted_create_process(session_entry_t session_entry, void* args) {
  create_process(session_entry, args);
}

void invoke_adapted_pthread_create(session_entry_t session_entry, void* args) {
  pthread_t thread;

  pthread_create(&thread, NULL, session_entry, args);
}
