typedef enum {
  // Single char
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,
  // One or two char
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,
  // Literals
  IDENTIFIER,
  STRING,
  NUMBER,
  // Keywords
  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,
  END
} TokenType;

typedef struct {
  TokenType type;
  char *lexeme;
  char *literal;
  int line;
} Token;

char *tok_to_str(Token *tkn);

char *tok_to_str(Token *tkn) {
  size_t len = 0;
  len = snprintf(NULL, len, "%d %s %s", tkn->type, tkn->lexeme, tkn->literal);
  char *fmt_str = (char*)malloc(len * sizeof(char) + 1);
  snprintf(fmt_str, len + 1, "%d %s %s", tkn->type, tkn->lexeme, tkn->literal);
  return fmt_str;
}
