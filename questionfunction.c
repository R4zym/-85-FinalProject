#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define DEFAULT_FILE_NAME "questiondata_en.csv"

static const char* g_active_data_file = DEFAULT_FILE_NAME;

#define MAX_LINE 256
#define MAX_Q 500
#define LINE_SIZE 300

typedef struct {
    char id[16];
    char question[500];
    char type[200];
    char department[200];
    char date[100];
    char activate[2];
} Question; 

int is_test_mode = 0; // Global

void updatequestion();
void addquestion();
int searchquestion();
void deletequestion();
int load_from_file(Question list[], int *count);



void set_active_data_file(const char* filename) {
    if (filename != NULL && strlen(filename) > 0) {
        g_active_data_file = filename;
    } else {
        // ถ้าไม่มีชื่อไฟล์ส่งมา ให้กลับไปใช้ไฟล์ Default (ไฟล์จริง)
        g_active_data_file = DEFAULT_FILE_NAME;
    }
}

void save_to_file(Question list[], int count) {
    // แก้ไข fopen ให้ใช้ตัวแปร g_active_data_file
    FILE *fp = fopen(g_active_data_file, "w");
    if (!fp) {
        printf("Cannot open file for writing: %s\n", g_active_data_file);
        return;
    }

    fprintf(fp, "id,question,type,department,date,activate\n");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,\"%s\",\"%s\",\"%s\",%s,%s\n",
                list[i].id, list[i].question, list[i].type,
                list[i].department, list[i].date, list[i].activate);
    }
    fclose(fp);
}

void openfile(){
    FILE *questiondata;
    questiondata = fopen(g_active_data_file,"r");

    if (questiondata == NULL) {
        fprintf(stderr, "[ERROR] Could not open file '%s'\n", g_active_data_file);
        return;
    }
    
    printf("\n====================================================================================================================\n");
    printf("                                          Question Data from File\n");
    printf("====================================================================================================================\n");
    
    char line[LINE_SIZE];
    int row = 0;
    while (fgets(line, sizeof(line), questiondata)) {
        line[strcspn(line, "\n\r")] = 0; // Remove trailing newline

        char *col1 = strtok(line, ",");
        char *col2 = strtok(NULL, ",");
        char *col3 = strtok(NULL, ",");
        char *col4 = strtok(NULL, ",");
        char *col5 = strtok(NULL, ",");
        char *col6 = strtok(NULL, ",");

        if (row == 0) {
            printf("%-8s | %-50s | %-25s | %-20s | %-15s | %-8s\n", "ID", "Question", "Type", "Department", "Date", "Active");
            printf("--------------------------------------------------------------------------------------------------------------------\n");
        } else {
            printf("%-8s | %-50s | %-25s | %-20s | %-15s | %-8s\n", col1 ? col1 : "", col2 ? col2 : "", col3 ? col3 : "", col4 ? col4 : "", col5 ? col5 : "", col6 ? col6 : "");
        }
        row++;
    }
    
    printf("====================================================================================================================\n\n");

    fclose(questiondata);
}

void addquestion() {
    Question list[MAX_Q];
    int count = 0;
    load_from_file(list, &count);

    if (count >= MAX_Q) {
        printf("Cannot add question because the list is full\n");
        return;
    }

    int questionDepartmentChoice;
    char question_text[200] = "", type[60] = "", department[60] = "";

    do {
        printf("-----------Select Department-----------\n");
        printf("1. Management\n2. Marketing\n3. Sales\n4. Human Resources\n5. Finance & Accounting\n");
        printf("6. Operations / Production\n7. Customer Service\n8. Other\n9. Back to Main Menu\n");
        printf("--------------------------------\n");
        printf("Select department: ");
        scanf("%d", &questionDepartmentChoice);
        getchar();

        const char *departments[] = {"Management", "Marketing", "Sales", "Human Resources", "Finance & Accounting", "Operations / Production", "Customer Service", "Other"};
        if (questionDepartmentChoice >= 1 && questionDepartmentChoice <= 8) {
            strcpy(department, departments[questionDepartmentChoice - 1]);
        } else if (questionDepartmentChoice == 9) {
            printf("Returning to main menu...\n");
            return;
        } else {
            printf("Invalid option. Please choose 1-9\n");
        }
    } while (department[0] == '\0');

    printf("---------------Add New Question---------------\n");
    do {
        printf("Enter the question: ");
        fgets(question_text, sizeof(question_text), stdin);
        question_text[strcspn(question_text, "\n")] = 0;
        if (strlen(question_text) > 0) break;
        if (strlen(question_text) == 0) {
            printf("Question cannot be empty\n");
        }
    } while (1);

    do {
        printf("Enter the question type: ");
        fgets(type, sizeof(type), stdin);
        type[strcspn(type, "\n")] = 0;
        if (strlen(type) > 0) break;
        printf("Question type cannot be empty\n");
    } while (1);

    FILE *questiondata = fopen(g_active_data_file, "r");
    if (!questiondata) {
        printf("Error: Could not open the question file %s\n", g_active_data_file);
        return;
    }
    // Find the last id
    char line[MAX_LINE];
    int last_id = 0;
    while (fgets(line, sizeof(line), questiondata)) {
        char *token = strtok(line, ",");
        if (token != NULL && isdigit(token[0])) {
            int curr_id = atoi(token);
            if (curr_id > last_id) last_id = curr_id;
        }
    }
    fclose(questiondata);
    

    Question new_question;
    sprintf(new_question.id, "%06d", last_id + 1);
    strcpy(new_question.question, question_text);
    strcpy(new_question.type, type);
    strcpy(new_question.department, department);
    strcpy(new_question.activate, "1");

    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);
    sprintf(new_question.date, "%02d/%02d/%d", tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900);

    list[count] = new_question;
    count++;

    save_to_file(list, count);
    printf("\n? New question added successfully\n");
}

void trim(char *str) {
    char *end;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0) return;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    *(end+1) = 0;
}

int strcasecmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2))
            return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
        s1++; s2++;
    }
    return *s1 - *s2;
}

int load_from_file(Question list[], int *count) {
    FILE *fp = fopen(g_active_data_file, "r");
    if (!fp) {
        // ไม่ต้องแสดง error ถ้าเป็นไฟล์ test ที่ยังไม่มี
        if (strcmp(g_active_data_file, DEFAULT_FILE_NAME) == 0) {
             printf("Cannot open file for reading: %s\\n", g_active_data_file);
        }
        return 0;
    }

    char line[MAX_LINE * 2];
    *count = 0;
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp) && *count < MAX_Q) {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0) continue;

        sscanf(line, "%[^,],\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",%[^,],%s",
               list[*count].id, list[*count].question, list[*count].type,
               list[*count].department, list[*count].date, list[*count].activate);
        (*count)++;
    }
    fclose(fp);
    return 1;
}

int searchquestion() {
    Question list[MAX_Q];
    int count = 0;
    if (!load_from_file(list, &count) || count == 0) {
        printf("No questions found in the system.\n");
        return 0;
    }

    int questionchoice, found = 0;
    char type[200], question[500];

    do {
        found = 0;
        printf("-----------Search for Question-----------\n");
        printf("1. Search by Question Text\n");
        printf("2. Search by Question Type\n");
        printf("3. Back to Main Menu\n");
        printf("Select (1-3): ");
        if (scanf("%d", &questionchoice) != 1) {
             while(getchar() != '\n'); // Clear buffer on bad input
             printf("Invalid input. Please enter a number.\n");
             continue;
        }
        getchar(); // Consume newline

        if (questionchoice == 1) {
            printf("Enter text to search for: ");
            fgets(question, sizeof(question), stdin);
            question[strcspn(question, "\n")] = 0;
            printf("\n--- Search Results ---\n");
            for (int i = 0; i < count; i++) {
                if(strstr(list[i].question, question) != NULL) {
                    printf("ID: %s | Type: %s | Question: %s\n", list[i].id, list[i].type, list[i].question);
                    found = 1;
                }
            }
            if (!found) {
                printf("No matching questions found.\n");
            }
            printf("----------------------\n");
        } else if (questionchoice == 2) {
            printf("Enter question type to search for: ");
            fgets(type, sizeof(type), stdin);
            type[strcspn(type, "\n")] = 0;
            trim(type);
            printf("\n--- Search Results ---\n");
            for (int i = 0; i < count; i++) {
                if (strcasecmp(list[i].type, type) == 0) {
                    printf("ID: %s | Type: %s | Question: %s\n", list[i].id, list[i].type, list[i].question);
                    found = 1;
                }
            }

            if (!found) {
                printf("No questions found for this type.\n");
            }
            printf("----------------------\n");
        } else if (questionchoice == 3) {
            printf("Returning to main menu...\n");
            break;
        } else {
            printf("Invalid choice. Please select 1-3.\n");
        }

    } while (questionchoice != 3);

    return found;
}

void updatequestion() {
    Question list[MAX_Q];
    int count = 0;
    if (!load_from_file(list, &count)) return;

    char id[16];
    while (1) {
        printf("Enter the ID of the question to edit: ");
        if (fgets(id, sizeof(id), stdin) == NULL) {
            return;
        }
        id[strcspn(id, "\n")] = 0; 

        if (strlen(id) > 0) {
            break; 
        }
    }

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].id, id) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Error: Question ID '%s' not found\n", id);
        return;
    }

    printf("Current question: %s\n", list[index].question);
    printf("Enter new question (press Enter to skip): ");
    char buffer[200];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    if (strlen(buffer) > 0) {
        strcpy(list[index].question, buffer);
        save_to_file(list, count);
        printf("\n? Question updated successfully\n");
    } else {
        printf("\nUpdate cancelled\n");
    }
}

void deletequestion() {
    Question list[MAX_Q];
    int count = 0;
    if (!load_from_file(list, &count)) return;

    char id[16];

    while (1) {
        printf("Enter the ID of the question to delete (set status to 'inactive'): ");
        if (fgets(id, sizeof(id), stdin) == NULL) {
            return;
        }
        id[strcspn(id, "\n")] = 0;

        if (strlen(id) > 0) {
            break;
        }
    }
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].id, id) == 0) {
            strcpy(list[i].activate, "0");
            found = 1;
            break;
        }
    }

    if (found) {
        save_to_file(list, count);
        printf("\n? Question ID %s has been set to 'inactive' successfully\n", id);
    } else {
        printf("Error: Question ID '%s' not found\n", id);
    }
}

void testaddquestion();
void testsearchquestion();
void EndToEndTestQuestionWorkflow();


void UnitTestQuestionFunction() {
    is_test_mode = 0;
    printf("\n--- Running Unit Tests ---\n");
    testaddquestion();
    testsearchquestion();
    printf("\n--- Unit Tests Finished ---\n");
}

void EndToEndTestQuestionFunction() {
    is_test_mode = 0;
    printf("\n--- Running End-to-End Tests ---\n");
    EndToEndTestQuestionWorkflow();
    printf("\n--- End-to-End Tests Finished ---\n");
}