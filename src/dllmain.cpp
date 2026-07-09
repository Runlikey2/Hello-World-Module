#include <Windows.h>
#include <thread>

constexpr uintptr_t print_offset = 0x46d3410;
using console_print_fn = void(__fastcall*)(void*, const char*);

void init() {
	uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
	auto print = reinterpret_cast<console_print_fn>(base + print_offset);
	print(nullptr, "hello world");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		std::thread(init).detach();
	}
	return TRUE;
}
