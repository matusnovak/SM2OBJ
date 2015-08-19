#ifndef FFW_CONFIG
#define FFW_CONFIG

#if __cplusplus < 201103L
//  #error This library needs at least a C++11 compliant compiler
#endif

#define UNICODE 1

#ifdef FFW_EXPORTS
#define FFW_API __declspec(dllexport)
#else
#define FFW_API __declspec(dllimport)
#endif

#ifdef _MSC_VER
#define _USING_MSVC
#pragma warning( disable: 4251 )
#endif
#ifdef __MINGW32__
#define _USING_MINGW
#endif

#endif
