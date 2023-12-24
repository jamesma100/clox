#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"
#include "token_list.h"

/*
 * Dynamically resizing list for Tokens
 */

void init(TokenList *tl, size_t initial_size) {
  tl->used = 0;
  tl->size = initial_size;
  tl->list = malloc(initial_size * sizeof(Token));
}

void insert(TokenList *tl, Token *t) {
  if (tl->used == tl->size) {
    tl->size *= 2;
    tl->list = realloc(tl->list, tl->size * sizeof(Token));
  }
  tl->list[tl->used++] = *t;
}

void free_list(TokenList *tl) {
  free(tl->list);
  tl->list = NULL;
  tl->used = tl->size = 0;
}

// int main() {
//   TokenList tl;
//   init(&tl, 5);
//   for (int i = 0; i < 21; ++i) {
//     Token t = {PRINT, "hello", "world", i};
//     insert(&tl, &t); 
//   }
// 
//   printf("%d\n", tl.list[9].line);
//   printf("%d\n", tl.list[12].line);
//   printf("%zu\n", tl.size);
//   free_list(&tl);
//   return 0;
// }
