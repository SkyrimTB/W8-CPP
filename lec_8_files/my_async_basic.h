#ifndef MY_ASYNC_H
#define MY_ASYNC_H
#include<future>
#include<type_traits>
#include<thread>
#include<utility>
#include<cmath>
using std::forward;
using std::invoke_result_t;
using std::decay_t;
using std::move;
using std::packaged_task;
using std::thread;

namespace mpcs {
  template<typename Func, typename ...Args>
  auto my_async(Func f, Args ... args)
  {
    using RetType = decltype(f(args...));

    packaged_task<RetType(Args...)> pt(f);
    auto result = pt.get_future();
    thread(std::move(pt), args...).detach();
    return result;
  }
}

#endif