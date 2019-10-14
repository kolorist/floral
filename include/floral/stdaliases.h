#ifndef __FLORAL_STD_ALIASES_H__
#define __FLORAL_STD_ALIASES_H__

// according to the C++11 Standard
// for Win32, popular Unix-like systems (Linux, Mac OS X)
// ref: http://en.cppreference.com/w/cpp/language/types

// integer
typedef char									c8;
typedef signed char                             s8;
typedef unsigned char                           u8;

typedef signed short int                        s16;
typedef unsigned short int						u16;

typedef signed int								s32;
typedef unsigned int                            u32;

typedef signed long long int                    s64;
typedef unsigned long long int                  u64;

// floating point number
typedef float                                   f32;
typedef double                                  f64;

// size type
typedef u32										size32;
typedef u32										usize32;
typedef s32										ssize32;
typedef u64										size64;
typedef u64										usize64;
typedef s64										ssize64;
// index type
typedef u32										uidx32;
typedef s32										sidx32;
typedef u64										uidx64;
typedef s64										sidx64;
#if defined(PLATFORM_WINDOWS)
// MSVC 64-bit compiler will defined both _WIN32 and _WIN64
#	if defined(_WIN32) && defined(_WIN64)
typedef size64									size;
typedef usize64									usize;
typedef ssize64									ssize;
typedef uidx64									uidx;		// unsigned index type
typedef sidx64									sidx;		// signed index type
typedef size64									aptr;		// pointer type for arithmetic
#	elif defined(_WIN32)
typedef size32									size;
typedef usize32									usize;
typedef ssize32									ssize;
typedef uidx32									uidx;
typedef sidx32									sidx;
typedef size32									aptr;
#	else
// TODO: not supported
#	endif
#elif defined(PLATFORM_POSIX)
#	if defined(POSIX64)
typedef size64									size;
typedef usize64									usize;
typedef ssize64									ssize;
typedef uidx64									uidx;		// unsigned index type
typedef sidx64									sidx;		// signed index type
typedef size64									aptr;		// pointer type for arithmetic
#	elif defined(POSIX32)
typedef size32									size;
typedef usize32									usize;
typedef ssize32									ssize;
typedef uidx32									uidx;
typedef sidx32									sidx;
typedef size32									aptr;
#	else
// TODO: not supported
#	endif
#else
// TODO: not supported
#endif

// c-string
typedef char*                                   cstr;
typedef const char*                             const_cstr;

// normal pointer
typedef u8*										p8;
typedef u16*									p16;
typedef u32*									p32;
typedef u64*									p64;

// void pointer
typedef void*                                   voidptr;

#endif // __FLORAL_STD_ALIASES_H__
