//=== AsmJS.h - Declare AsmJS target feature support *- C++ -*-------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares Emscripten/AsmJS TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_ASM_JS_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_ASM_JS_H

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
    SizeType = TargetInfo::UnsignedLong;
    PtrDiffType = TargetInfo::SignedLong;
    IntPtrType = TargetInfo::SignedLong;
    SuitableAlign = 128;
    LargeArrayMinWidth = 128;
    LargeArrayAlign = 128;
    SimdDefaultAlign = 128;
    SigAtomicType = SignedLong;
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
  IntType getIntTypeByWidth(unsigned BitWidth,
                            bool IsSigned) const final {
    return BitWidth == 64 ? (IsSigned ? SignedLongLong : UnsignedLongLong)
                          : TargetInfo::getIntTypeByWidth(BitWidth, IsSigned);
  }
  IntType getLeastIntTypeByWidth(unsigned BitWidth,
                                 bool IsSigned) const final {
    return BitWidth == 64
               ? (IsSigned ? SignedLongLong : UnsignedLongLong)
               : TargetInfo::getLeastIntTypeByWidth(BitWidth, IsSigned);
  }
};

// Emscripten target
template <typename Target>
class EmscriptenTargetInfo : public OSTargetInfo<Target> {
protected:
  void getOSDefines(const LangOptions &Opts, const llvm::Triple &Triple,
                    MacroBuilder &Builder) const override {
    // A macro for the platform.
    Builder.defineMacro("__EMSCRIPTEN__");
    // Earlier versions of Emscripten defined this, so we continue to define it
    // for compatibility, for now. Users should ideally prefer __EMSCRIPTEN__.
    Builder.defineMacro("EMSCRIPTEN");
    // A common platform macro.
    if (Opts.POSIXThreads)
      Builder.defineMacro("_REENTRANT");
    // Follow g++ convention and predefine _GNU_SOURCE for C++.
    if (Opts.CPlusPlus)
      Builder.defineMacro("_GNU_SOURCE");

    // Emscripten's software environment and the asm.js runtime aren't really
    // Unix per se, but they're perhaps more Unix-like than what software
    // expects when "unix" is *not* defined.
    DefineStd(Builder, "unix", Opts);
  }

public:
  explicit EmscriptenTargetInfo(const llvm::Triple &Triple, const TargetOptions &Opts)
      : OSTargetInfo<Target>(Triple, Opts) {
    // XXX  set UserLabelPrefix to ""?
    this->MaxAtomicPromoteWidth = this->MaxAtomicInlineWidth = 32;

    // Emscripten uses the Itanium ABI mostly, but it uses ARM-style pointers
    // to member functions so that it can avoid having to align function
    // addresses.
    this->TheCXXABI.set(TargetCXXABI::Emscripten);
  }
  ArrayRef<Builtin::Info> getTargetBuiltins() const override {
    return None;
  }
};
// @LOCALMOD-END Emscripten

} // namespace targets
} // namespace clang
#endif // LLVM_CLANG_LIB_BASIC_TARGETS_ASM_JS_H
