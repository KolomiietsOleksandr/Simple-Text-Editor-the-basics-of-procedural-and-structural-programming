#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int command = 0;

     char** Array = NULL;
     int ArrayLines = 0;

     while (1)
     {
        printf("Write command 1-5:");
        scanf("%d", &command);

        if (command == 1)
        {
            char buffer[400];
            printf("Write text to append:");
            scanf(" %[^\n]", buffer);

            Array = (char**) realloc(Array, ArrayLines + 1 * sizeof(char *));
            Array[ArrayLines] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
            strcpy(Array[ArrayLines], buffer);
            ArrayLines++;
        }
     }
    return 0;
}