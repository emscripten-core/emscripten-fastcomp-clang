// RUN: %clang_cc1 -triple asmjs-unknown-emscripten -std=c++11 -verify %s
// expected-no-diagnostics

#include <stddef.h>
#include <stdarg.h>

template <typename T, typename U> struct is_same { static const bool value = false; };
template <typename T> struct is_same<T, T> { static const bool value = true; };

static_assert(is_same<__SIZE_TYPE__, unsigned long>::value, "__SIZE_TYPE__ should be unsigned long");

static_assert(alignof(char) == 1, "alignof char should be 1");

static_assert(sizeof(short) == 2, "sizeof short should be 2");
static_assert(alignof(short) == 2, "alignof short should be 2");

static_assert(sizeof(int) == 4, "sizeof int should be 4");
static_assert(alignof(int) == 4, "alignof int should be 4");

static_assert(sizeof(long) == 4, "sizeof long should be 4");
static_assert(alignof(long) == 4, "alignof long should be 4");

static_assert(sizeof(long long) == 8, "sizeof long long should be 8");
static_assert(alignof(long long) == 8, "alignof long long should be 8");

static_assert(sizeof(void*) == 4, "sizeof void * should be 4");
static_assert(alignof(void*) == 4, "alignof void * should be 4");

static_assert(sizeof(float) == 4, "sizeof float should be 4");
static_assert(alignof(float) == 4, "alignof float should be 4");

static_assert(sizeof(double) == 8, "sizeof double should be 8");
static_assert(alignof(double) == 8, "alignof double should be 8");

static_assert(sizeof(long double) == 8, "sizeof long double should be 8");
static_assert(alignof(long double) == 8, "alignof long double should be 8");

static_assert(sizeof(va_list) == 16, "sizeof va_list should be 16");
static_assert(alignof(va_list) == 4, "alignof va_list should be 4");

static_assert(sizeof(size_t) == 4, "sizeof size_t should be 4");
static_assert(alignof(size_t) == 4, "alignof size_t should be 4");
