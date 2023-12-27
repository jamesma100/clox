#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

char *tok_to_str(Token *tkn) {
  size_t len = 0;
  len = snprintf(NULL, len, "%d %s", tkn->type, tkn->lexeme);
  char *fmt_str = (char*)malloc(len * sizeof(char) + 1);
  snprintf(fmt_str, len + 1, "%d %s", tkn->type, tkn->lexeme);
  return fmt_str;
}
