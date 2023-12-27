#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "token.h"
#include "token_list.h"
#include <ctype.h>
#include "clox.h"
#include "scanner.h"

bool is_at_end(Scanner *s) {
  return (size_t)s->current >= strlen(s->source);
}

char peek(Scanner *s) {
  if (is_at_end(s)) return '\0';
  return *(s->source + s->current);
}

char peek_next(Scanner *s) {
  if ((size_t)(s->current + 1) >= strlen(s->source)) return '\0';
  return *(s->source + s->current + 1);
}

char advance(Scanner *s) {
  return *(s->source + s->current++);
}

/*
 * Return substring of str from start to end (exclusive)
 * Does dynamic allocation so remember to free when done!
 */
char* substr(char *str, int start, int end) {
  size_t sz = (size_t)(end - start);
  char *substr = malloc(sz);
  strncpy(substr, str + start, sz);
  return substr;
}

void add_token_with_literal(Scanner *s, TokenType type, char *string_literal, double* double_literal) {
  char *text = substr(s->source, s->start, s->current);
  Token tkn = {type, text, string_literal, double_literal, s->line};
  insert(s->tokens, &tkn);
}

void add_token(Scanner *s, TokenType type) {
  add_token_with_literal(s, type, NULL, NULL);
}

bool match(Scanner *s, char expected) {
  if (is_at_end(s)) return false;
  if (*(s->source + s->current) != expected) return false;
  s->current++;
  return true;
}

void do_string(Scanner *s) {
  while (peek(s) != '"' && !is_at_end(s)) {
    if (peek(s) == '\n') s->line++;
    advance(s);
  }

  if (is_at_end(s)) {
    error(s->line, "Unterminated string.");
    return;
  }

  advance(s);

  // trim the surrounding quotes
  char *value = substr(s->source, s->start + 1, s->current - 1);
  add_token_with_literal(s, STRING, value, NULL);
}

void do_number(Scanner *s) {
  while(isdigit(peek(s))) advance(s);

  // look for fractional part
  if (peek(s) == '.' && isdigit(peek_next(s))) {
    advance(s);

    while (isdigit(peek(s))) advance(s);
  }

  char *double_str = substr(s->source, s->start, s->current);
  double d = atof(double_str);
  free(double_str);
  double_str = NULL;
  add_token_with_literal(s, NUMBER, NULL, &d);
}


void do_identifier(Scanner *s) {
  while (isalnum(peek(s))) advance(s);

  char *newtext = substr(s->source, s->start, s->current);
  TokenType type;

  if (strcmp(newtext, "and") == 0){
    type = AND;
  } else if (strcmp(newtext, "class") == 0) {
    type = CLASS;
  } else if (strcmp(newtext, "else") == 0) {
    type = ELSE;
  } else if (strcmp(newtext, "false") == 0) {
    type = FALSE;
  } else if (strcmp(newtext, "for") == 0) {
    type = FOR;
  } else if (strcmp(newtext, "fun") == 0) {
    type = FUN;
  } else if (strcmp(newtext, "if") == 0) {
    type = IF;
  } else if (strcmp(newtext, "nil") == 0) {
    type = NIL;
  } else if (strcmp(newtext, "or") == 0) {
    type = OR;
  } else if (strcmp(newtext, "print") == 0) {
    type = PRINT;
  } else if (strcmp(newtext, "return") == 0) {
    type = RETURN;
  } else if (strcmp(newtext, "super") == 0) {
    type = SUPER;
  } else if (strcmp(newtext, "this") == 0) {
    type = THIS;
  } else if (strcmp(newtext, "true") == 0) {
    type = TRUE;
  } else if (strcmp(newtext, "var") == 0) {
    type = VAR;
  } else if (strcmp(newtext, "while") == 0) {
    type = WHILE;
  } else {
    type = IDENTIFIER;
  }

  add_token(s, type);
}
void scan_token(Scanner *s) {
  char c = advance(s);
  switch (c) {
    case '(':
      add_token(s, LEFT_PAREN);
      break;
    case ')':
      add_token(s, RIGHT_PAREN);
      break;
    case '{':
      add_token(s, LEFT_BRACE);
      break;
    case '}':
      add_token(s, RIGHT_BRACE);
      break;
    case ',':
      add_token(s, COMMA);
      break;
    case '.':
      add_token(s, DOT);
      break;
    case '-':
      add_token(s, MINUS);
      break;
    case '+':
      add_token(s, PLUS);
      break;
    case ';':
      add_token(s, SEMICOLON);
      break;
    case '*':
      add_token(s, STAR);
      break;
    case '!':
      add_token(s, match(s, '=') ? BANG_EQUAL : BANG);
      break;
    case '=':
      add_token(s, match(s, '=') ? EQUAL_EQUAL : EQUAL);
      break;
    case '<':
      add_token(s, match(s, '=') ? LESS_EQUAL : LESS);
      break;
    case '>':
      add_token(s, match(s, '=') ? GREATER_EQUAL : GREATER);
      break;
    case '/':
      if (match(s, '/')) {
        while (peek(s) != '\n' && !is_at_end(s)) advance(s);
      } else {
        add_token(s, SLASH);
      }
      break;
    case ' ':
    case '\r':
    case '\t':
      // ignore whitespace
      break;
    case '\n':
      s->line++;
      break;
    case '"':
      do_string(s);
      break;
    default:
      if (isdigit(c)) {
        do_number(s);
      } else if (isalpha(c)) {
        do_identifier(s);
      } else {
        error(s->line, "Unexpected character.");
      }
      break;
  }
}

TokenList* scan_tokens(Scanner *s) {
  while (!is_at_end(s)) {
    s->start = s->current;
    scan_token(s);
  }
  Token end_token = {END, "", NULL, NULL, s->line};
  insert(s->tokens, &end_token);
  return s->tokens;
}
