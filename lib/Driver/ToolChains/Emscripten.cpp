//===--- Emscripten.cpp - Emscripten ToolChain Implementation ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Emscripten.h"
#include "CommonArgs.h"
#include "InputInfo.h"
#include "clang/Driver/Compilation.h"
#include "llvm/Option/ArgList.h"

using namespace clang::driver;
using namespace clang::driver::toolchains;
using namespace clang::driver::tools;
using namespace clang;
using namespace llvm::opt;

/// Emscripten Toolchain
EmscriptenToolChain::EmscriptenToolChain(const Driver &D,
                                         const llvm::Triple &Triple,
                                         const ArgList &Args)
  : ToolChain(D, Triple, Args) {}

