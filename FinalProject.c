#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addUser(char ***names, int **ages, char ***emails, int *count) {
    *names = (char **)realloc(*names, (*count + 1) * sizeof(char *));
    *ages = (int *)malloc((*count + 1) * sizeof(int));
    *emails = (char **)realloc(*emails, (*count + 1) * sizeof(char *));
    (*names)[*count] = (char *)malloc(100 * sizeof(char));
    (*emails)[*count] = (char *)malloc(100 * sizeof(char));

    printf("Enter user name: ");
    scanf("%99s", (*names)[*count]);
    printf("Enter user age: ");
    scanf("%d", &(*ages)[*count]);
    printf("Enter user email: ");
    scanf("%99s", (*emails)[*count]);

    (*count)++;
}

void displayUsers(char **names, int *ages, char **emails, int count) {
    for (int i = 0; i < count; i++) {
        printf("Name: %s\n", names[i]);
        printf("Age: %d\n", ages[i]);
        printf("Email: %s\n", emails[i]);
    }
}

void searchUser(char **names, int *ages, char **emails, int count) {
    char searchName[100];

    printf("Enter name or email or age to search: ");
    scanf("%99s", searchName);

    int found = 0;
    for (int i = 0; i < count; i++) {
        char ageStr[10];
        sprintf(ageStr, "%d", ages[i]);
        if (strcmp(names[i], searchName) == 0 || strcmp(emails[i], searchName) == 0 || strcmp(ageStr, searchName) == 0 ) {
            printf("User found: Name: %s\n", names[i]);
            printf("Age: %d\n", ages[i]);
            printf("Email: %s\n", emails[i]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("User not found.\n");
    }
}

int main() {
    char **names = NULL, **emails = NULL;
    int *ages = NULL;
    int count = 0;

    addUser(&names, &ages, &emails, &count);
    displayUsers(names, ages, emails, count);
    searchUser(names, ages, emails, count);

    free(names);
    free(emails);
    free(ages);

    return 0;
}