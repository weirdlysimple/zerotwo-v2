#pragma once
#include <wchar.h>
#include <sys/prx.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/ppu_thread.h>
#include <string.h>
#include <sys/sys_time.h>
#include <sys/time_util.h>
#include <stdarg.h>
#include <assert.h>
#include <sys/process.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/return_code.h>
#include <sys/prx.h>
#include <stddef.h>
#include <math.h>
#include <stdarg.h>
#include <cellstatus.h>
#include <typeinfo>
//#include <vector>
#include <pthread.h>
#include <locale.h>
#include <cell/error.h>
#include <sys/paths.h>
#include <time.h>
#include <cell/sysmodule.h>
#include <sys/ss_get_open_psid.h>
/*int console_write(const char * s)
{
uint32_t len;
system_call_4(403, 0, (uint64_t)s, std::strlen(s), (uint64_t)&len);
return_to_user_prog(int);
}*/
void sleep(usecond_t time)
{
	sys_timer_usleep(time * 1000);
}
namespace mainFuncs
{
	//void* HenReadFixed(uint64_t ea, uint32_t size)
	//{
	//	void* data;
	//	//system_call_4(904, (uint64_t)sys_process_getpid(), ea, size, (uint64_t)data);
	//	system_call_6(8, 0x7777, 0x31, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)size, (uint64_t)data);
	//	return data;
	//}

	int writeProcMem(uint64_t address, const void* data, size_t size, bool ps3mapi)
	{
		if (ps3mapi) {
			system_call_6(8, 0x7777, 0x32, (uint64_t)sys_process_getpid(), (uint64_t)address, (uint64_t)data, (uint64_t)size);
			return_to_user_prog(int);
		}
		else
		{
			system_call_4(905, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
			return_to_user_prog(int32_t);
		}
	}

	int readProcMem(uint64_t address, void* data, size_t size, bool ps3mapi)
	{
		if (ps3mapi) {
			system_call_6(8, 0x7777, 0x31, (uint64_t)sys_process_getpid(), (uint64_t)address, (uint64_t)data, (uint64_t)size);
			return_to_user_prog(int32_t);
		}
		else
		{
			system_call_4(904, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
			return_to_user_prog(int32_t);
		}
	}



	void hookFunctionStart(uint32_t functionStartAddress, uint32_t newFunction, uint32_t functionStub, bool ps3mapi)
	{

		uint32_t normalFunctionStub[8], hookFunctionStub[4];
		readProcMem(functionStartAddress, normalFunctionStub, 0x10, ps3mapi);
		normalFunctionStub[4] = 0x3D600000 + ((functionStartAddress + 0x10 >> 16) & 0xFFFF);
		normalFunctionStub[5] = 0x616B0000 + (functionStartAddress + 0x10 & 0xFFFF);
		normalFunctionStub[6] = 0x7D6903A6;
		normalFunctionStub[7] = 0x4E800420;
		writeProcMem(functionStub, normalFunctionStub, 0x20, ps3mapi);
		hookFunctionStub[0] = 0x3D600000 + ((newFunction >> 16) & 0xFFFF);
		hookFunctionStub[1] = 0x616B0000 + (newFunction & 0xFFFF);
		hookFunctionStub[2] = 0x7D6903A6;
		hookFunctionStub[3] = 0x4E800420;
		writeProcMem(functionStartAddress, hookFunctionStub, 0x10, ps3mapi);

	}
}

void PatchInJump(int Address, int Destination) {
	int FuncBytes[4];
	Destination = *(int*)Destination;
	FuncBytes[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF);
	if (Destination & 0x8000) FuncBytes[0] += 1;
	FuncBytes[1] = 0x396B0000 + (Destination & 0xFFFF);
	FuncBytes[2] = 0x7D6903A6;
	FuncBytes[3] = 0x4E800420;
	for (int i = 0; i < 4; i++) {
		*(int*)(Address + (i * 4)) = FuncBytes[i];

	}
}
char byteArray[100];
char* ReadBytes(int address, int length)
{
	for (int i = 0; i < length; i++)
	{
		byteArray[i] = *(char*)(address + (i));
	}
	return byteArray;
}
void WriteBytes(int address, char* input, int length)
{
	for (int i = 0; i < length; i++)
	{
		*(char*)(address + (i)) = input[i];
	}
}
void WriteString(int address, char* string)
{
	int FreeMem = 0x1D00000;
	int strlength = std::strlen(string);
	char* strpointer = *(char**)FreeMem = string;
	char* StrBytes = ReadBytes(*(int*)FreeMem, strlength);
	WriteBytes(address, StrBytes, strlength);
}