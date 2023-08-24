//===--- AdrTidyCheck.cpp - clang-tidy ------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//


#include "AdrTidyCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"

#include <iostream>
#include <fstream>


using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

/**
 * () --> [] on ArrOfXXX
 */
void AdrTidyCheck::registerMatchers_croch(MatchFinder *Finder) {
//  let ta recordType(hasDeclaration(namedDecl(hasName("TRUSTArray"))))
//  let arrT hasType( hasUnqualifiedDesugaredType(ta))
//
//  let callE hasDescendant( callExpr   (arrT) )
//  let declE hasDescendant( declRefExpr(arrT) )
//  let membE hasDescendant( memberExpr(arrT) )
//
//  m cxxOperatorCallExpr( argumentCountIs(2), hasOverloadedOperatorName("()"), anyOf(callE, declE, membE)  )


  // All classes rooting to TRUSTArray<T>:
  auto ta = recordType(hasDeclaration(namedDecl(anyOf(hasName("TRUSTArray"), hasName("TRUSTArrayFT")))));
  auto arrT = hasType( hasUnqualifiedDesugaredType(ta));

  // all calls like "toto()(28)" where return type for "toto()" is ArrOfXXX
  auto callE = hasDescendant( callExpr   (arrT) );
  // all direct usage of an ArrOfXXX like: "tab_(23)"
  auto declE = hasDescendant( declRefExpr(arrT) );
  // all invocations on class members
  auto membE = hasDescendant( memberExpr(arrT) );

  // all (overloaded) operator calls to ArrOfXXX (includes '+', '-' etc...), plus the following constraints:
  //  - name matches
  //  - number of args matches
  auto opCall = cxxOperatorCallExpr( argumentCountIs(2), hasOverloadedOperatorName("()"), anyOf(callE, declE, membE)  );

  // Another way to do it:
  // the declaration of the overloaded "()" operator, with a single argument, in ArrOfXXX classes:
  // Matching the declaration of the method allows to also catch the DoubleVect using the inherited operator [] - not what want now:
//  auto declM = cxxMethodDecl( parameterCountIs(1),
//                              hasOverloadedOperatorName("()" ),
//                              ofClass(names));
//  auto callerPar = callExpr(callee(declM));

  Finder->addMatcher(
      opCall.bind("roundBrackToSquareBrack")
      , this);
}

void AdrTidyCheck::check_croch(const MatchFinder::MatchResult &Result) {
  if (const auto MatchedDecl = Result.Nodes.getNodeAs<CallExpr>("roundBrackToSquareBrack"))
    {
      // Finding opening parenth '('. This is not so obvious:
      //   1. the begining of the last token of arg0 which is 'this' actually...
      SourceLocation locA0B = MatchedDecl->getArg(0)->getEndLoc();
      const SourceManager & SM = *Result.SourceManager;

      //   2, are we inside a macro ?
      bool mac = SM.isMacroBodyExpansion(locA0B);
      bool mac1 = SM.isMacroArgExpansion(locA0B);
      std::cout << "mac is " << mac << " " << mac1 << std::endl;

      //   2. Token after the caller, i.e. the left parenth '('
      auto tok = Lexer::findNextToken(locA0B, SM, Result.Context->getLangOpts());
      SourceLocation locLP = tok->getLocation();
      auto rB = SourceRange(locLP, locLP);

      // Finding closing parenth ')'
      SourceLocation locE = MatchedDecl->getEndLoc();
      auto rE = SourceRange(locE, locE);

      mac1 ? diag(locA0B, "loc A0B MAC") : diag(locA0B, "loc A0B");

      diag(locLP, "opening round bracket should be turned into square brackets")
            << FixItHint::CreateReplacement(rB, "[");
      diag(locE, "closing round bracket should be turned into square brackets")
            << FixItHint::CreateReplacement(rE, "]");
    }
}

/**
 * [] --> () on XXXTab or XXXTrav. See comments above.
 */
void AdrTidyCheck::registerMatchers_crochets2(MatchFinder *Finder) {
  auto names = anyOf(hasName("DoubleTab"), hasName("DoubleTrav"), hasName("IntTab"), hasName("IntTrav"));
  auto arrT = hasType( cxxRecordDecl(names) );

  auto callE = hasDescendant( callExpr   (arrT) );
  auto declE = hasDescendant( declRefExpr(arrT) );

  auto opCall = cxxOperatorCallExpr( argumentCountIs(2),
                                     hasOverloadedOperatorName("[]"),
                                     anyOf(callE, declE)  );

  Finder->addMatcher(
      opCall.bind("squareBrackToRoundBrack")
      , this);
}

void AdrTidyCheck::check_crochets2(const MatchFinder::MatchResult &Result) {
  if (const auto MatchedDecl = Result.Nodes.getNodeAs<CallExpr>("squareBrackToRoundBrack"))
    {
      SourceLocation locBB = MatchedDecl->getCallee()->getBeginLoc();
      SourceLocation locE = MatchedDecl->getEndLoc();

      auto r1 = SourceRange(locBB, locBB);
      auto r2 = SourceRange(locE, locE);
      diag(locBB, "opening square bracket should be turned into round brackets")
                  << FixItHint::CreateReplacement(r1, "(");
      diag(locE, "closing square bracket should be turned into round brackets")
            << FixItHint::CreateReplacement(r2, ")");
    }
}

void AdrTidyCheck::registerMatchers(MatchFinder *Finder) {
  auto typRefTo = anyOf(hasType( asString("const int &")),
                        hasType( asString("const long &")),
                        hasType( asString("const double &")),
                        hasType( asString("const float &")),
                        hasType( asString("const unsigned int &")));

  auto constDR = varDecl( typRefTo ,
//                          unless(parmVarDecl()),
                          unless(hasAncestor( cxxForRangeStmt()))
                        );

  Finder->addMatcher(constDR.bind("removeBuiltinRef") , this);
}


void AdrTidyCheck::check(const MatchFinder::MatchResult &Result) {
  if (const auto MatchedDecl = Result.Nodes.getNodeAs<VarDecl>("removeBuiltinRef"))
    {
      SourceLocation locE = MatchedDecl->getTypeSpecEndLoc();
      SourceRange r2(locE, locE);
      diag(locE, "'const <builtin> &' should be turned into 'const <builtin>'")
            << FixItHint::CreateRemoval(r2);
    }
//  if (const auto MatchedDecl = Result.Nodes.getNodeAs<VarDecl>("forAuto"))
//    {
//      SourceLocation locE = MatchedDecl->getBeginLoc();
//      SourceRange r2(locE, locE);
//      diag(locE, "for auto around here")
//            << FixItHint::CreateRemoval(r2);
//    }
}

//let y hasDescendant(declRefExpr( to ( enumConstantDecl( hasAnyName("KALLOC") ) )))
//let b binaryOperator(hasAnyOperatorName("=="), hasEitherOperand( y ) )
//m ifStmt(hasThen(compoundStmt().bind("thenCmpStmt")), hasCondition(b) )


void AdrTidyCheck::registerMatchers_gau(MatchFinder *Finder) {
  auto kalloUse = hasDescendant(declRefExpr( to ( enumConstantDecl( hasAnyName("KALLOC") ) )));
  auto binaryOp = binaryOperator(hasAnyOperatorName("=="), hasEitherOperand( kalloUse ) );
  auto zeMatcher = ifStmt(hasThen(compoundStmt().bind("thenCmpStmt")), hasCondition( binaryOp ) );

  Finder->addMatcher( zeMatcher , this);
}

std::string stmt2str(const Stmt *d, const SourceManager * sm) {
    SourceLocation b(d->getBeginLoc()), _e(d->getEndLoc());
    SourceLocation e(Lexer::getLocForEndOfToken(_e, 0, *sm, LangOptions()));
    return std::string(sm->getCharacterData(b),
        sm->getCharacterData(e)-sm->getCharacterData(b));
}

void AdrTidyCheck::check_gau(const MatchFinder::MatchResult &Result) {

  if (const Stmt* MatchedDecl = Result.Nodes.getNodeAs<Stmt>("thenCmpStmt"))
    {
      const SourceManager * sm = Result.SourceManager;

      SourceLocation locB = MatchedDecl->getBeginLoc();
      SourceLocation locE = MatchedDecl->getEndLoc();
      SourceRange r2(locB, locE);
      diag(locE, "Degager comp stmt")
            << FixItHint::CreateReplacement(r2, "XXX_ADRIEN_XXX \n ");

      // Ecriture dans un fichier
      std::ofstream myfile;
      myfile.open ("HDONOKH_alloc.cxx");
      myfile << stmt2str(MatchedDecl, sm);
      myfile << std::endl;
      myfile.close();
    }
}

} // namespace misc
} // namespace tidy
} // namespace clang
