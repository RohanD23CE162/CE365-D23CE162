#include <stdio.h>
#include <string.h>

int main() {
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Validate a string (against a*bb)\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            char input[500]; // Character array for user input

            printf("Enter a string: ");
            scanf("%s", input); // Read the input string from the user

            int len = strlen(input); // Calculate length of input string

            // Validate string using custom logic
            int i = 0;
            while (input[i] == 'a') { // Count leading 'a's
                i++;
            }

            // Check for "bb" and end of string
            if (input[i] == 'b' && input[i + 1] == 'b' && input[i + 2] == '\0') {
                printf("Valid String\n");
            } else {
                printf("Invalid String\n");
            }
        } else if (choice == 2) {
            printf("Exiting the program.\n");
        } else {
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 2);

    return 0;
}
