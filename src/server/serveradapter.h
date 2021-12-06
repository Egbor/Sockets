#ifndef _SERVER_ADAPTER_H_
#define _SERVER_ADPATER_H_

#include "serverdef.h"

extern void invoke_adapted_create_process(session_entry_t session_entry, void* args);
extern void invoke_adapted_pthread_create(session_entry_t session_entry, void* args);

#endif
