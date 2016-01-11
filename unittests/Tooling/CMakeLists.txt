set(LLVM_LINK_COMPONENTS
  ${LLVM_TARGETS_TO_BUILD}
  Support
  )

add_clang_unittest(ToolingTests
  CommentHandlerTest.cpp
  CompilationDatabaseTest.cpp
  LookupTest.cpp
  ToolingTest.cpp
  RecursiveASTVisitorTest.cpp
  RecursiveASTVisitorTestCallVisitor.cpp
  RecursiveASTVisitorTestDeclVisitor.cpp
  RecursiveASTVisitorTestExprVisitor.cpp
  RecursiveASTVisitorTestTypeLocVisitor.cpp
  RefactoringTest.cpp
  RewriterTest.cpp
  RefactoringCallbacksTest.cpp
  ReplacementsYamlTest.cpp
  )

# XXX Emscripten: Hotfix for bug https://llvm.org/bugs/show_bug.cgi?id=26089
if (MSVC)
  set_source_files_properties(RecursiveASTVisitorTestExprVisitor.cpp PROPERTIES COMPILE_FLAGS /bigobj)
endif()

target_link_libraries(ToolingTests
  clangAST
  clangASTMatchers
  clangBasic
  clangFrontend
  clangLex
  clangRewrite
  clangTooling
  clangToolingCore
  )
