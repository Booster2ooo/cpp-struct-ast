# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.9)

project ("StructAnalyzer")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(LLVM CONFIG REQUIRED)   # Brings in LLVM::Support, LLVM::Core, etc. :contentReference[oaicite:2]{index=2}
find_package(Clang CONFIG REQUIRED)  # Brings in Clang::Tooling, Clang::ASTMatchers, ... :contentReference[oaicite:3]{index=3}

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")  # So AddLLVM/Clang macros are visible
include(AddLLVM)                                   # Provides add_clang_executable :contentReference[oaicite:4]{index=4}
                                               # Enables add_clang_executable, etc.


# Include sub-projects.
add_subdirectory ("src")
