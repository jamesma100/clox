#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include "token.h"
#include "token_list.h"

static bool had_error = false;

void report(int line, char* where, char* msg) {
  printf("[line %d] Error %s: %s", line, where, msg);
  had_error = true;
}

void error(int line, char* msg) {
  report(line, "", msg);
}

void run(char* line) {
    printf("Read line: %s", line);
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
  Token t = {FALSE, "hello", "world", 1};
  char *res = tok_to_str(&t);
  printf("string result: %s\n", res);
  if (res) free(res);
  
  if (argc > 2) {
    exit(64);
  } else if (argc == 2) {
    get_input(argv[1]);
  } else {
    get_input(NULL);
  }
  return 0;
}
