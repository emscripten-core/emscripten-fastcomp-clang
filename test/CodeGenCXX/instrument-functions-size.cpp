// RUN: %clang_cc1 -S -emit-llvm -o - %s -finstrument-functions -finstrument-functions-size 2 | FileCheck %s

// CHECK: define i32 @_Z5test1i
int test1(int x) {
// CHECK-NOT: __cyg_profile_func_enter
// CHECK-NOT: __cyg_profile_func_exit
// CHECK: ret i32
  return x;
}

// CHECK: define i32 @_Z5test2i
int test2(int) __attribute__((no_instrument_function));
int test2(int x) {
  if(x) {test1(x);}
// CHECK-NOT: __cyg_profile_func_enter
// CHECK-NOT: __cyg_profile_func_exit
// CHECK: ret i32
  return x;
}

// CHECK: define i32 @_Z5test3i
int test3(int x) {
  if(x) {test1(x);}
// CHECK: __cyg_profile_func_enter
// CHECK: __cyg_profile_func_exit
// CHECK: ret i32
  return x;
}
