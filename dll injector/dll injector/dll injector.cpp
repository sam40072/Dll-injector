// dll injector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <sstream>
#include "GetProcessId.h"


int main()
{
    std::string path;
    std::string procname;
    std::cout << "path: ";
    std::getline(std::cin, path); //used std::getline because std::cin got rid of blank spaces
    const char* dllpath = path.c_str();;
    DWORD procID = 0;
    while (!procID)
    {
        std::cout << "process name (same way it is in task manager): ";
        std::getline(std::cin, procname);
        procID = get_procId(procname.c_str());
        if (!procID)
        {
            std::cout << "process not found! Dont forget .exe if needed " << std::endl;
        }
    }
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procID);

    if (hProc != INVALID_HANDLE_VALUE)
    {
        void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        WriteProcessMemory(hProc, loc, dllpath, strlen(dllpath) + 1, 0);

        HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);

        if (hProc)
        {
            CloseHandle(hProc);
        }
        return 0;
        std::cout << "injected successfully" << std::endl;
        exit(0);
    }
}
