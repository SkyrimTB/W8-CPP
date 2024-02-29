#ifndef MY_PROMISE_H
#define MY_PROMISE_H

#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <exception>
#include <stdexcept>
#include <optional>
#include <variant>

using std::shared_ptr;
using std::make_shared;
using std::unique_lock;
using std::mutex;
using std::condition_variable;
using std::exception_ptr;
using std::rethrow_exception;
using std::runtime_error;
using std::optional;
using std::variant;
using std::holds_alternative;

namespace mpcs {

template<class T>
class MyPromise;

// Define a variant type to hold either a value or an exception
template<class T>
using ValueOrException = variant<optional<T>, exception_ptr>;

template<class T>
struct SharedState {
  ValueOrException<T> data{optional<T>{}}; // Initially empty optional
  mutex mtx;
  condition_variable cv;
};

template<typename T>
class MyFuture {
public:
  MyFuture(MyFuture const &) = delete;
  MyFuture(MyFuture &&) = default;
  T get() {
    unique_lock lck{sharedState->mtx};
    sharedState->cv.wait(lck, [&] { return sharedState->data.index() != 0; });
    if (holds_alternative<optional<T>>(sharedState->data)) {
      return **std::get_if<optional<T>>(&sharedState->data); // Dereference twice to get T
    } else {
      rethrow_exception(*std::get_if<exception_ptr>(&sharedState->data));
    }
  }
private:
  friend class MyPromise<T>;
  explicit MyFuture(shared_ptr<SharedState<T>> sharedState) 
    : sharedState(std::move(sharedState)) {}
  shared_ptr<SharedState<T>> sharedState;
};

template<typename T>
class MyPromise {
public:
  MyPromise() : sharedState{make_shared<SharedState<T>>()} {}

  void set_value(const T &value) {
    unique_lock lck(sharedState->mtx);
    sharedState->data = optional<T>{value};
    sharedState->cv.notify_one();
  }

  void set_exception(exception_ptr exc) {
    unique_lock lck(sharedState->mtx);
    sharedState->data = exc;
    sharedState->cv.notify_one();
  }

  MyFuture<T> get_future() {
    return MyFuture<T>(sharedState);
  }
private:
  shared_ptr<SharedState<T>> sharedState;
};

} // namespace mpcs

#endif // MY_PROMISE_H
