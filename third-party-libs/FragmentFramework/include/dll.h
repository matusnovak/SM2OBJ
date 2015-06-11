#ifndef FFW_DLL
#define FFW_DLL

#ifdef _MSC_VER
#ifdef FFW_EXPORTS
#define FFW_API __declspec(dllexport)
#else
#define FFW_API __declspec(dllimport)
#endif
#endif

#ifdef __MINGW32__
#define FFW_API
#endif

#endif
