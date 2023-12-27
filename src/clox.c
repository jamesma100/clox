#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include "token.h"
#include "token_list.h"
#include "clox.h"
#include "scanner.h"

static bool had_error = false;

void report(int line, char* where, char* msg) {
  printf("[line %d] Error %s: %s", line, where, msg);
  had_error = true;
}

void error(int line, char* msg) {
  report(line, "", msg);
}

void run(char* line) {
  TokenList tl;
  init(&tl, 4);
  Scanner s = {&tl, line, 0, 0, 0};

  TokenList* tokens = scan_tokens(&s);
  for (int i = 0; i < (int)tokens->used; ++i) {
    printf("%s\n", tok_to_str(tokens->list + i));
  }
}

void get_input(char* filename) {
  FILE *fp = stdin;
  if (filename != NULL) {
    fp = fopen(filename, "r");
    if (fp == NULL) {
      printf("ERROR: unable to open file. Exiting.\n");
      exit(1);
    }
  }

  char *line = NULL;
  size_t cap = 0;
  ssize_t read;
  while ((read = getline(&line, &cap, fp)) > 0) {
    run(line);
    if (had_error) {
      if (fp == stdin) {
        had_error = true;
      } else {
        exit(65);
      }
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc > 2) {
    exit(64);
  } else if (argc == 2) {
    get_input(argv[1]);
  } else {
    get_input(NULL);
  }
  return 0;
}
