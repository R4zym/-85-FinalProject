#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
    int id , numberquestion;
    char question[200], type[30], date[30];
    FILE *questiondata;
    questiondata = fopen("questiondata.csv","r");
    fscanf(questiondata, "%d %s %s %s", &id , question , type , date);
    numberquestion = Id + 1;

    fclose(questiondata);

    FILE *questiondata;
    questiondata = fopen("questiondata.csv","a");
    if(questiondata == NULL){
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return 1;
    }
    printf("---------------เพิ่มข้อมูลคำถามใหม่---------------\n");

    fscanf(stdin, "%c");
    printf("กรอกคำถาม: ");
    scanf("%s", question);

    printf("กรอกประเภทคำถาม: ");
    scanf("%s", type);

    printf("กรอกวันที่เดือนปี(ตัวอย่าง: xx(เดือน),xx(วัน),xxxx(ปีคศ.)): ");
    scanf("%s", &date);

    fprintf(questiondata, "%d,%s,%s,%s\n", numberquestion, question, type, date);
    while (fprintf(questiondata, "%d,%s,%s,%s\n", numberquestion, question, type, date) < 0){
        printf("เกิดข้อผิดพลาดในการเขียนไฟล์\n");
    }
    printf("เพิ่มข้อมูลคำถามใหม่เรียบร้อย\n");
    fclose(questiondata);

    return 0;
}



int main(){
    int choice=0;
    

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
        // }else if (choice < 1 || choice > 6){
        //     printf("Please select again.\n");
        // }
    } while (choice != 6);

    return 0;
}