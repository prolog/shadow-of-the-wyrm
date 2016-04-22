#pragma once
#ifdef _MSC_VER
#include <Windows.h>

LONG sotw_fault_handler(struct _EXCEPTION_POINTERS *  ExInfo);
void write_minidump(struct _EXCEPTION_POINTERS * e);
#endif

void register_unhandled_exception_handler();

