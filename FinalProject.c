#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int openfile(){
    FILE *questiondata;
    questiondata = fopen("questiondata.csv","r");

    if(questiondata == NULL){
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return 1;
    }
    
    printf("---------------ข้อมูล---------------\n");

    char line[256];

    while (fgets(line, sizeof(line), questiondata)) {
        printf("%s", line);
    }

    fclose(questiondata);
    return 0;
}

int addquestion(){
    int id , numberquestion , questiontypechoice , day , month , year;
    char question[200], type[30], date[30], line[300];
    size_t len , lenquestion , lentype , lendate;
    char *token = strtok(date, ",");
    time_t t;
    struct tm *tm_info;

    FILE *questiondata;
    questiondata = fopen("questiondata.csv","r");

    if(questiondata == NULL){
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return 1;
    }

    do
    {
        printf("-----------ประเภทคำถาม-----------\n");
        printf("1. คำถามปลายเปิด\n");
        printf("2. คำถามปลายปิด\n");
        printf("3. ออกจากเมนูเพิ่มคำถาม\n");
        printf("เลือกประเภทคำถาม: ");
        scanf("%d", &questiontypechoice);
        len = strlen(questiontypechoice);
            if(len == 0){
                printf("กรุณาเลือก 1-3\n");
            }
            if(questiontypechoice == 1){
                strcpy(type, "คำถามปลายเปิด");
            }
            if(questiontypechoice == 2){
                strcpy(type, "คำถามปลายปิด");
            }
            if(questiontypechoice == 3){
                printf("ออกจากเมนูเพิ่มคำถาม\n");
                main();
            }
    } while (questiontypechoice != 3);

    fgets(line, sizeof(line), questiondata);
    while(fgets(line, sizeof(line), questiondata) != NULL) {
        if(strstr(line, "type") != NULL){
            return 1;
        }
        token = strtok(line, ",");
        if (token != NULL) {
            numberquestion = atoi(token);
            token = strtok(NULL, ",");
            strcpy(question, token);
            token = strtok(NULL, ",");
            strcpy(type, token);
            token = strtok(NULL, ",");
            strcpy(date, token);
        }
    }
    numberquestion = id + 1;

    fclose(questiondata);

    questiondata = fopen("questiondata.csv","a");

    if(questiondata == NULL){
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return 1;
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
    } while (lenquestion != 0 || lentype != 0);

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

    do
    {
        printf("------MENU------\n");
        printf("1. แก้ไขคำถาม\n");
        printf("2. เพิ่มคำถามใหม่\n");
        printf("3. กลับเมนูหลัก\n");
        printf("เลือกประเภทคำถาม: ");
        scanf("%d", &questiontypechoice);
        len = strlen(questiontypechoice);
            if(len == 0){
                printf("กรุณาเลือก 1-3\n");
            }
            if(questiontypechoice == 1){
                editquestion();
            }
            if(questiontypechoice == 2){
                addquestion();
            }
            if(questiontypechoice == 3){
                printf("กำลังกลับเมนูหลัก\n");
                main();
            }
    } while (questiontypechoice != 3);

    return 0;
}

int editquestion(){

    return 0;
}


int searchquestion(){
    


    return 0;
}

int updatequestion(){

    return 0;
}

int deletequestion(){

    return 0;
}

int main(){
    int choice=0;
    size_t lenchoice;
    do{
        printf("---------------Menu---------------\n");
        printf("1. ReadQuestionfile\n");
        printf("2. AddQuestion\n");
        printf("3. SearchQuestion\n");
        printf("4. UpdateQuestion\n");
        printf("5. Deletequestion\n");
        printf("6. ExitProgram\n");

        printf("choose your choice: ");
        scanf("%d", &choice);

        lenchoice = strlen(choice);
        if(lenchoice == 0){
            printf("กรุณาเลือก 1-6\n");
        }

        if (choice == 1){
            openfile();
        }
        // }else if (choice == 2){
        //     addquestion();
        // }else if (choice == 3){
        //     searchquestion();
        // }else if (choice == 4){
        //     updatequestion();
        // }else if (choice == 5){
        //     deletequestion();
        // }else if (choice == 6){
        //     printf("ExitProgram\n");
        //     exitprogram();
        // }else if (choice < 1 || choice > 6){
        //     printf("Please select again.\n");
        // }
    } while (choice != 6);

    return 0;
}