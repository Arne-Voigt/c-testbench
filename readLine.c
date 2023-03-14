#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFERSIZE 10

// works almost like getline(), reads one line from a file into a buffer (**line),
// increases the buffer size if necessary, returns the used buffersize in *lineSize
// returns NULL on read-error/eof otherwise returns *line
char *readline(char **line, int *lineSize, FILE *fp)
{
    int writeOffset = 0;
    int bytesToRead;

    if (*line == NULL)
    {
        *line = (char *)malloc(BUFFERSIZE * sizeof(char));
        *lineSize = BUFFERSIZE;
    }

    bytesToRead = *lineSize;

    while (fgets(*line + writeOffset , bytesToRead, fp))
    {
        if (strcmp(*line + writeOffset + strlen(*line + writeOffset) - 1, "\n") == 0 || // eol reached
            feof(fp)) // eof reached, edge case: last line in a file (no final '\n') shouldn't be returning NULL
        {
            return *line;
        }
        // line reading not yet completted -> increase buffer
        *line = realloc(*line, *lineSize + BUFFERSIZE);
        writeOffset = *lineSize - 1;    // continue wrting on top of the '\0'
        bytesToRead = BUFFERSIZE + 1;   // "+1" -> byte of previous read '\0', can be added to the possible read length
        *lineSize += BUFFERSIZE;
    }
    return NULL;
}

int main()
{
    char *line = NULL;
    int lineSize = 0;
    FILE *fp;

    fp = fopen("readLine.txt", "r");

    while (readline(&line, &lineSize, fp) != NULL)      // fake getline()
        printf("buffersize: %3d;\tline read: %s", lineSize, line);

    fclose(fp);
    free(line);
    return (0);
}
