CFLAGS=-Wall -Wextra -Werror

.PHONY: all
all: clox

clox: src/clox.c src/token.c src/token.h src/scanner.c src/scanner.h src/token_list.c src/token_list.h
	gcc $(CFLAGS) src/clox.c src/token.c src/scanner.c src/token_list.c -o clox
