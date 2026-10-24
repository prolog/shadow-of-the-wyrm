#pragma once
#ifdef _MSC_VER
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 0
#endif
#include <Windows.h>

LONG sotw_fault_handler(struct _EXCEPTION_POINTERS *  ExInfo);
void write_minidump(struct _EXCEPTION_POINTERS * e);
#endif

void register_unhandled_exception_handler();

