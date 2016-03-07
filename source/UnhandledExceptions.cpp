#include "UnhandledExceptions.hpp"
#include <iostream>

#ifdef _MSC_VER
#include <windows.h>
#include <dbghelp.h>
#endif

using namespace std;

#ifdef _MSC_VER
LONG sotw_fault_handler(struct _EXCEPTION_POINTERS *  e)
{
  write_minidump(e);

  cout << "Shadow of the Wyrm crashed unexpectedly (sorry!)." << endl << endl;
  cout << "Please email the .dmp file created to jcd748@mail.usask.ca and mention if you're using the Win7 or XP build." << endl << endl;
  return EXCEPTION_EXECUTE_HANDLER;
}

void write_minidump(struct _EXCEPTION_POINTERS* e)
{
  auto hDbgHelp = LoadLibraryA("dbghelp");
  if (hDbgHelp == nullptr)
    return;
  auto pMiniDumpWriteDump = (decltype(&MiniDumpWriteDump))GetProcAddress(hDbgHelp, "MiniDumpWriteDump");
  if (pMiniDumpWriteDump == nullptr)
    return;

  char name[MAX_PATH];
  {
    auto nameEnd = name + GetModuleFileNameA(GetModuleHandleA(0), name, MAX_PATH);
    SYSTEMTIME t;
    GetSystemTime(&t);
    wsprintfA(nameEnd - strlen(".exe"),
      "_%4d%02d%02d_%02d%02d%02d.dmp",
      t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
  }

  auto hFile = CreateFileA(name, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
  if (hFile == INVALID_HANDLE_VALUE)
    return;

  MINIDUMP_EXCEPTION_INFORMATION exceptionInfo;
  exceptionInfo.ThreadId = GetCurrentThreadId();
  exceptionInfo.ExceptionPointers = e;
  exceptionInfo.ClientPointers = FALSE;

  auto dumped = pMiniDumpWriteDump(
    GetCurrentProcess(),
    GetCurrentProcessId(),
    hFile,
    MINIDUMP_TYPE(MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory),
    e ? &exceptionInfo : nullptr,
    nullptr,
    nullptr);

  CloseHandle(hFile);
}
#endif

void register_unhandled_exception_handler()
{
  #ifdef _MSC_VER
  SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)sotw_fault_handler);
  #endif
}