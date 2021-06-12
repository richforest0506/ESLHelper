#include "common.h"
char* trim(char* str)
{
	char* po = str;
	size_t len = strlen(po);

	size_t off = 0;
	while (po[off] == ' ')
		off++;
	if (off > len)
		return NULL;

	while (len-- > 0 && (po[len] == ' ' || po[len] == '\n' || po[len] == '\r'))
		po[len] = '\0';

	memmove(str, &po[off], len - off + 2);
	return str;
}

char** str_split(char* str, char* delimiter)
{
    char** result = 0;
    char* tmp = str;
    char* last_word = 0;
    size_t count = 0;
    while (*tmp)
    {
        if (strncmp(delimiter, tmp, strlen(delimiter))== 0)
        {
            count++;
            last_word = tmp;
            tmp += strlen(delimiter);
        }
        else
            tmp++;
    }

    count += (last_word < (str + strlen(str) - 1));
    count++;
    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx = 0;
        char* token = strtok(str, delimiter);

        while (token)
        {
            assert(idx < count);
            result[idx++] = strdup(token);
            token = strtok(0, delimiter);
        }
        assert(idx == count - 1);
        result[idx] = 0;
    }

    return result;
}
