// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_SUPPORT_LOGGING_H_
#define TORUSLANG_SUPPORT_LOGGING_H_

#include <llvm/Support/raw_ostream.h>

namespace mlir {
namespace toruslang {

/// Returning references to instances of different classes `S` and `T`
/// is prohibited, even if `T` inherits from `S`. The wrapper class
/// `StreamWrap` can be initialized with a pointer to an instance of
/// `S` or any of its subclasses and acts as a proxy transparently
/// forwarding all calls to `S::operator<<`. The class thus hides the
/// dereferencing of the pointer and a reference to it can be used as a
/// replacement for a reference to `S`.
template <class S> class StreamWrap {
public:
  StreamWrap() = delete;
  StreamWrap(S *s) : s(s) {}

  /// Forward all invocations of
  /// `StreamWrap<S>::operator<<` to S::operator<<`.
  template <class T> StreamWrap<S> &operator<<(const T &v) {
    *this->s << v;
    return *this;
  }

private:
  S *s = nullptr;
};

StreamWrap<llvm::raw_ostream> &log_error(void);
StreamWrap<llvm::raw_ostream> &log_verbose(void);
void setupLogging(bool verbose);
bool isVerbose();
} // namespace toruslang
} // namespace mlir

#endif
