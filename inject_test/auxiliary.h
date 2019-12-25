#include <stdio.h>
#include <Windows.h>
#include <tlhelp32.h>
/*
 * definitions for auxiliary functions
 */
DWORD findPidByName(wchar_t * pname);
DWORD getThreadID(DWORD pid);
BOOL SetSePrivilege();
DWORD demoCreateRemoteThreadW(PCWSTR pszLibFile, DWORD dwProcessId);