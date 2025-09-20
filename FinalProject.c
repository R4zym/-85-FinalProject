#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "questionfunction.h"

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

void showMenu() {
    system(CLEAR); // ล้างหน้าจอทุกครั้ง
    printf("=====================================\n");
    printf("   Interview Question Management\n");
    printf("=====================================\n");
    printf("  [1] Read Question File\n");
    printf("  [2] Add Question\n");
    printf("  [3] Search Question\n");
    printf("  [4] Update Question\n");
    printf("  [5] Delete Question\n");
    printf("  [6] Exit Program\n");
    printf("=====================================\n");
    printf("Enter your choice (1-6): ");
}

int main(){
    int choice = 0;

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    do {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            printf("\n⚠️ Invalid input! Please enter a number.\n");
            while(getchar() != '\n'); // เคลียร์ buffer
            choice = 0; // reset
            continue;
        }

        switch(choice){
            case 1:
                openfile();
                break;
            case 2:
                addquestion();
                printf("\n✅ Question added successfully!\n");
                break;
            case 3:
                searchquestion();
                break;
            case 4:
                updatequestion();
                printf("\n✅ Question updated successfully!\n");
                break;
            case 5:
                deletequestion();
                printf("\n✅ Question deleted successfully!\n");
                break;
            case 6:
                printf("\n👋 Exiting program. Goodbye!\n");
                break;
            default:
                printf("\n⚠️ Please select a number between 1–6.\n");
        }

        if (choice != 6) {
            printf("\nPress Enter to continue...");
            getchar(); // รอ Enter ก่อนกลับไปเมนู
        }

    } while (choice != 6);

    return 0;
}