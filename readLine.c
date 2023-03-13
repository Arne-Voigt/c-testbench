#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFFERSIZE 10

// reads one line from a file into a buffer, increases the buffer size if necessary 
// buffer location is written back into the parameter **line
// returns NULL on read-error/eof otherwise returns *line 
char *readline(char **line, FILE *fp)
{
    int lineSize = 0;

    if (*line != NULL)
        free(*line);
    *line = malloc(BUFFFERSIZE * sizeof(char));

    while (fgets(*line + lineSize, BUFFFERSIZE, fp))
    {
        lineSize = strlen(*line);
        if (strcmp(*line + lineSize - 1, "\n") == 0 || // eol reached
            feof(fp))                                  // eof reached, edge case: last line in a file (no final '\n') shouldn't be returning NULL
            return *line;
        // line reading not yet completted -> increase buffer
        *line = realloc(*line, lineSize + 1 + BUFFFERSIZE);
    }
    return NULL;
}

int main()
{
    char *line = NULL;
    FILE *fp;

    fp = fopen("readLine.txt", "r");

    while (readline(&line, fp) != NULL)
        printf("line fread: %s", line);

    fclose(fp);
    free(line);
    return (0);
}
