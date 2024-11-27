#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>

#define PROCESS_NAME "RobloxPlayerBeta.exe" // Program name here

#define CHECK_DELAY 4000

#define ROBLOX_URI NULL

int isProcessRunning(const char *precessName){
    int found = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if(Process32First(hSnapshot, &pe32)){
        do{
            if(_stricmp(pe32.szExeFile, precessName) == 0){
                found = 1;
                break;
            }
        }while(Process32Next(hSnapshot, &pe32));
    }
    CloseHandle(hSnapshot);
    return found;
}

void startRoblox(){
    ShellExecute(NULL, "open", ROBLOX_URI, NULL, NULL, SW_SHOWNORMAL); // Replace ROBLOX_URI with NULL if you don't want a roblox place ID.
    printf("✅ Roblox restarted successfuly.\n");
}

int uriChoose(){
    char choice;
    printf("Want to open Roblox with a specific URI? (y/n): ");
    scanf(" %c", &choice);
    if(choice == 'y'){
        char uri[100];
        printf("Enter the URI: ");
        scanf("%s", ROBLOX_URI);
        return 1;
    }else if(choice == 'n'){
        printf("No URI chosen.\n");
        return 1;
    }
}

int main(){
    uriChoose();
    int crashCount = 0;
    printf("🔎 Processus checking %s...\n", PROCESS_NAME);
    printf("Roblox encounter %d crash", crashCount);
    while(1){
        if(!isProcessRunning(PROCESS_NAME)){
            printf("⚠️ Roblox crashed %d times. Restarting...", crashCount);
            Sleep(6000);
            startRoblox();
        }
    }
    return 0;
}