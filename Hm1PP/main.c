#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int command = 0;

    char** Array = NULL;
    int ArrayLines = 0;

    char FileName[50];

    while (1)
    {
        printf("Write command 1-7:");
        scanf("%d", &command);

        while (getchar() != '\n');

        if (command == 1)
        {
            char buffer[400];
            printf("Write text to append:");
            scanf("%[^\n]", buffer);

            if (ArrayLines == 0)
            {
                Array = (char**)malloc(sizeof(char*));
                Array[ArrayLines] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
                strcpy(Array[ArrayLines], buffer);
                ArrayLines++;
            } else
            {
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
            scanf("%s", FileName);

            FILE* file = fopen(FileName, "w");
            if (file != NULL)
            {
                for (int i = 0; i < ArrayLines; i++)
                {
                    fprintf(file, "%s\n", Array[i]);
                }
                fclose(file);
                printf("Array saved to %s\n", FileName);
            }
            else
            {
                printf("Error opening the file.\n");
            }
        }

        if (command == 5)
        {
            printf("Write file name to LOAD:");
            scanf("%s", FileName);

            FILE* file = fopen(FileName, "r");
            if (file != NULL)
            {
                char line[400];
                while (fgets(line, sizeof(line), file) != NULL)
                {
                    line[strlen(line) - 1] = '\0';
                    ArrayLines++;
                    Array = (char**)realloc(Array, ArrayLines * sizeof(char*));
                    Array[ArrayLines - 1] = (char*)malloc((strlen(line) + 1) * sizeof(char));
                    strcpy(Array[ArrayLines - 1], line);
                }
                fclose(file);
                printf("Array loaded from %s\n", FileName);
            }
            else
            {
                printf("Error opening the file.\n");
            }
        }

        if (command == 6)
        {
            char substring[100];
            printf("Enter the substring to search for: ");
            scanf("%s", substring);
            int found = 0;

            for (int i = 0; i < ArrayLines; i++)
            {
                char* line = Array[i];
                int position = -1;
                int first_letter_pos = -1;
                int last_letter_pos = -1;
                int substring_index = 0;

                for (int j = 0; j < strlen(line); j++)
                {
                    if (line[j] == substring[substring_index])
                    {
                        if (first_letter_pos == -1)
                        {
                            first_letter_pos = j;
                        }
                        last_letter_pos = j;
                        substring_index++;

                        if (substring_index == strlen(substring))
                        {
                            position = first_letter_pos;
                            printf("Word found in line %d, positions %d to %d: %s\n", i + 1, position + 1, last_letter_pos + 1, substring);
                            found = 1;
                            substring_index = 0;
                            first_letter_pos = -1;
                        }
                    }
                    else
                    {
                        substring_index = 0;
                        first_letter_pos = -1;
                        last_letter_pos = -1;
                    }
                }
            }

            if (!found) {
                printf("Substring not found in any line.\n");
            }
        }

        if (command == 7) {
            int line_index, position;
            char substring[100];

            printf("Enter line index for insertion: ");
            scanf("%d", &line_index);

            if (line_index < 1 || line_index > ArrayLines) {
                printf("Invalid line index.\n");
                continue;
            }

            printf("Enter position for insertion (0-%d): ", strlen(Array[line_index - 1]));
            scanf("%d", &position);

            if (position < 0 || position > strlen(Array[line_index - 1])) {
                printf("Invalid position.\n");
                continue;
            }

            printf("Enter substring to insert: ");
            scanf("%s", substring);

            int new_length = strlen(Array[line_index - 1]) + strlen(substring) + 1;
            Array[line_index - 1] = (char*)realloc(Array[line_index - 1], new_length * sizeof(char));

            char* temp = (char*)malloc(new_length * sizeof(char));
            strcpy(temp, Array[line_index - 1]);

            for (int i = 0; i < position; i++) {
                Array[line_index - 1][i] = temp[i];
            }

            for (int i = 0; i < strlen(substring); i++) {
                Array[line_index - 1][position + i] = substring[i];
            }

            for (int i = position; i < strlen(temp); i++) {
                Array[line_index - 1][position + strlen(substring) + i] = temp[i];
            }

            free(temp);
        }

        if (command < 0 || command > 7) {
            printf("The command is not implemented.\n");
        }
    }
    return 0;
}
