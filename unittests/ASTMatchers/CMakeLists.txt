set(LLVM_LINK_COMPONENTS
  Support
  )

add_clang_unittest(ASTMatchersTests
  ASTMatchersTest.cpp)

# XXX Emscripten: Hotfix for bug https://llvm.org/bugs/show_bug.cgi?id=26089
if (MSVC)
  set_source_files_properties(ASTMatchersTest.cpp PROPERTIES COMPILE_FLAGS /bigobj)
endif()

target_link_libraries(ASTMatchersTests
  clangAST
  clangASTMatchers
  clangBasic
  clangFrontend
  clangTooling
  )

add_subdirectory(Dynamic)
