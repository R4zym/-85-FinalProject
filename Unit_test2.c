#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX_LINE 256
#define UNIT2_TEST_FILE "unit2_test_output.csv"

void set_active_data_file(const char* filename);
int searchquestion();

// --- Test Helper Functions ---

// Creates a dummy data file for searching
static void setup_test_data() {
    FILE *data_file = fopen(UNIT2_TEST_FILE, "w"); // <--- แก้ไขตรงนี้
    if (data_file) {
        fprintf(data_file, "id,question,type,department,date,activate\n");
        fprintf(data_file, "000001,Metric question about success,Strategic,Management,2025-10-09,1\n");
        fprintf(data_file, "000002,What is the biggest bottleneck?,Operational,IT,2025-10-09,1\n");
        fclose(data_file);
    }
}


static void set_stdin_input(const char *input) {
    FILE *mock_file = fopen("mock_stdin_search.txt", "w");
    if (mock_file) {
        fputs(input, mock_file);
        fclose(mock_file);
        freopen("mock_stdin_search.txt", "r", stdin);
    }
}

// Resets stdin to the console
static void reset_stdin() {
#ifdef _WIN32
    freopen("CON", "r", stdin);
#else
    freopen("/dev/tty", "r", stdin);
#endif
}

// --- Test Cases ---

void normaltestsearchquestion() {
    printf("  Running: Normal Cases - Standard searches...\n");

    // Search for a full question
    set_stdin_input("1\nMetric question about success\n");
    assert(searchquestion() == 1 && "Normal Case 1 Failed");

    // Search by type
    set_stdin_input("2\nStrategic\n");
    assert(searchquestion() == 1 && "Normal Case 2 Failed");
    
    printf("  PASSED!\n");
}

void boundarytestsearchquestion() {
    printf("  Running: Boundary Cases - Edge condition searches...\n");
    

    set_stdin_input("1\nbottleneck\n");
    assert(searchquestion() == 1 && "Boundary Case 1 Failed");


    set_stdin_input("2\n Operational \n");
    assert(searchquestion() == 1 && "Boundary Case 2 Failed");


    set_stdin_input("1\nWhat\n");
    assert(searchquestion() == 1 && "Boundary Case 3 Failed");

    printf("  PASSED!\n");
}

void extremetestsearchquestion() {
    printf("  Running: Extreme Cases - Invalid and non-existent searches...\n");

    // Search for a question that does not exist, then exit
    set_stdin_input("1\nThis question does not exist\n3\n");
    assert(searchquestion() == 0 && "Extreme Case 1 Failed");

    // Input invalid menu option first, then a valid search
    set_stdin_input("4\n2\nOperational\n");
    assert(searchquestion() == 1 && "Extreme Case 2 Failed");

    printf("  PASSED!\n");
}

// --- Main Test Runner ---
void testsearchquestion() {
    printf("\n--- Running Tests for searchquestion() ---\n");

    set_active_data_file(UNIT2_TEST_FILE);

    setup_test_data();

    normaltestsearchquestion();
    boundarytestsearchquestion();
    extremetestsearchquestion();

    printf("--- All 'searchquestion' tests passed! ---\n\n");

    // --- Cleanup ---
    remove(UNIT2_TEST_FILE);
    remove("mock_stdin_search.txt");
    set_active_data_file(NULL);
    reset_stdin();
    printf("\nPress Enter to continue...");
    getchar();
}