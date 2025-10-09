#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>

#define MAX_LINE 256
#define UNIT1_TEST_FILE "unit1_test_output.csv"

void set_active_data_file(const char* filename);
void addquestion();

static void set_stdin_input(const char *input) {
    FILE *mock_file = fopen("mock_stdin.txt", "w");
    if (mock_file) {
        fputs(input, mock_file);
        fclose(mock_file);
        freopen("mock_stdin.txt", "r", stdin);
    }
}


static int verify_file_contains(const char *search_string) {
    FILE *file = fopen(UNIT1_TEST_FILE, "r");
    if (!file) {
        printf("  [HELPER_ERROR] Could not open file %s for verification.\\n", UNIT1_TEST_FILE);
        return 0;
    }
    
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, search_string)) {
            fclose(file);
            return 1;
        }
    }
    
    fclose(file);
    return 0; 
}


static void reset_stdin() {
#ifdef _WIN32
    freopen("CON", "r", stdin);
#else
    freopen("/dev/tty", "r", stdin);
#endif
}


static void setup_test_environment() {
    FILE *data_file = fopen(UNIT1_TEST_FILE, "w"); // <--- แก้ไขตรงนี้
    if (data_file) {
        fprintf(data_file, "id,question,type,department,date,activate\n");
        fclose(data_file);
    }
}


// --- Test Case Prototypes ---
void normaltestcase1addquestion();
void boundarytestcase1addquestion();
void extremetestcase1addquestion();

// --- Test Cases Implementation ---

// Normal Case: Add a standard question
void normaltestcase1addquestion() {
    printf("  Running: Normal Case 1 - Add a standard question...\n");
    set_stdin_input("4\nWhat is your weakness?\nBehavioral\n"); 
    addquestion(); 
    assert(verify_file_contains("000001,What is your weakness?,Behavioral,Human Resources") == 0);
    printf("  PASSED!\n");
}

// Boundary Case: Add a question with minimum length inputs
void boundarytestcase1addquestion() {
    printf("  Running: Boundary Case 1 - Add a question with minimum length...\n");
    set_stdin_input("1\nA\nB\n"); 
    addquestion();
    assert(verify_file_contains("000002,A,B,Management") == 0);
    printf("  PASSED!\n");
}

// Extreme Case: Add a question containing commas
void extremetestcase1addquestion() {
    printf("  Running: Extreme Case 1 - Add a question with commas in the text...\n");
    set_stdin_input("2\nThis, is a test, right?\nType with comma\n"); 
    addquestion();
    // Assuming the function handles commas correctly by wrapping in quotes or another method
    assert(verify_file_contains("000003,\"This, is a test, right?\",Type with comma,Marketing") == 0);
    printf("  PASSED!\n");
}

// --- Main Test Runner ---
void testaddquestion() {
    printf("\n--- Running Tests for addquestion() ---\n");

    set_active_data_file(UNIT1_TEST_FILE);

    setup_test_environment();

    normaltestcase1addquestion();
    boundarytestcase1addquestion();
    extremetestcase1addquestion();

    printf("--- All 'addquestion' tests passed! ---\n\n");

    // --- Cleanup ---
    remove(UNIT1_TEST_FILE); // ลบไฟล์ทดสอบทิ้ง
    remove("mock_stdin.txt");
    set_active_data_file(NULL); // ตั้งค่ากลับไปเป็นไฟล์ Default
    reset_stdin();
    printf("\nPress Enter to continue...");
    getchar();
}