#include "Overall.hpp"

#include <SFML/Config.hpp>
#include <SFML/GpuPreference.hpp>

#ifdef SFML_SYSTEM_WINDOWS

#include <windows.h>

#ifdef USE_DISCRETE_GPU

SFML_DEFINE_DISCRETE_GPU_PREFERENCE

#endif // USE_DISCRETE_GPU

extern int main(int argc, char* argv[]);

#ifdef USE_DEFAULT_WINMAIN_ENTRYPOINT
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
	return main(__argc, __argv);
}
#endif // USE_DEFAULT_WINMAIN_ENTRYPOINT

#endif // SFML_SYSTEM_WINDOWS
