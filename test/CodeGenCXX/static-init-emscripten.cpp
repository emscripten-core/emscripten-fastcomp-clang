// RUN: %clang_cc1 -emit-llvm -triple=asmjs-unknown-emscripten -o - %s | FileCheck %s

int f();

// Test that Emscripten uses the Itanium/x86 ABI in which the static
// variable's guard variable is tested via "load i8 and compare with
// zero" rather than the ARM ABI which uses "load i32 and test the
// bottom bit".
void g() {
  static int a = f();
}
// CHECK: load atomic i8* bitcast (i64* @_ZGVZ1gvE1a to i8*) acquire
// CHECK-NEXT: %guard.uninitialized = icmp eq i8 %0, 0
// CHECK-NEXT: br i1 %guard.uninitialized, label %init.check, label %init.end
