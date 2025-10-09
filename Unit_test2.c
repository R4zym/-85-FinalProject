#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>

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

int searchquestion();

static void set_stdin_input(const char *input) {
    FILE *questiondata = fopen("testunit_input.csv", "w");
    fputs(input, questiondata);
    fclose(questiondata);
    freopen("testunit_input.csv", "r", stdin);
}

void normaltestcase1searchquestion() {
    printf("Normal Test Case 1: Searching for a question...\n");
    set_stdin_input("1\nตัวชี้วัด (Metric) ที่เราใช้อยู่ในปัจจุบัน สะท้อนความสำเร็จที่แท้จริงของแผนกเราได้ดีแค่ไหน?\n");
    searchquestion();
    assert(searchquestion() == 1);
    printf("Test case 1 Passed!\n");
}

void normaltestcase2searchquestion() {
    printf("Normal Test Case 2: Searching for a question...\n");
    set_stdin_input("1\nเป้าหมายหลัก (Key Objectives) ที่เราต้องทำให้สำเร็จในไตรมาสนี้/ปีนี้คืออะไร?\n");
    searchquestion();
    assert(searchquestion() == 1);
    printf("Test case 2 Passed!\n");
}

void normaltestcase3searchquestion() {
    printf("Normal Test Case 3: Searching for a question...\n");
    set_stdin_input("2\nคำถามเชิงกลยุทธ์\n");
    searchquestion();
    assert(searchquestion() == 1);
    printf("Test case 3 Passed!\n");
}

void normaltestsearchquestion() {
    printf("Normal Test: Searching for a question...\n");
    normaltestcase1searchquestion();
    normaltestcase2searchquestion();
    normaltestcase3searchquestion();
}

void Boundarytestcase1searchquestion() {
    printf("Boundary Test Case 1: Searching for a question...\n");
    set_stdin_input("1\nbottleneck\n");
    searchquestion();
    assert(searchquestion() == 1);
    printf("Boundary Test Case 1 Passed!\n");
}

void Boundarytestcase2searchquestion() {
    printf("Boundary Test Case 2: Searching for a question...with whitespace\n");
    set_stdin_input("2\n คำถามเชิงกลยุทธ์ \n");
    searchquestion();
    assert(searchquestion() == 1);
    printf("Boundary Test Case 2 Passed!\n");
}

void Boundarytestcase3searchquestion() {
    printf("Boundary Test Case 3: Searching for a question...\n");
    set_stdin_input("1\nอะไร?\n");
    searchquestion();
    assert(searchquestion() == 1);
    printf("Boundary Test Case 3 Passed!\n");
}

void Boundarytestsearchquestion() {
    printf("Boundary Test: Searching for a question...\n");
    Boundarytestcase1searchquestion();
    Boundarytestcase2searchquestion();
    Boundarytestcase3searchquestion();
}

void extremetestcase1searchquestion() {
    printf("Extreme Test Case 1: Searching for a question...\n");
    set_stdin_input("1\nThis question does not exist\n3\n");
    searchquestion();
    assert(searchquestion() == 0);
    printf("Extreme Test Case 1 Passed!\n");
}

void extremetestcase2searchquestion() {
    printf("Extreme Test Case 2: Searching for a question...\n");
    set_stdin_input("4\n9\n2\nคำถามเชิงกลยุทธ์\n");
    searchquestion();
    assert(searchquestion() == 1);
    printf("Extreme Test Case 2 Passed!\n");
}

void extremetestsearchquestion() {
    printf("Extreme Test: Searching for a question...\n");
    extremetestcase1searchquestion();
    extremetestcase2searchquestion();

    printf("All Extreme Test Cases Passed!\n");
}

void testsearchquestion() {
    printf("Testing searchquestion function...\n");
    normaltestsearchquestion();
    Boundarytestsearchquestion();
    extremetestsearchquestion();
}