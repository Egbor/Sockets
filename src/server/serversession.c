#include "serversession.h"
#include "serversettings.h"

void create_session(session_entry_t session_entry, void* args) {
  void(*session_constructor)(session_entry_t, void*);
  get_session_constructor(&session_constructor);
  session_constructor(session_entry, args);
}
