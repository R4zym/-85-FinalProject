#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "questionfunction.h"

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
        }else if (choice == 2){
            addquestion();
        }else if (choice == 3){
            searchquestion();
        }else if (choice == 4){
            updatequestion();
        }else if (choice == 5){
            deletequestion();
        }else if (choice == 6){
            printf("ExitProgram\n");
        }else if (choice < 1 || choice > 6){
            printf("Please select (1-6).\n");
        }
    } while (choice != 6);

    return 0;
}