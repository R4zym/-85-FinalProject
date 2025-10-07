#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

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

void updatequestion();

void pressEnterToContinue() {
    printf("\nกด Enter เพื่อดำเนินการต่อ...");
    while (getchar() != '\n');
}

void openfile(){
    FILE *questiondata;
    questiondata = fopen("questiondata.csv","r");

    if (questiondata == NULL) {
        fprintf(stderr, "[ERROR] ไม่สามารถเปิดไฟล์ 'questiondata.csv' ได้\n");
        return;
    }
    
    printf("\n====================================================================================================================\n");
    printf("                                                Question Data from File\n");
    printf("====================================================================================================================\n");

    char line[LINE_SIZE];

    
    int row = 0;
    while (fgets(line, sizeof(line), questiondata)) {
        line[strcspn(line, "\n\r")] = 0;

        if (row == 0) {
            char *col1 = strtok(line, ",");
            char *col2 = strtok(NULL, ",");
            char *col3 = strtok(NULL, ",");
            char *col4 = strtok(NULL, ",");
            char *col5 = strtok(NULL, ",");
            char *col6 = strtok(NULL, ",");
            printf("%-8s | %-50s | %-25s | %-20s | %-15s | %-8s\n", col1 ? col1 : "", col2 ? col2 : "", col3 ? col3 : "", col4 ? col4 : "", col5 ? col5 : "", col6 ? col6 : "");
            printf("--------------------------------------------------------------------------------------------------------------------\n");
        } else {
            char *col1 = strtok(line, ",");
            char *col2 = strtok(NULL, ",");
            char *col3 = strtok(NULL, ",");
            char *col4 = strtok(NULL, ",");
            char *col5 = strtok(NULL, ",");
            char *col6 = strtok(NULL, ",");
            printf("%-8s | %-50s | %-25s | %-20s | %-15s | %-8s\n", col1 ? col1 : "", col2 ? col2 : "", col3 ? col3 : "", col4 ? col4 : "", col5 ? col5 : "", col6 ? col6 : "");
        }
        row++;
    }
    
    printf("====================================================================================================================\n\n");
    
    pressEnterToContinue();

    fclose(questiondata);
}

void addquestion() {
    int qid = 0, questiontypechoice, day, month, year , questionDepartmentChoice;
    char question[200] = "", type[60] = "", department[60] = "", date[30] = "", line[300], activate[2] = "1";
    time_t t;
    struct tm *tm_info;

    FILE *questiondata = fopen("questiondata.csv", "r");
    if (questiondata == NULL) {
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return;
    }

    
    do {
        printf("-----------Department-----------\n");
        printf("1. Management\n");
        printf("2. Marketing\n");
        printf("3. Sales\n");
        printf("4. Human Resources\n");
        printf("5. Finance & Accounting\n");
        printf("6. Operations / Production\n");
        printf("7. Customer Service\n");
        printf("8. Other\n");
        printf("9. กลับเมนูหลัก\n");
        printf("--------------------------------\n");
        printf("เลือกประเภทคำถาม: ");
        scanf("%d", &questionDepartmentChoice);
        getchar();
        if (questionDepartmentChoice == 1) {
            strcpy(department, "Management");
        } else if (questionDepartmentChoice == 2) {
            strcpy(department, "Marketing");
        } else if (questionDepartmentChoice == 3) {
            strcpy(department, "Sales");
        } else if (questionDepartmentChoice == 4) {
            strcpy(department, "Human Resources");
        } else if (questionDepartmentChoice == 5) {
            strcpy(department, "Finance & Accounting");
        } else if (questionDepartmentChoice == 6) {
            strcpy(department, "Operations / Production");
        } else if (questionDepartmentChoice == 7) {
            strcpy(department, "Customer Service");
        } else if (questionDepartmentChoice == 8) {
            strcpy(department, "Other");
        } else if (questionDepartmentChoice == 9) {
            printf("กลับเมนูหลัก\n");
            fclose(questiondata);
            pressEnterToContinue();
            return;
        } else {
            printf("กรุณาเลือก 1-9\n");
        }
    } while (questionDepartmentChoice != 1 && questionDepartmentChoice != 2 && questionDepartmentChoice != 3 && questionDepartmentChoice != 4 && questionDepartmentChoice != 5 && questionDepartmentChoice != 6 && questionDepartmentChoice != 7 && questionDepartmentChoice != 8 && questionDepartmentChoice != 9);

    // หา id ล่าสุด
    int last_id = 0;
    while (fgets(line, sizeof(line), questiondata)) {
        char *token = strtok(line, ",");
        if (token != NULL && isdigit(token[0])) {
            int curr_id = atoi(token);
            if (curr_id > last_id) last_id = curr_id;
        }
    }
    fclose(questiondata);

    
    printf("---------------เพิ่มคำถามใหม่---------------\n");
    printf("กรอกคำถาม: ");
    fgets(question, sizeof(question), stdin);
    question[strcspn(question, "\n")] = 0;

    if (strlen(question) == 0) {
        printf("กรุณากรอกคำถาม\n");
        pressEnterToContinue();
        return;
    }

    
    printf("กรอกประเภทคำถาม: ");
    fgets(type, sizeof(type), stdin);
    type[strcspn(type, "\n")] = 0;
    if (strlen(type) == 0) {
        printf("กรุณากรอกประเภทคำถาม\n");
        pressEnterToContinue();
        return;
    }

    
    time(&t);
    tm_info = localtime(&t);
    year = tm_info->tm_year + 1900;
    month = tm_info->tm_mon + 1;
    day = tm_info->tm_mday;
    sprintf(date, "%02d/%02d/%04d", day, month, year);

    
    questiondata = fopen("questiondata.csv", "a");
    if (questiondata == NULL) {
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return;
    }
    fprintf(questiondata, "%06d,%s,%s,%s,%s,%s\n", last_id + 1, question, type, department, date, activate);
    fclose(questiondata);

    printf("เพิ่มคำถามใหม่เรียบร้อย\n");
    pressEnterToContinue();
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
    FILE *questiondata = fopen("questiondata.csv", "r");
    if (!questiondata) return 0;

    char line[LINE_SIZE];
    *count = 0;

    // skip header
    fgets(line, sizeof(line), questiondata);

    while (fgets(line, sizeof(line), questiondata)) {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0) continue;

        sscanf(line, "%15[^,],%199[^,],%59[^,],%59[^,],%29[^,],%7[^,\n]", list[*count].id, list[*count].question, list[*count].type, list[*count].department, list[*count].date, list[*count].activate);
        (*count)++;
    }
    fclose(questiondata);
    return 1;
}

void searchquestion() {
    Question list[MAX_Q];
    int count = 0;
    if (!load_from_file(list, &count) || count == 0) {
        printf("ไม่มีคำถามในระบบ\n");
        pressEnterToContinue();
        return;
    }

    int questionchoice, found = 0;
    char type[60], question[200];

    do {
        found = 0;
        printf("-----------ค้นหาคำถาม-----------\n");
        printf("1. ค้นหาจากคำถาม\n");
        printf("2. ค้นหาจากประเภทคำถาม\n");
        printf("3. กลับเมนูหลัก\n");
        printf("เลือก (1-3): ");
        scanf("%d", &questionchoice);
        getchar();

        if (questionchoice == 1) {
            printf("ค้นหาจากคำถาม\n");
            printf("กรอกคำถามที่ต้องการค้นหา: ");
            fgets(question, sizeof(question), stdin);
            question[strcspn(question, "\n")] = 0;
            printf("---------------------------------------------------------------------------------\n");
            printf("| %-10s | %-40s | %-25s | %-20s |\n", "รหัส", "คำถาม", "ประเภท", "วันที่เพิ่ม");
            printf("---------------------------------------------------------------------------------\n");
            for (int i = 0; i < count; i++) {
                if(strstr(list[i].question, question) != NULL) {
                    printf("| %-10s | %-40s | %-25s | %-20s |\n", list[i].id, list[i].question, list[i].type, list[i].date);
                    found = 1;
                }
            }
            if (!found) {
                printf("ไม่พบคำถามที่ค้นหา\n");
            }
        }

        if (questionchoice == 2) {
            printf("ค้นหาจากประเภทคำถาม\n");
            printf("กรอกประเภทคำถามที่ต้องการค้นหา: ");
            fgets(type, sizeof(type), stdin);
            type[strcspn(type, "\n")] = 0;
            trim(type);

            found = 0;
            for (int i = 0; i < count; i++) {
                if (strcasecmp(list[i].type, type) == 0) {
                    printf("เจอคำถามประเภท %s: %s\n", type, list[i].question);
                    found = 1;
                }
            }

            if (!found) {
                printf("ไม่พบคำถามในประเภทนี้\n");
            }
        }

        if (questionchoice == 3) {
            printf("กลับเมนูหลัก\n");
            break;
        }

    } while (questionchoice != 3);

    pressEnterToContinue();
}

void updatequestion(){
    Question list[MAX_Q];
    int count = 0;
    if (!load_from_file(list, &count) || count == 0) {
        printf("ไม่มีคำถามในระบบ\n");
        pressEnterToContinue();
        return;
    }

    char id[16];
    printf("กรอก ID คำถามที่ต้องการแก้ไข: ");
    scanf("%15s", id);
    getchar();

    int found = 0;
    for(int i = 0; i < count; i++) {
        if(strcmp(list[i].id, id) == 0) {
            found = 1;
            printf("พบคำถาม: %s\n", list[i].question);
            printf("ประเภทคำถามเดิม: %s\n", list[i].type);

            printf("กรอกคำถามใหม่ (หากไม่ต้องการเปลี่ยนแปลง กด Enter): \n");
            char new_question[200];
            fgets(new_question, sizeof(new_question), stdin);
            new_question[strcspn(new_question, "\n")] = 0;
            if (strlen(new_question) > 0) {
                strcpy(list[i].question, new_question);
            }

            printf("กรอกประเภทคำถามใหม่ (หากไม่ต้องการเปลี่ยนแปลง กด Enter): \n");
            char new_type[60];
            fgets(new_type, sizeof(new_type), stdin);
            new_type[strcspn(new_type, "\n")] = 0;
            if (strlen(new_type) > 0) {
                strcpy(list[i].type, new_type);
            }

            printf("สถานะเดิม: %s\n", list[i].activate);
            printf("กรอกสถานะใหม่ (1=ใช้งาน, 0=ไม่ใช้งาน) (หากไม่ต้องการเปลี่ยนแปลง กด Enter): \n");
            char new_activate[2];
            fgets(new_activate, sizeof(new_activate), stdin);
            new_activate[strcspn(new_activate, "\n")] = 0;
            if (strlen(new_activate) > 0) {
                strcpy(list[i].activate, new_activate);
            }

            time_t t;
            struct tm *tm_info;
            time(&t);
            tm_info = localtime(&t);
            int year = tm_info->tm_year + 1900;
            int month = tm_info->tm_mon + 1;
            int day = tm_info->tm_mday;
            sprintf(list[i].date, "%02d/%02d/%04d", day, month, year);
            strncpy(list[i].date, list[i].date, sizeof(list[i].date)-1);
            break;
        }
    }

    if (!found) {
        printf("ไม่พบคำถามที่มี ID นี้\n");
        pressEnterToContinue();
        return;
    }

    FILE *questiondata = fopen("questiondata.csv", "w");
    if(!questiondata) {
        printf("ไม่สามารถเปิดไฟล์เพื่อเขียนได้\n");
        pressEnterToContinue();
        return;
    }

    fprintf(questiondata, "id,question,type,department,date,activate\n");

    for(int i= 0; i < count; i++) {
        fprintf(questiondata, "%s,%s,%s,%s,%s,%s\n", list[i].id, list[i].question, list[i].type, list[i].department, list[i].date, list[i].activate);
    }
    fclose(questiondata);

    printf("แก้ไขคำถามเรียบร้อย\n");
    pressEnterToContinue();
}

void deletequestion(){
    Question list[MAX_Q];
    int count = 0;
    char id[16];
    if (!load_from_file(list, &count) || count == 0) {
        printf("ไม่มีคำถามในระบบ\n");
        pressEnterToContinue();
        return;
    }

    printf("กรุณากรอกรหัสคำถามที่ต้องการลบ : ");
    scanf("%15s", id);
    getchar();

    int found = 0;
    for(int i = 0; i < count; i++) {
        if(strcmp(list[i].id, id) == 0) {
            strcpy(list[i].activate, "0");
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("ไม่พบรหัสคำถามนี้\n");
        pressEnterToContinue();
        return;
    }

    FILE *questiondata = fopen("questiondata.csv", "w");
    if(!questiondata) {
        printf("ไม่สามารถเปิดไฟล์เพื่อเขียนได้\n");
        pressEnterToContinue();
        return;
    }

    fprintf(questiondata, "id,question,type,department,date,activate\n");
    for(int i = 0; i < count; i++) {
        fprintf(questiondata, "%s,%s,%s,%s,%s,%s\n", list[i].id, list[i].question, list[i].type, list[i].department, list[i].date, list[i].activate);
    }
    fclose(questiondata);

    printf("ลบคำถามเรียบร้อย\n");
    pressEnterToContinue();
}