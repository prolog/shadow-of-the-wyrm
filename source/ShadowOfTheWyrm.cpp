#include <stdio.h>

#include <iostream>
#include <xercesc/util/PlatformUtils.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/filesystem.hpp>

#include "common.hpp"
#include "global_prototypes.hpp"

#include "CursesKeyboardController.hpp"

#include "CursesDisplay.hpp"
#include "DisplayConstants.hpp"
#include "DisplayFactory.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "Metadata.hpp"
#include "ShadowOfTheWyrmEngine.hpp"
#include "Settings.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"
#include "XMLDataStructures.hpp"
#include "XMLFileReader.hpp"

#ifdef UNIT_TESTS
#include "gtest/gtest.h"
#endif

#ifdef _MSC_VER
#include <tchar.h>
#include <windows.h>
#include <dbghelp.h>

LONG sotw_fault_handler(struct _EXCEPTION_POINTERS *  ExInfo);
void write_minidump(struct _EXCEPTION_POINTERS * e);

LONG sotw_fault_handler(struct _EXCEPTION_POINTERS *  e)
{
  write_minidump(e);

  std::cout << "Shadow of the Wyrm crashed unexpectedly (sorry!)." << std::endl << std::endl;
  std::cout << "Please email the .dmp file created to jcd748@mail.usask.ca and mention if you're using the Win7 or XP build." << std::endl << std::endl;
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

/*{
  std::string fault;

  switch (ExInfo->ExceptionRecord->ExceptionCode)
  {
    case EXCEPTION_ACCESS_VIOLATION: fault = "ACCESS VIOLATION"; break;
    case EXCEPTION_DATATYPE_MISALIGNMENT: fault = "DATATYPE MISALIGNMENT"; break;
    case EXCEPTION_BREAKPOINT: fault = "BREAKPOINT"; break;
    case EXCEPTION_SINGLE_STEP: fault = "SINGLE STEP"; break;
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: fault = "ARRAY BOUNDS EXCEEDED"; break;
    case EXCEPTION_FLT_DENORMAL_OPERAND: fault = "FLT DENORMAL OPERAND"; break;
    case EXCEPTION_FLT_DIVIDE_BY_ZERO: fault = "FLT DIVIDE BY ZERO"; break;
    case EXCEPTION_FLT_INEXACT_RESULT: fault = "FLT INEXACT RESULT"; break;
    case EXCEPTION_FLT_INVALID_OPERATION: fault = "FLT INVALID OPERATION"; break;
    case EXCEPTION_FLT_OVERFLOW: fault = "FLT OVERFLOW"; break;
    case EXCEPTION_FLT_STACK_CHECK: fault = "FLT STACK CHECK"; break;
    case EXCEPTION_FLT_UNDERFLOW: fault = "FLT UNDERFLOW"; break;
    case EXCEPTION_INT_DIVIDE_BY_ZERO: fault = "INT DIVIDE BY ZERO"; break;
    case EXCEPTION_INT_OVERFLOW: fault = "INT OVERFLOW"; break;
    case EXCEPTION_PRIV_INSTRUCTION: fault = "PRIV INSTRUCTION"; break;
    case EXCEPTION_IN_PAGE_ERROR: fault = "IN PAGE ERROR"; break;
    case EXCEPTION_ILLEGAL_INSTRUCTION: fault = "ILLEGAL INSTRUCTION"; break;
    case EXCEPTION_NONCONTINUABLE_EXCEPTION: fault = "NONCONTINUABLE EXCEPTION"; break;
    case EXCEPTION_STACK_OVERFLOW: fault = "STACK OVERFLOW"; break;
    case EXCEPTION_INVALID_DISPOSITION: fault = "INVALID DISPOSITION"; break;
    case EXCEPTION_GUARD_PAGE: fault = "GUARD PAGE"; break;
    default: fault = "(unknown)";           break;
  }
  
  Metadata md;
  std::ofstream crash_log;
  crash_log.open("crash_sotw.log");

  if (crash_log.good())
  {
    crash_log << "Crash log for " << md.get_full_game_version_details() << std::endl << std::endl;
    crash_log << "Exception at address: 0x" << std::hex << ExInfo->ExceptionRecord->ExceptionAddress << std::dec << std::endl;
    crash_log << "Exception type: " << fault << std::endl;
  }

  std::cout << "Shadow of the Wyrm crashed unexpectedly." << std::endl << std::endl;
  std::cout << "Please email crash_sotw.log to jcd748@mail.usask.ca and mention if you're using the Win7 or XP build." << std::endl;

  return EXCEPTION_EXECUTE_HANDLER;
} */
#endif

using namespace std;
using namespace xercesc;

void print_title();
bool check_write_permissions();
int parse_command_line_arguments(int argc, char* argv[]);

#ifdef UNIT_TESTS
int run_unit_tests();

int run_unit_tests()
{
  int test_result = RUN_ALL_TESTS();
  return test_result;
}
#endif

void print_title()
{
  Metadata meta;

  std::string version = meta.get_version();
	std::cout << "Shadow of the Wyrm " << version << std::endl;

}

int parse_command_line_arguments(int argc, char* argv[])
{
  for (int x = 0; x < argc; x++)
  {
    string current_arg = argv[x];

    if (current_arg == "/test")
    {
      #ifdef UNIT_TESTS
      ::testing::InitGoogleTest(&argc, argv);
      int test_result = run_unit_tests();
      return test_result;
      #else
      cout << "Unit tests are not available in release mode." << endl;
      #endif
    }
    else
    {
      cout << "Unknown argument: " << current_arg << endl;
    }
  }

  return 0;
}

#ifdef _MSC_VER
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int argc, char* argv[])
#endif
{
  // JCD FIXME refactor
  #ifdef _MSC_VER
  SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)sotw_fault_handler);
  #endif

  Log& log = Log::instance();

  try
  {
    log.set_log_level(LoggingLevel::LOG_ERROR);
    log.trace("main - testing");

    print_title();

    if (argc > 1)
    {
      return parse_command_line_arguments(argc, argv);
    }
    else
    {
      Settings settings(true);

      // Set the default display and controller.  This is hard-coded, but c
      // JCD FIXME: Refactor.  This id should eventually be in a .rc
      // type file, so that each individual person can set their own
      // settings...
      string display_id = settings.get_setting("display");
      pair<DisplayPtr, ControllerPtr> display_details = DisplayFactory::create_display_details(display_id);
      DisplayPtr display = display_details.first;
      ControllerPtr controller = display_details.second;

      bool write_ok = check_write_permissions();

      if (!write_ok)
      {
        cout << "No write permissions in current directory!" << endl;
        throw "error";
      }

      if (display && display->create())
      {
        ShadowOfTheWyrmEngine engine;

        // set the default display into the engine
        engine.set_display(display);
        engine.set_controller(controller);
        engine.start(settings);

        display->tear_down();
      }
      else
      {
        log.error("main - Could not create display!");
        cerr << "Could not create display - exiting.";
        throw "error";
      }
    }
  }
  catch(...)
  {
    log.error("main - Unable to run Shadow of the Wyrm!");
    return 1;
  }

  return 0;
}

bool check_write_permissions()
{
  bool can_write = true;

  string fname = "test";
  ofstream test_file;
  test_file.open(fname, ios::out | ios::binary);

  if (!test_file.good())
  {
    can_write = false;
  }
  else
  {
    test_file.close();
    std::remove(fname.c_str());
  }
  
  return can_write;
}