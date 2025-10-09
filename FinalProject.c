#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

void openfile();
void addquestion();
int searchquestion();
void updatequestion();
void deletequestion();
void UnitTestQuestionFunction();
void EndToEndTestQuestionFunction();

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
    printf("  [6] Unit Tests\n");
    printf("  [7] End to End Tests\n");
    printf("  [8] Exit Program\n");
    printf("=====================================\n");
    printf("Enter your choice (1-8): ");
}

int main(){
    int choice = 0;

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    do {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            printf("\n⚠️ Invalid input! Please enter a number.\n");
            while(getchar() != '\n');
            choice = 0;
            continue;
        }

        switch(choice){
            case 1:
                openfile();
                getchar();
                break;
            case 2:
                addquestion();
                printf("\n✅ Question added successfully!\n");
                printf("\nPress Enter to continue...");
                getchar();
                break;
            case 3:
                searchquestion();
                printf("\nPress Enter to continue...");
                getchar();
                break;
            case 4:
                updatequestion();
                printf("\n✅ Question updated successfully!\n");
                printf("\nPress Enter to continue...");
                getchar();
                break;
            case 5:
                deletequestion();
                printf("\n✅ Question deleted successfully!\n");
                printf("\nPress Enter to continue...");
                getchar();
                break;
            case 6:
                UnitTestQuestionFunction();
                printf("\n✅ Unit tests completed!\n");
                printf("\nPress Enter to continue...");
                getchar();
                break;
            case 7:
                EndToEndTestQuestionFunction();
                printf("\n✅ End to End tests completed!\n");
                printf("\nPress Enter to continue...");
                getchar();
                break;
            case 8:
                printf("\n👋 Exiting program. Goodbye!\n");
                break;
            default:
                printf("\n⚠️ Please select a number between 1–8.\n");
        }

        if (choice != 8) {
            printf("\nPress Enter to continue...");
            getchar(); // รอ Enter ก่อนกลับไปเมนู
        }

    } while (choice != 8);

    return 0;
}