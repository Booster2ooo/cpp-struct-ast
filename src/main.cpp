#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang;
using namespace clang::tooling;
using namespace clang::ast_matchers;
using namespace llvm;

static DeclarationMatcher StructMatcher =
    cxxRecordDecl(hasName("Core_DataCenter_Metadata_World_SubAreasRoot_o"))
        .bind("targetStruct");

class StructPrinter : public MatchFinder::MatchCallback {
public:
  void run(const MatchFinder::MatchResult &Result) override {
    if (const CXXRecordDecl *RD =
            Result.Nodes.getNodeAs<CXXRecordDecl>("targetStruct")) {
      // Direct (non‑virtual) bases
      for (const auto &Base : RD->bases())
        outs() << "Base: " << Base.getType().getAsString() << "\n";

      // Data members
      for (const auto *Field : RD->fields())
        outs() << "Field: " << Field->getNameAsString()
               << " : " << Field->getType().getAsString() << "\n";
    }
  }
};

static cl::OptionCategory ToolCategory("struct-analyzer options");

int main(int argc, const char **argv) {
  CommonOptionsParser OptionsParser(argc, argv, ToolCategory);
  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());

  StructPrinter Printer;
  MatchFinder Finder;
  Finder.addMatcher(StructMatcher, &Printer);

  return Tool.run(newFrontendActionFactory(&Finder).get());
}
