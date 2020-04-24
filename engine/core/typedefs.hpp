#ifndef TYPEDEFS_H
#define TYPEDEFS_H


// Should always inline no matter what.
#ifndef _ALWAYS_INLINE_
#if defined(__GNUC__)
#define _ALWAYS_INLINE_ __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
#define _ALWAYS_INLINE_ __forceinline
#else
#define _ALWAYS_INLINE_ inline
#endif
#endif


// Should always inline, except in debug builds because it makes debugging harder.
#ifndef _FORCE_INLINE_
#ifdef DISABLE_FORCED_INLINE
#define _FORCE_INLINE_ inline
#else
#define _FORCE_INLINE_ _ALWAYS_INLINE_
#endif
#endif


// 8 bits integer types
typedef signed   char int8;
typedef unsigned char uint8;

// 16 bits integer types
typedef signed   short int16;
typedef unsigned short uint16;

// 32 bits integer types
typedef signed   int int32;
typedef unsigned int uint32;

// 64 bits integer types
#if defined(_MSC_VER)
    typedef signed   __int64 int64;
    typedef unsigned __int64 uint64;
#else
    typedef signed   long long int64;
    typedef unsigned long long uint64;
#endif




#endif