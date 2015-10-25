#ifndef FFW_CONFIG
#define FFW_CONFIG

/*
#if __cplusplus < 201103L
#error This library needs at least a C++11 compliant compiler
#endif
*/

// Use multi byte strings, needed by windows.h
#define UNICODE 1

// FragmentFramework export
#ifdef FFW_EXPORTS
#define FFW_API __declspec(dllexport)
#else
#define FFW_API __declspec(dllimport)
#endif

// If using Visual Studio
#ifdef _MSC_VER
#define _USING_MSVC
#pragma warning( disable: 4251 )
// Use STD threads 
#define FFW_USE_STD_THREADS 1
#endif

// If using MinGW
#ifdef __MINGW32__
#define _USING_MINGW
#endif

#endif
