#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "token.h"
#include "token_list.h"


typedef struct {
  TokenList *tokens;
  char *source;
  int start;
  int current;
  int line;
} Scanner;

bool is_at_end(Scanner *s) {
  return s->current >= strlen(s->source);
}

void scan_token(Scanner *s) {
}

TokenList* scan_tokens(Scanner *s) {
  while (!is_at_end(s)) {
    s->start = s->current;
    scan_token(s);
  }
  Token end_token = {END, "", NULL, s->line};
  insert(s->tokens, &end_token);
  return s->tokens;

}
