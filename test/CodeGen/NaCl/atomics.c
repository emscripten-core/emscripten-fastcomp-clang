// Test frontend handling of synchronization builtins which NaCl handles
// differently.
// Modified from test/CodeGen/Atomics.c
// RUN: %clang_cc1 -triple le32-unknown-nacl -emit-llvm %s -o - | FileCheck %s

// CHECK: define void @test_sync_synchronize()
// CHECK-NEXT: entry:
void test_sync_synchronize (void)
{
  __sync_synchronize ();
  // CHECK-NEXT: call void asm sideeffect "", "~{memory}"()
  // CHECK-NEXT: fence seq_cst
  // CHECK-NEXT: call void asm sideeffect "", "~{memory}"()

  // CHECK-NEXT: ret void
}

// CHECK: define void @test_asm_memory_1()
// CHECK-NEXT: entry:
void test_asm_memory_1 (void)
{
  asm ("":::"memory");
  // CHECK-NEXT: call void asm sideeffect "", "~{memory}"()
  // CHECK-NEXT: fence seq_cst
  // CHECK-NEXT: call void asm sideeffect "", "~{memory}"()

  // CHECK-NEXT: ret void
}

// CHECK: define void @test_asm_memory_2()
// CHECK-NEXT: entry:
void test_asm_memory_2 (void)
{
  asm volatile ("":::"memory");
  // CHECK-NEXT: call void asm sideeffect "", "~{memory}"()
  // CHECK-NEXT: fence seq_cst
  // CHECK-NEXT: call void asm sideeffect "", "~{memory}"()

  // CHECK-NEXT: ret void
}

// CHECK: define void @test_asm_memory_3()
// CHECK-NEXT: entry:
void test_asm_memory_3 (void)
{
  __asm__ ("":::"memory");
  // CHECK-NEXT: call void asm sideeffect "", "~{memory}"()
  // CHECK-NEXT: fence seq_cst
  // CHECK-NEXT: call void asm sideeffect "", "~{memory}"()

  // CHECK-NEXT: ret void
}

// CHECK: define void @test_asm_memory_4()
// CHECK-NEXT: entry:
void test_asm_memory_4 (void)
{
  __asm__ __volatile__ ("":::"memory");
  // CHECK-NEXT: call void asm sideeffect "", "~{memory}"()
  // CHECK-NEXT: fence seq_cst
  // CHECK-NEXT: call void asm sideeffect "", "~{memory}"()

  // CHECK-NEXT: ret void
}
