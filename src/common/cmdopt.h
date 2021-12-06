#ifndef _CMDOPT_H_
#define _CMDOPT_H_

typedef struct _options options_t;

extern options_t* create_options();
extern void free_options(options_t* options);

extern void add_option(options_t* options, int optchar, void(*handler)(void*));
extern void handle_options(options_t* options, int argc, char* const argv[], const char* optstring);

#endif
