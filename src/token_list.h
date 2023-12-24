typedef struct {
  Token *list;
  size_t used;
  size_t size;
} TokenList;

void init(TokenList *tl, size_t initial_size);
void insert(TokenList *tl, Token *t);
void free_list(TokenList *tl);
