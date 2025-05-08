#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <thread>
#include <chrono>
#include <string>

using namespace std;

bool IfOpened() {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return false;
    }

    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &processEntry)) {
        do {
            wstring wProcessName(processEntry.szExeFile);
            string processName(wProcessName.begin(), wProcessName.end());
            if (processName == "ExampleProcess1.exe" || processName == "ExampleProcess2.exe") {
                CloseHandle(hSnapshot);
                return true;
            }
        } while (Process32Next(hSnapshot, &processEntry));
    }

    CloseHandle(hSnapshot);
    return false;
}

void WhenOpened() {
    while (true) {
        if (IfOpened()) {
            // Here code
        }
    }
}

int main() {
    WhenOpened();
    return 0;
}