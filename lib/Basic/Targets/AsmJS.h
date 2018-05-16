//=== WebAssembly.h - Declare WebAssembly target feature support *- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares WebAssembly TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_WEBASSEMBLY_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_WEBASSEMBLY_H

#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Support/Compiler.h"

namespace clang {
namespace targets {

// @LOCALMOD-START Emscripten
class LLVM_LIBRARY_VISIBILITY AsmJSTargetInfo : public TargetInfo {
public:
  explicit AsmJSTargetInfo(const llvm::Triple &T, const TargetOptions &Opts) : TargetInfo(T) {
    BigEndian = false;
    NoAsmVariants = true;
    LongAlign = LongWidth = 32;
    PointerAlign = PointerWidth = 32;
    IntMaxType = Int64Type = TargetInfo::SignedLongLong;
    DoubleAlign = 64;
    LongDoubleWidth = LongDoubleAlign = 64;
    SizeType = TargetInfo::UnsignedInt;
    PtrDiffType = TargetInfo::SignedInt;
    IntPtrType = TargetInfo::SignedInt;
    RegParmMax = 0; // Disallow regparm

    // Set the native integer widths set to just i32, since that's currently the
    // only integer type we can do arithmetic on without masking or splitting.
    //
    // Set the required alignment for 128-bit vectors to just 4 bytes, based on
    // the direction suggested here:
    //   https://bugzilla.mozilla.org/show_bug.cgi?id=904913#c21
    // We can still set the preferred alignment to 16 bytes though.
    //
    // Set the natural stack alignment to 16 bytes to accomodate 128-bit aligned
    // vectors.
    resetDataLayout("e-p:32:32-i64:64-v128:32:128-n32-S128");
  }
  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override {
    defineCPUMacros(Builder, "asmjs", /*Tuning=*/false);
  }
  BuiltinVaListKind getBuiltinVaListKind() const override {
    // Reuse PNaCl's va_list lowering.
    return TargetInfo::PNaClABIBuiltinVaList;
  }
  ArrayRef<const char *> getGCCRegNames() const {
    return None;
  }
  ArrayRef<TargetInfo::GCCRegAlias> getGCCRegAliases() const {
    return None;
  }
  bool validateAsmConstraint(const char *&Name,
                             TargetInfo::ConstraintInfo &Info) const override {
    return false;
  }
  const char *getClobbers() const override { return ""; }
  bool isCLZForZeroUndef() const override {
    // Today we do clz in software, so we just do the right thing. With ES6,
    // we'll get Math.clz32, which is to be defined to do the right thing:
    // http://esdiscuss.org/topic/rename-number-prototype-clz-to-math-clz#content-36
    return false;
  }
};
// @LOCALMOD-END Emscripten

} // namespace targets
} // namespace clang
#endif // LLVM_CLANG_LIB_BASIC_TARGETS_WEBASSEMBLY_H
