#ifndef CORE_INCLUDESPEROS_H
#define CORE_INCLUDESPEROS_H
//Windows.
#ifdef _WIN32
#include "disp.win32.cpp"
#endif //_WIN32

//Android.
#ifdef __ANDROID__
#error: Your platform isnt supported yet.
#else

//Mac.
#ifdef __APPLE__
#error: Your platform isnt supported yet.
#else

//Any unix-like OS, that must not be a Mac. --Expects X11--
#ifdef __unix__
#include "disp.x11.cpp"
#endif //LINUX or UNIX
#endif //MACOSX
#endif //ANDROID
#endif // CORE_INCLUDESPEROS_H
