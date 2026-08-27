// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_SUPPORT_STRING_ERROR_H
#define TORUSLANG_SUPPORT_STRING_ERROR_H

#include <llvm/Support/Error.h>

namespace mlir {
namespace toruslang {

/// Internal error class that allows for composing `llvm::Error`s
/// similar to `llvm::createStringError()`, but using stream-like
/// composition with `operator<<`.
///
/// Example:
///
///   llvm::Error foo(int i, size_t s, ...) {
///      ...
///      if(...) {
///        return StreamStringError()
///               << "Some error message with an integer: "
///               << i << " and a size_t: " << s;
///      }
///      ...
///   }
class StreamStringError {
public:
  StreamStringError(const llvm::StringRef &s) : buffer(s.str()), os(buffer){};
  StreamStringError() : buffer(""), os(buffer){};

  template <typename T> StreamStringError &operator<<(const T &v) {
    this->os << v;
    return *this;
  }

  operator llvm::Error() {
    return llvm::make_error<llvm::StringError>(os.str(),
                                               llvm::inconvertibleErrorCode());
  }

  template <typename T> operator llvm::Expected<T>() {
    return this->operator llvm::Error();
  }

protected:
  std::string buffer;
  llvm::raw_string_ostream os;
};

inline StreamStringError &operator<<(StreamStringError &se, llvm::Error &err) {
  se << llvm::toString(std::move(err));
  return se;
}

} // namespace toruslang
} // namespace mlir

#endif
