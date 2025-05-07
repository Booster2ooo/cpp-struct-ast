# CMakeList.txt : CMake project for StructAnalyzer, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (StructAnalyzer "main.cpp") # "example_parser.hpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET StructAnalyzer PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(StructAnalyzer
  PRIVATE
    clangTooling
    clangASTMatchers
    # Optionally add other components:
    clangBasic
    clangFrontend
    LLVM
)

# Ensure the include directories and compile definitions are set
# based on LLVM’s configured variables.
target_include_directories(StructAnalyzer
  PRIVATE
    ${LLVM_INCLUDE_DIRS}                                        # Include LLVM headers :contentReference[oaicite:9]{index=9}
)
target_compile_definitions(StructAnalyzer
  PRIVATE
    ${LLVM_DEFINITIONS}                                         # E.g. _GLIBCXX_USE_CXX11_ABI, etc. :contentReference[oaicite:10]{index=10}
)