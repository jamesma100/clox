CFLAGS=-Wall -Wextra -Werror

clox: src/clox.c
	gcc $(CFLAGS) src/clox.c -o clox
