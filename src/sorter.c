#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUMBER_OF_PARAMETERS 2
#define NUMBER_OF_STRINGS_TO_PRINT 100
#define MAX_STRING_SIZE 1000

int parse_arguments(int argc) {
    if (argc != NUMBER_OF_PARAMETERS) {
        fprintf(stderr, "Incorrect number of parameters\n");
        return -1;
    }
    return 0;
}

int is_punctuation_mark(char letter) {
    char punctuation_marks[] = ".,;:?!";
    for (size_t j = 0; j < strlen(punctuation_marks); j++) {
        if (letter == punctuation_marks[j]) {
            return -1;
        }
    }
    return 0;
}

void remove_punctuation_marks(char *string, size_t *number_of_strings) {
    *number_of_strings = *number_of_strings + 1;
    size_t string_length = strlen(string);
    size_t punctuation_marks_met = 0;
    for (size_t i = 0; i <= string_length; i++) {
        if (is_punctuation_mark(string[i]) != 0) {
            punctuation_marks_met++;
        } else {
            string[i - punctuation_marks_met] = string[i];
            if (string[i] == '\n') {
                string[i - punctuation_marks_met] = '\0';
            }
        }
    }
}

int read_input_file(FILE *file, char **strings, size_t *number_of_strings) {
    for (size_t i = 0; i < NUMBER_OF_STRINGS_TO_PRINT; i++) {
        strings[i] = (char *) malloc(MAX_STRING_SIZE * sizeof(char));
        if (strings[i] == NULL) {
            fprintf(stderr, "Failed to allocate memory for strings\n");
            return -1;
        }
    }
    char *current_string = (char *) malloc(MAX_STRING_SIZE * sizeof(char));
    if (current_string == NULL) {
        fprintf(stderr, "Failed to allocate memory for string\n");
        return -1;
    }

    while (!feof(file)) {
        if (fgets(current_string, MAX_STRING_SIZE, file) == NULL) {
            if (feof(file) == 0) {
                fprintf(stderr, "Failed to read the string\n");
                return -1;
            } else {
                current_string[0] = '\0';
            }
        }
        remove_punctuation_marks(current_string, number_of_strings);
        if (*number_of_strings > NUMBER_OF_STRINGS_TO_PRINT) {
            *number_of_strings = NUMBER_OF_STRINGS_TO_PRINT;
        }
        int check = 0;
        for (size_t i = 0; i < NUMBER_OF_STRINGS_TO_PRINT; i++) {
            if (strcmp(strings[i], current_string) <= 0) {
                char *tmp = strings[*number_of_strings - 1];
                for (size_t j = *number_of_strings - 1; j > i; j--) {
                    strings[j] = strings[j - 1];
                }
                if (*number_of_strings < NUMBER_OF_STRINGS_TO_PRINT) {
                    strings[i] = strings[*number_of_strings];
                    strings[*number_of_strings] = tmp;
                } else {
                    strings[i] = tmp;
                }
                strcpy(strings[i], current_string);
                check = 1;
                break;
            }
        }
        if ((check == 0) && (*number_of_strings < NUMBER_OF_STRINGS_TO_PRINT)) {
            strcpy(strings[*number_of_strings - 1], current_string);
        }

    }
    free(current_string);
    return 0;
}

void print_strings(char **strings, size_t string_number) {
    for (int i = 0; i < string_number; i++) {
        fprintf(stdout, "%s\n", strings[i]);
    }
}

int main(int argc, char **argv) {
    if (parse_arguments(argc) != 0) {
        return -1;
    }
    FILE *input_file = fopen(argv[1], "rb");
    if (input_file == NULL) {
        fprintf(stderr, "Failed to open input file\n");
        return -1;
    }
    char **string_array = (char **) malloc(NUMBER_OF_STRINGS_TO_PRINT * sizeof(char *));
    if (string_array == NULL) {
        fprintf(stderr, "Failed to allocate memory for string array\n");
        return -1;
    }
    size_t number_of_strings = 0;
    if (read_input_file(input_file, string_array, &number_of_strings) != 0) {
        fprintf(stderr, "Failed to read input file\n");
        return -1;
    }
    print_strings(string_array, number_of_strings);
    for (int i = 0; i < number_of_strings; i++) {
        free(string_array[i]);
    }
    free(string_array);
    return 0;
}