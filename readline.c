#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *line;

    line = readline("LazyShell>");
    if (line != NULL) {
        printf("Bonjour, %s!\n", line);
        free(line);
    }

    return 0;
}

