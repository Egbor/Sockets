#ifndef _SERVER_SETTINGS_H_
#define _SERVER_SETTINGS_H_

#include "serverdef.h"

extern void switch_server_to_process_mode(void* args);
extern void switch_server_to_threads_mode(void* args);

extern void get_session_constructor(void(**func)(session_entry_t, void*));
// extern void get_session_destructor(void(*func)(void));

#endif
