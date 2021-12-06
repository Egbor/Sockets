#include "cmdopt.h"

#include <stdlib.h>
#include <memory.h>
#include <unistd.h>

typedef struct _options {
  int optchar;
  void(*handler)(void*);
  struct _options* next;
} options_t;

options_t* create_options() {
  // craete a new list of option
  options_t* options = (options_t*)malloc(sizeof(options_t));
  memset(options, 0, sizeof(options_t));
  return options;
}

void free_options(options_t* options) {
  if (options) {
    free_options(options->next);
    free(options);
  }
}

void add_option(options_t* options, int optchar, void(*handler)(void*)) {
  // add a new element into list of option
  if (options->next) {
    add_option(options->next, optchar, handler);
    return;
  }
  options->optchar = optchar;
  options->handler = handler;
  options->next = create_options();
}

void handle_options(options_t* options, int argc, char* const argv[], const char* optstring) {
  int optchar = 0;

  // enumerate each element in the list and invoke the handler if an option was set
  
  while ((optchar = getopt(argc, argv, optstring)) > -1) {
    options_t* next_option = options;

    while (next_option->next) {
      if (next_option->optchar == optchar) {
	next_option->handler(optarg);
	break;
      }
      next_option = next_option->next;
    }
    
  }
}
