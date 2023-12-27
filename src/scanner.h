typedef struct {
  TokenList *tokens;
  char *source;
  int start;
  int current;
  int line;
} Scanner;

TokenList* scan_tokens(Scanner *s);
