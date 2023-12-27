#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

static bool had_error;
void report(int line, char* where, char* msg);
void error(int line, char* msg);
