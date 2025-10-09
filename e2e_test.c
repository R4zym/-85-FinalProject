#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define E2E_TEST_FILE "e2e_test_output.csv"


void set_active_data_file(const char* filename);
void addquestion();
int searchquestion();

// --- Test Helper Functions ---


static void set_stdin_input(const char *input) {
    FILE *mock_file = fopen("mock_stdin_e2e.txt", "w");
    if (mock_file) {
        fputs(input, mock_file);
        fclose(mock_file);
        freopen("mock_stdin_e2e.txt", "r", stdin);
    }
}


static void reset_stdin() {
#ifdef _WIN32
    freopen("CON", "r", stdin);
#else
    freopen("/dev/tty", "r", stdin);
#endif
}

// Prepares the data file for the E2E test
static void setup_e2e_environment() {
    FILE *data_file = fopen(E2E_TEST_FILE, "w"); // <--- แก้ไขตรงนี้
    if (data_file) {
        fprintf(data_file, "id,question,type,department,date,activate\n");
        fclose(data_file);
    }
}

// --- End-to-End Test Case ---

void EndToEndTestQuestionWorkflow() {
    printf("\n=== Running END-TO-END TEST ===\n");

    set_active_data_file(E2E_TEST_FILE);

    setup_e2e_environment();

    printf("  [STEP 1] Adding a new question...\n");
    set_stdin_input("3\nWhat are the project goals for Q1?\nStrategic\n");
    addquestion();

    printf("  [STEP 2] Searching for the new question...\n");
    set_stdin_input("1\nWhat are the project goals for Q1?\n");
    int search_result = searchquestion();

    assert(search_result == 1);
    printf("  [STEP 3] Verification PASSED.\n");

    printf("\n--- END-TO-END TEST PASSED ---\n\n");

    // --- Cleanup ---
    remove(E2E_TEST_FILE);
    remove("mock_stdin_e2e.txt");
    set_active_data_file(NULL);
    reset_stdin();
}