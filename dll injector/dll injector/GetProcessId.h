
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <sstream>
#pragma once

DWORD get_procId(const char* procName)
{
    DWORD procID = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(snapshot, &procEntry))
        {
            while (Process32Next(snapshot, &procEntry))
            {
                if (!_stricmp(procEntry.szExeFile, procName))
                {
                    procID = procEntry.th32ProcessID;
                    break;
                }
            }
        }
        CloseHandle(snapshot);
        return procID;
    }
}