//===--- TotoCheck.h - clang-tidy -------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_ADRTIDYCHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_ADRTIDYCHECK_H

#include "../ClangTidyCheck.h"

namespace clang {
namespace tidy {
namespace misc {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/misc-toto.html
class AdrTidyCheck : public ClangTidyCheck {
public:
  AdrTidyCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  void registerMatchers_croch(ast_matchers::MatchFinder *Finder); // override;
  void check_croch(const ast_matchers::MatchFinder::MatchResult &Result); // override;

  void registerMatchers_crochets2(ast_matchers::MatchFinder *Finder) ;//override;
  void check_crochets2(const ast_matchers::MatchFinder::MatchResult &Result) ;//override;

  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;

  void registerMatchers_gau(ast_matchers::MatchFinder *Finder) ;//override;
  void check_gau(const ast_matchers::MatchFinder::MatchResult &Result) ;//override;
};

} // namespace misc
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_TOTOCHECK_H
