#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    int qid , numberquestion , questiontypechoice , day , month , year;
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
                exit(0);
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

    do // เปลี่ยนเป็น switch case
    {
        printf("------MENU------\n");
        printf("1. แก้ไขคำถาม\n");
        printf("2. เพิ่มคำถามใหม่\n");
        printf("3. กลับเมนูหลัก\n");
        printf("เลือกประเภทคำถาม: ");
        scanf("%d", &questiontypechoice);
        // len = strlen(questiontypechoice);
        //     if(len == 0){
        //         printf("กรุณาเลือก 1-3\n");
        //     }
            // if(questiontypechoice == 1){
            //     updatequestion();
            // }
            if(questiontypechoice == 2){
                addquestion();
            }
            if(questiontypechoice == 3){
                printf("กำลังกลับเมนูหลัก\n");
            }
    } while (questiontypechoice != 1 || questiontypechoice != 2 || questiontypechoice != 3);

}

void searchquestion(){

}

void updatequestion(){

}

void deletequestion(){

}