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
    char activate[8];
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
    printf("                                                ข้อมูลคำถามจากไฟล์\n");
    printf("====================================================================================================================\n");
    printf("%-8s | %-50s | %-25s | %-20s | %-15s | %-8s\n", "รหัส", "คำถาม", "ประเภท", "Department", "วันที่เพิ่ม", "สถานะ");
    printf("--------------------------------------------------------------------------------------------------------------------\n");

    char line[LINE_SIZE];

    // ข้าม header
    fgets(line, sizeof(line), questiondata);

    while (fgets(line, sizeof(line), questiondata)) {
        line[strcspn(line, "\n\r")] = 0;

        char *col1 = strtok(line, ",");
        char *col2 = strtok(NULL, ",");
        char *col3 = strtok(NULL, ",");
        char *col4 = strtok(NULL, ",");
        char *col5 = strtok(NULL, ",");
        char *col6 = strtok(NULL, ",");
        if (col1 && col2 && col3 && col4 && col5 && col6) {
            printf("%-8s | %-50s | %-25s | %-20s | %-15s | %-8s\n", col1, col2, col3, col4, col5, col6);
        }
    }
    printf("====================================================================================================================\n\n");
    
    pressEnterToContinue();

    fclose(questiondata);
}

void addquestion() {
    int qid = 0, questiontypechoice, day, month, year;
    char question[200] = "", type[60] = "", department[60] = "", date[30] = "", line[300], activate[8] = "1";
    time_t t;
    struct tm *tm_info;

    FILE *questiondata = fopen("questiondata.csv", "r");
    if (questiondata == NULL) {
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return;
    }

    // เลือกประเภทคำถาม
    do {
        printf("-----------ประเภทคำถาม-----------\n");
        printf("1. ปลายเปิด\n");
        printf("2. ปลายปิด\n");
        printf("3. กลับเมนูหลัก\n");
        printf("เลือกประเภทคำถาม: ");
        scanf("%d", &questiontypechoice);
        getchar();
        if (questiontypechoice == 1) {
            strcpy(type, "ปลายเปิด");
        } else if (questiontypechoice == 2) {
            strcpy(type, "ปลายปิด");
        } else if (questiontypechoice == 3) {
            printf("กลับเมนูหลัก\n");
            fclose(questiondata);
            pressEnterToContinue();
            return;
        } else {
            printf("กรุณาเลือก 1-3\n");
        }
    } while (questiontypechoice != 1 && questiontypechoice != 2);

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

    // รับคำถาม
    printf("---------------เพิ่มคำถามใหม่---------------\n");
    printf("กรอกคำถาม: ");
    fgets(question, sizeof(question), stdin);
    question[strcspn(question, "\n")] = 0;

    if (strlen(question) == 0) {
        printf("กรุณากรอกคำถาม\n");
        pressEnterToContinue();
        return;
    }

    // รับแผนก
    printf("กรอกชื่อแผนก: ");
    fgets(department, sizeof(department), stdin);
    department[strcspn(department, "\n")] = 0;
    if (strlen(department) == 0) {
        printf("กรุณากรอกชื่อแผนก\n");
        pressEnterToContinue();
        return;
    }

    // สร้างวันที่
    time(&t);
    tm_info = localtime(&t);
    year = tm_info->tm_year + 1900;
    month = tm_info->tm_mon + 1;
    day = tm_info->tm_mday;
    sprintf(date, "%02d/%02d/%04d", day, month, year);

    // เขียนไฟล์
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

        sscanf(line, "%15[^,],%199[^,],%59[^,],%59[^,],%29[^,],%7[^,\n]",
                list[*count].id,
                list[*count].question,
                list[*count].type,
                list[*count].department,
                list[*count].date,
                list[*count].activate);
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
    // ยังไม่ได้ปรับปรุงเต็มรูปแบบ
    printf("ฟังก์ชันแก้ไขคำถามยังไม่พร้อมใช้งาน\n");
    pressEnterToContinue();
}

void deletequestion(){
    // ยังไม่ได้ปรับปรุงเต็มรูปแบบ
    printf("ฟังก์ชันลบคำถามยังไม่พร้อมใช้งาน\n");
    pressEnterToContinue();
}