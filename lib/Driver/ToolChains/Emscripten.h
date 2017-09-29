//===--- Emscripten.h - Emscripten ToolChain Implementation -----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_DRIVER_TOOLCHAINS_EMSCRIPTEN_H
#define LLVM_CLANG_LIB_DRIVER_TOOLCHAINS_EMSCRIPTEN_H

#include "InputInfo.h"
#include "clang/Driver/ToolChain.h"

namespace clang {
namespace driver {
namespace toolchains {

// @LOCALMOD-START Emscripten
/// A toolchain for the Emscripten C/C++ to JS compiler.
class LLVM_LIBRARY_VISIBILITY EmscriptenToolChain : public ToolChain {
public:
  EmscriptenToolChain(const Driver &D, const llvm::Triple &Triple,
                      const llvm::opt::ArgList &Args);
  ~EmscriptenToolChain() override {}

  bool IsMathErrnoDefault() const override { return false; }
  bool IsObjCNonFragileABIDefault() const override { return true; }
  bool isPICDefault() const override { return false; }
  bool isPIEDefault() const override { return false; }
  bool isPICDefaultForced() const override { return false; }
};
// @LOCALMOD-END Emscripten

} // end namespace toolchains
} // end namespace driver
} // end namespace clang

#endif // LLVM_CLANG_LIB_DRIVER_TOOLCHAINS_AVR_H
