#include <iostream>
//#include "spdlog/spdlog.h"


#if defined(__linux__) || defined(__APPLE__)
void __attribute__((destructor)) destructor() {
    // 在动态库卸载时执行清理操作
}
#else
#include <windows.h>
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_DETACH) {
        // 在动态库卸载时执行清理操作
    }
    return TRUE;
}
#endif