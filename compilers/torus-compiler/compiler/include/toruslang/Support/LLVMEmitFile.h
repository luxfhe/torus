// Part of the Concrete Compiler Project, under the BSD3 License with Zama
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_SUPPORT_LLVMEMITFILE
#define TORUSLANG_SUPPORT_LLVMEMITFILE

#include <llvm/ADT/StringRef.h>

namespace mlir {
namespace toruslang {

llvm::Error emitObject(llvm::Module &module, std::string objectPath);

llvm::Error callCmd(std::string cmd);

llvm::Error emitLibrary(std::vector<std::string> objectsPath,
                        std::string libraryPath, std::string linker,
                        std::optional<std::vector<std::string>> extraArgs = {});

} // namespace toruslang
} // namespace mlir

#endif
