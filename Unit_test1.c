#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>

#define FILE_NAME "questiondata.csv"

#define MAX_LINE 256
#define MAX_Q 200
#define LINE_SIZE 300

typedef struct {
    char id[16];
    char question[200];
    char type[60];
    char department[60];
    char date[30];
    char activate[2];
} Question; 

int verify_file_contains(const char* expected_string) {
    FILE* file = fopen(FILE_NAME, "r");
    if (!file) return 0;

    char line[LINE_SIZE];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, expected_string) != NULL) {
            found = 1;
            break;
        }
    }
    fclose(file);
    return found;
}

void addquestion();

extern int is_test_mode;

static void set_stdin_input(const char *input) {
    FILE *questiondata = fopen(FILE_NAME, "a");
    fputs(input, questiondata);
    fclose(questiondata);
    freopen(FILE_NAME, "r", stdin);
}

void normaltestcase1addquestion() {
    printf("  Running: Normal Case 1 - Add a standard question...\n");
    set_stdin_input("4\nWhat is your weakness?\nBehavioral\n");
    addquestion();
    assert(verify_file_contains("000001,What is your weakness?,Behavioral,Human Resources") == 1);
    printf("  PASSED!\n");
}

void boundarytestcase1addquestion() {
    printf("  Running: Boundary Case 1 - Add a question with minimum length...\n");
    set_stdin_input("1\nA\nB\n");
    addquestion();
    assert(verify_file_contains("000002,A,B,Management") == 1);
    printf("  PASSED!\n");
}

void extremetestcase1addquestion() {
    printf("  Running: Extreme Case 1 - Add a question with commas in the text...\n");
    set_stdin_input("2\nThis, is a test, right?\nType, with, comma\n");
    addquestion();

    assert(verify_file_contains("000003,This, is a test, right?,Type, with, comma,Marketing") == 1);
    printf("  PASSED!\n");
}

// --- Main Test Function ---
void testaddquestion() {
    printf("Setting up test environment for addquestion...\n");

    normaltestcase1addquestion();
    boundarytestcase1addquestion();
    extremetestcase1addquestion();

    printf("All 'addquestion' tests passed!\n");


    freopen("CON", "r", stdin);
}