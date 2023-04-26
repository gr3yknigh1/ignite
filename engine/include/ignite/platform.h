#ifndef IGNITE_PLATFORM_H_
#define IGNITE_PLATFORM_H_

#ifdef _WIN32
#define IGNITE_PLATFORM_WINDOWS
#ifdef _WIN64
#define IGNITE_PLATFORM_WINDOWS_X64
#else
#define IGNITE_PLATFORM_WINDOWS_X32
#endif // _WIN64
#elif defined(__APPLE__) || defined(__MACH__)
#error "Premium devices is not supported"
#elif defined(__ANDROID__)
#error "Android is not supported"
#elif defined(__linux__)
#define IGNITE_PLATFORM_LINUX
#else
#error "Unknown platform"
#endif // _WIN32

#endif // IGNITE_PLATFORM_H_
