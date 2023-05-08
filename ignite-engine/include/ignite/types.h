#ifndef IGNITE_TYPES_H_
#define IGNITE_TYPES_H_

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

#include "ignite/static_assert.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long i64;

typedef float f32;
typedef double f64;

// NOTE: Ensure size on number types
IGNITE_STATIC_ASSERT((bool)(sizeof(u8) == 1), "Expected `u8` to be 1 byte");
IGNITE_STATIC_ASSERT((bool)(sizeof(u16) == 2), "Expected `u16` to be 2 byte");
IGNITE_STATIC_ASSERT((bool)(sizeof(u32) == 4), "Expected `u32` to be 4 byte");
IGNITE_STATIC_ASSERT((bool)(sizeof(u64) == 8), "Expected `u64` to be 8 byte");

IGNITE_STATIC_ASSERT((bool)(sizeof(i8) == 1), "Expected `i8` to be 1 byte");
IGNITE_STATIC_ASSERT((bool)(sizeof(i16) == 2), "Expected `i16` to be 2 byte");
IGNITE_STATIC_ASSERT((bool)(sizeof(i32) == 4), "Expected `i32` to be 4 byte");
IGNITE_STATIC_ASSERT((bool)(sizeof(i64) == 8), "Expected `i64` to be 8 byte");

IGNITE_STATIC_ASSERT((bool)(sizeof(f32) == 4), "Expected `f32` to be 4 byte");
IGNITE_STATIC_ASSERT((bool)(sizeof(f64) == 8), "Expected `f64` to be 8 byte");

typedef size_t usize;
typedef ssize_t ssize;

IGNITE_STATIC_ASSERT((bool)(sizeof(usize) == 8),
                     "Expected `usize` to be 8 byte");
IGNITE_STATIC_ASSERT((bool)(sizeof(ssize) == 8),
                     "Expected `ssize` to be 8 byte");

typedef unsigned char byte;
typedef const char *c_str;

IGNITE_STATIC_ASSERT((bool)(sizeof(byte) == 1), "Expected `byte` to be 1 byte");

#endif // IGNITE_TYPES_H_
