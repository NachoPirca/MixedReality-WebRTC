#include <windows.h>
#include "pch.h"
#include <cstdlib>
#include <crtdbg.h>


BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ulReasonForCall,
                      LPVOID lpReserved) {
  if (ulReasonForCall == DLL_PROCESS_ATTACH) {
    SetErrorMode(SEM_NOGPFAULTERRORBOX | SEM_FAILCRITICALERRORS);
    _set_error_mode(_OUT_TO_STDERR);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
  }
  return TRUE;
}
