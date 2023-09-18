#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int command = 0;

    char** Array = NULL;
    int ArrayLines = 0;

    char FileName[50];

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
            Array[ArrayLines - 1][0] = '\0';
        }

        if (command == 3)
        {
            for (int i = 0; i < ArrayLines; i++)
            {
                printf("%d: %s\n", i + 1, Array[i]);
            }
        }

        if (command == 4)
        {
            printf("Write file name to SAVE:");
            scanf("%s", &FileName);

            FILE* file = fopen(FileName, "w");
            if (file != NULL)
            {
                for (int i = 0; i < ArrayLines; i++)
                {
                    fprintf(file, "%s\n", Array[i]);
                }
                fclose(file);
                printf("Array saved to %s \n", FileName);
            }
            else
            {
                printf("Error opening the file.\n");
            }
        }

        if (command == 5)
        {
            printf("Write file name to LOAD:");
            scanf("%s", &FileName);

            FILE* file = fopen(FileName, "r");
            if (file != NULL) {
                char line[400];
                while (fgets(line, sizeof(line), file) != NULL)
                {
                    line[strlen(line) - 1] = '\0'; // Видаляємо символ нового рядка з кінця рядка
                    ArrayLines++;
                    Array = (char**)realloc(Array, ArrayLines * sizeof(char*));
                    Array[ArrayLines - 1] = (char*)malloc((strlen(line) + 1) * sizeof(char));
                    strcpy(Array[ArrayLines - 1], line);
                }
                fclose(file);
                printf("Array loaded from %s \n", FileName);

            } else {
                printf("Error opening the file.\n");
            }
        }

        if (command < 0 || command > 8)
        {
            printf("The command is not implemented. \n");
        }
    }
    return 0;
}