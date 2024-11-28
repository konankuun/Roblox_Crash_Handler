#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>

#define PROCESS_NAME "RobloxPlayerBeta.exe"

#define CHECK_DELAY 4000

#define CRASH_FORMAT "Roblox crashed %d times. Restarting...\n"
#define RESTART_FORMAT "Restarting in %d... "
#define PROCESS_CHECK_FORMAT "Processus checking %s...\n"
#define CRASH_COUNT_FORMAT "Roblox encounter %d crash\n"

char idPlace[25];
char rblxUri[50];

int isProcessRunning(const char *processName) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    PROCESSENTRY32 pe32 = { .dwSize = sizeof(PROCESSENTRY32) };
    BOOL found = FALSE;

    if (Process32First(hSnapshot, &pe32)) {
        do {
            if (_stricmp(pe32.szExeFile, processName) == 0) {
                found = TRUE;
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }
    
    CloseHandle(hSnapshot);
    return found;
}

void startRoblox(){
    if(rblxUri[0] == '\0') {
        ShellExecute(NULL, "open", "roblox://", NULL, NULL, SW_SHOWNORMAL);
    } else {
        ShellExecute(NULL, "open", rblxUri, NULL, NULL, SW_SHOWNORMAL);
    }
    printf("Roblox restarted successfuly.\n");
}

int uriChoose() {
    char choice;
    printf("Want to open Roblox with a specific ID place ? (y/n): ");
    scanf(" %c", &choice);
    switch(choice) {
        case 'y':
        case 'Y':
            printf("Enter the ID place : ");
            scanf("%s", idPlace);
            sprintf(rblxUri, "roblox://placeID=%s/", idPlace);
            return 1;
        case 'n':
        case 'N':
            printf("No ID place chosen.\n");
            rblxUri[0] = '\0';
            return 1;
        default:
            printf("Invalid input. Please enter 'y' or 'n'.\n");
            return uriChoose();
    }
}

int askSleep(){
    int sleepTime = 0;
    printf("Specify the delay in second : ");
    scanf("%d", &sleepTime);
    return sleepTime * 1000;
}

int main(){
    int sleepTime = askSleep();
    int crashCount = 0;
    uriChoose();

    system("cls");

    printf(PROCESS_CHECK_FORMAT, PROCESS_NAME);
    printf(CRASH_COUNT_FORMAT, crashCount);
    while(1){
        if(!isProcessRunning(PROCESS_NAME)){
            system("cls");
            crashCount++;
            for(int i = sleepTime / 1000; i > 0; i--) {
                printf(CRASH_FORMAT, crashCount);
                printf(RESTART_FORMAT, i);
                Sleep(1000);
                system("cls");
            }
            printf("\n");
            startRoblox();
            system("cls");
            printf(PROCESS_CHECK_FORMAT, PROCESS_NAME);
            printf(CRASH_COUNT_FORMAT, crashCount);
        }
    }
    return 0;
}