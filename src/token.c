#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "token.h"

/*
 * Whether or not token encapsulates a string literal
 */
bool tok_is_string(Token *tkn) {
  return (tkn->string_literal != NULL);
}

/*
 * Whether or not token encapsulates a double literal
 */
bool tok_is_double(Token *tkn) {
  return (tkn->double_literal != NULL);
}

char *tok_to_str(Token *tkn) {
  size_t len = 0;
  if (tok_is_string(tkn)) {
    len = snprintf(NULL, len, "%d %s %s", tkn->type, tkn->lexeme, tkn->string_literal);
  } else if (tok_is_double(tkn)) {
    len = snprintf(NULL, len, "%d %s %f", tkn->type, tkn->lexeme, *(tkn->double_literal));
  } else {
    len = snprintf(NULL, len, "%d %s", tkn->type, tkn->lexeme);
  }

  char *fmt_str = (char*)malloc(len * sizeof(char) + 1);

  if (tok_is_string(tkn)) {
    snprintf(fmt_str, len + 1, "%d %s %s", tkn->type, tkn->lexeme, tkn->string_literal);
  } else if (tok_is_double(tkn)) {
    snprintf(fmt_str, len + 1, "%d %s %f", tkn->type, tkn->lexeme, *(tkn->double_literal));
  } else {
    snprintf(fmt_str, len + 1, "%d %s", tkn->type, tkn->lexeme);
  }

  return fmt_str;
}
