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
  auto my_async(Func &&f, Args&&... args)
  {
    using RetType = invoke_result_t<decay_t<Func>, decay_t<Args>...>;
	packaged_task<RetType(decay_t<Args>...)> pt(forward<Func>(f));
    auto result = pt.get_future();
    thread(std::move(pt), forward<Args>(args)...).detach();
    return result;
  }
}

#endif