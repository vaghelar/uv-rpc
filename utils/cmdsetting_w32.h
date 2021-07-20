#pragma once
#include <stdio.h>
#include <stdlib.h>

#if  defined( WIN32) || defined(_WIN64)
#include <windows.h>
#include <TlHelp32.h>

int get_thread_amount()
{
	int i = 0;
	//char Buff[9];
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	int processid = GetCurrentProcessId();
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot() failed. error code:%d.\n", GetLastError());
		return 0;
	}
	BOOL bMore = ::Process32First(hProcessSnap, &pe32);

	//HANDLE hProcess;

	while (bMore)
	{
		if (pe32.th32ProcessID == processid)
		{
			return pe32.cntThreads;
		}

		bMore = Process32Next(hProcessSnap, &pe32);
		i++;
	}

	return 0;
}
#endif

// 这个函数很重要有些时候会造成阻塞，整个程序停止运行
void setModeCmd()
{
#ifdef WIN32
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);

	mode &= ~ENABLE_QUICK_EDIT_MODE; // 移除快速编辑模式
	mode &= ~ENABLE_INSERT_MODE;     // 移除插入模式
	mode &= ~ENABLE_MOUSE_INPUT;

	SetConsoleMode(hStdin, mode);
#else
	//std::cout << "";
#endif // WIN32
}



