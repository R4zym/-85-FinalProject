#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE 256
#define MAX_Q 100

typedef struct {
    char question[200];
    char type[30];
} Question;   

void updatequestion();

void pressEnterToContinue() {
    printf("\nกรุณากดปุ่ม Enter เพื่อไปต่อ...");
    while (getchar() != '\n');
}

void openfile(){
    FILE *questiondata;
    questiondata = fopen("questiondata.csv","r");

    if (questiondata == NULL) {
        fprintf(stderr, "[ERROR] ไม่สามารถเปิดไฟล์ 'questiondata.csv' ได้\n");
        return;
    }
    
    printf("\n======================================================================\n");
    printf("                       ข้อมูลจากไฟล์ (จัดคอลัมน์)\n");
    printf("======================================================================\n");
    printf("%-5s | %-40s | %-20s | %-20s\n", "รหัสคำถาม", "คำถาม", "ประเภทคำถาม", "วันที่เพิ่มคำถาม");
    printf("----------------------------------------------------------------------\n");

    char line[256];

    while (fgets(line, sizeof(line), questiondata)) {
        line[strcspn(line, "\n\r")] = 0;

        char *col1 = strtok(line, ",");
        char *col2 = strtok(NULL, ",");
        char *col3 = strtok(NULL, ",");
        char *col4 = strtok(NULL, ",");
        if (col1 != NULL && col2 != NULL && col3 != NULL && col4 != NULL) {
            printf("%-5s | %-40s | %-20s | %-20s\n", col1, col2, col3, col4);
        }
    }
    printf("======================================================================\n\n");
    
    pressEnterToContinue();

    fclose(questiondata);
}

void addquestion(){
    int qid , numberquestion , questiontypechoice , day , month , year , choice;
    char question[200], type[30], date[30], line[300] , id[10];
    size_t len , lenquestion , lentype , lendate;
    char *token;
    time_t t;
    struct tm *tm_info;
    

    FILE *questiondata;
    questiondata = fopen("questiondata.csv","r");

    if(questiondata == NULL){
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return;
    }

    do // เปลี่ยนเป็น switch case
    {
        printf("-----------ประเภทคำถาม-----------\n");
        printf("1. คำถามปลายเปิด\n");
        printf("2. คำถามปลายปิด\n");
        printf("3. ออกจากเมนูเพิ่มคำถาม\n");
        printf("เลือกประเภทคำถาม: ");
        scanf("%d", &questiontypechoice);
            if(questiontypechoice == 1){
                strcpy(type, "คำถามปลายเปิด");
            }
            if(questiontypechoice == 2){
                strcpy(type, "คำถามปลายปิด");
            }
            if(questiontypechoice == 3){
                printf("ออกจากเมนูเพิ่มคำถาม\n");
                return;
            }
            if (questiontypechoice != 1 && questiontypechoice != 2 && questiontypechoice != 3){
                printf("กรุณาเลือก(1-3)\n");
            }
            
    } while (questiontypechoice != 1 && questiontypechoice != 2);

    fgets(line, sizeof(line), questiondata);
    while(fgets(line, sizeof(line), questiondata) != NULL) {
        token = strtok(line, ",");
        if (token != NULL) {
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(id, token);
                qid = atoi(id);
                printf("id: %d\n", qid);
            }
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(question, token);
                printf("question: %s\n", question);
            }
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(type, token);
                printf("type: %s\n", type);
            }
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(date, token);
                printf("date: %s\n", date);
            }
        }
    }
    numberquestion = qid + 1;

    fclose(questiondata);

    questiondata = fopen("questiondata.csv","a");

    if(questiondata == NULL){
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return;
    }

    printf("---------------เพิ่มข้อมูลคำถามใหม่---------------\n");

    fscanf(stdin, "%c");
    do
    {
        printf("หากต้องการกลับเมนูหลัก(กด 0):");
        scanf("%d",choice);
        printf("กรอกคำถาม: ");
        scanf("%s", question);
        printf("กรอกประเภทคำถาม: ");
        scanf("%s", type);
        
        lenquestion = strlen(question);
        lentype = strlen(type);
        if(lenquestion == 0){
            printf("กรุณากรอกคำถาม\n");
        }
        if(lentype == 0){
            printf("กรุณากรอกประเภทคำถาม\n");
        }
    } while (lenquestion != 0 && lentype != 0);

    time(&t);
    tm_info = localtime(&t);

    year = tm_info->tm_year + 1900;
    month = tm_info->tm_mon + 1;
    day = tm_info->tm_mday;

    sprintf(date, "%2d/%2d/%4d", day, month, year);


    fprintf(questiondata, "%d,%s,%s,%s\n", &numberquestion, question, type, date);

    while (fprintf(questiondata, "%d,%s,%s,%s\n", &numberquestion, question, type, date) < 0){
        printf("เกิดข้อผิดพลาดในการเขียนไฟล์\n");
    }

    printf("เพิ่มข้อมูลคำถามใหม่เรียบร้อย\n");

    
    
    fclose(questiondata);

    pressEnterToContinue();

    do
    {
        printf("------MENU------\n");
        printf("1. แก้ไขคำถาม\n");
        printf("2. เพิ่มคำถามใหม่\n");
        printf("3. กลับเมนูหลัก\n");
        printf("เลือกประเภทคำถาม: ");
        scanf("%d", &questiontypechoice);

            if(questiontypechoice == 1){
                updatequestion();
            }
            if(questiontypechoice == 2){
                addquestion();
            }
            if(questiontypechoice == 3){
                printf("กำลังกลับเมนูหลัก\n");
            }
            else{
                printf("กรุณาเลือก(1-3)\n");
            }
    } while (questiontypechoice != 1 || questiontypechoice != 2 || questiontypechoice != 3);

}


void searchquestion(){
    FILE *questiondata;
    questiondata = fopen("questiondata.csv","r");
    int questionchoice, found = 0 , totalQuestions = 0;
    char type[30], question[200], line[300];
    Question questionList[MAX_Q];

    while (fgets(line, sizeof(line), questiondata)) {

        line[strcspn(line, "\n")] = 0;

        char *token = strtok(line, ",");
        if (token != NULL) {
            strcpy(questionList[totalQuestions].question, token);
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(questionList[totalQuestions].type, token);
            }
            totalQuestions++;
        }
    }

    do 
    {
        found = 0;
        printf("-----------ค้นหา-----------\n");
        printf("1. ค้นหาจากคำถาม\n");
        printf("2. ค้นหาจากประเภทคำถาม\n");
        printf("3. ออกจากเมนูค้นหาคำถาม\n");
        printf("เลือก(1-3): ");
        scanf("%d", &questionchoice);
            if(questionchoice == 1){
                printf("ค้นหาจากคำถาม\n");
                printf("กรอกคำถามที่ต้องการค้นหา: ");
                fgets(question, sizeof(question), stdin);
                question[strcspn(question, "\n")] = 0;

                for (int i = 0; i < totalQuestions; i++) {
                    if (strcmp(questionList[i].question, question) == 0) {
                    printf("เจอคำถาม: %s\n", questionList[i].question);
                    found = 1;
                    break;
                    }
                }

                if (!found) {
                    printf("ไม่พบคำถามที่คุณค้นหา\n");
                }
            }
            if(questionchoice == 2){
                printf("ค้นหาจากประเภทคำถาม\n");
                printf("กรอกประเภทคำถามที่ต้องการค้นหา: ");
                fgets(type, sizeof(type), stdin);
                type[strcspn(type, "\n")] = 0;
                
                for (int i = 0; i < totalQuestions; i++) {
                    if (strcmp(questionList[i].type, type) == 0) {
                        printf("เจอคำถามประเภท %s: %s\n", type, questionList[i].question);
                        found = 1;
                    }
                }

                if (!found) {
                    printf("ไม่พบคำถามในประเภทนี้\n");
                }
            }

            if(questionchoice == 3){
                printf("ออกจากเมนูค้นหาคำถาม\n");
                break;
            }

    } while (questionchoice != 1 && questionchoice != 2);

    printf("ค้นหาจาก %s\n", line);
    
    pressEnterToContinue();
    
    fclose(questiondata);
}

void updatequestion(){
    FILE *questiondata;
    questiondata = fopen("questiondata.csv","r");
    int questiontypechoice , choice;
    char type[30] , question[200], line[300];

    if(questiondata == NULL){
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return;
    }
    do
    {

        printf("---------------แก้ไขข้อมูลคำถาม---------------\n");
        printf("---------------ค้นหาข้อมูลที่จะแก้ไข---------------");
        printf("1. ประเภทคำถาม\n");
        printf("2. คำถาม\n");
        printf("3. กลับเมนูหลัก\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            do {
                printf("-----------ประเภทคำถามที่จะเเก้ไข-----------\n");
                printf("1. คำถามปลายเปิด\n");
                printf("2. คำถามปลายปิด\n");
                printf("3. ออกจากเมนูย่อยนี้\n");
                printf("เลือกประเภทคำถาม: ");
                scanf("%d", &questiontypechoice);

                if (questiontypechoice == 1) {
                    strcpy(type, "คำถามปลายเปิด");
                }
                else if (questiontypechoice == 2) {
                    strcpy(type, "คำถามปลายปิด");
                }
                else if (questiontypechoice == 3) {
                    printf("ออกจากเมนูย่อยแก้คำถาม\n");
                    break; // ออกจาก do-while ที่สอง
                }
                else {
                    printf("กรุณาเลือก 1-3\n");
                }
            } while (questiontypechoice != 3);
            break;

        case 2:
            printf("keyword about question: ");
            fgets(question, sizeof(question), stdin);
            question[strcspn(question, "\n")] = 0;
            break;

        case 3:
            printf("กำลังกลับเมนูหลัก\n");
            break;

        default:
            printf("กรุณาเลือก 1-3\n");
            break;
        }
    } while (choice != 1 && choice != 2);
    
    pressEnterToContinue();

    fclose(questiondata);

}

void deletequestion(){

}