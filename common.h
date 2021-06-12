#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_WORDLEN 20
#define MAX_RELATEWORD 10

#ifdef _WIN32
#define strdup _strdup
#endif

char* trim(char* str);
char** str_split(char* str, char* delimiter);

#endif	//_COMMON_H_