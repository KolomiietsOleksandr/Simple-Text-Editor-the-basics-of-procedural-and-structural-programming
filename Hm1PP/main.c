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

            if (ArrayLines == 0) {
                // Якщо це перший рядок, виділимо пам'ять та скопіюємо введений текст
                Array = (char**)malloc(sizeof(char*));
                Array[ArrayLines] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
                strcpy(Array[ArrayLines], buffer);
                ArrayLines++;
            } else {
                // Якщо не перший рядок, збільшимо розмір попереднього рядка та додамо введений текст
                Array[ArrayLines - 1] = (char*)realloc(Array[ArrayLines - 1], (strlen(Array[ArrayLines - 1]) + strlen(buffer) + 1) * sizeof(char));
                strcat(Array[ArrayLines - 1], buffer);
            }
        }

        if (command == 2)
        {
            ArrayLines++;
            Array = (char**)realloc(Array, ArrayLines * sizeof(char*));
            Array[ArrayLines - 1] = (char*)malloc(1);
        }

        if (command == 5)
        {
            for (int i = 0; i < ArrayLines; i++)
            {
                printf("%d: %s\n", i + 1, Array[i]);
            }
        }
    }
    return 0;
}