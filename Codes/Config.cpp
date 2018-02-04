#include "Overall.hpp"

#include <SFML/Config.hpp>

#ifdef SFML_SYSTEM_WINDOWS

#include <windows.h>

#ifdef USE_DISCRETE_GPU
extern "C"
{
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif // USE_DISCRETE_GPU

extern int main(int argc, char* argv[]);

#ifdef USE_DEFAULT_WINMAIN_ENTRYPOINT
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
	return main(__argc, __argv);
}
#endif // USE_DEFAULT_WINMAIN_ENTRYPOINT

#endif // SFML_SYSTEM_WINDOWS
