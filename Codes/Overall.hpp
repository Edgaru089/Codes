#pragma once

#pragma warning(disable: 4244) // Inline conventions, possible loss of data
#pragma warning(disable: 4018) // Variable comparation signed/unsigned mismatch 

#define LOCAL
#define NOMINMAX

#define wxUSE_ANY 1

///////////////////////// Define currently tested code file /////////////////////////
#define CODE_20180804_LUOGU3807


// Inform the Nvidia/AMD driver that this SFML application could
// benefit from using the more powerful discrete GPU
//#define USE_DISCRETE_GPU

// Windows specific: we define the WinMain entry point,
// so that developers can use the standard main function
// even in a Win32 Application project, and thus keep a
// portable code
#define USE_DEFAULT_WINMAIN_ENTRYPOINT
