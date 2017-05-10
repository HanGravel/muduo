// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_CURRENTTHREAD_H
#define MUDUO_BASE_CURRENTTHREAD_H

#include <stdint.h>

namespace muduo
{
namespace CurrentThread
{
  /*
  * __thread 代表每个线程各自保有而非共享的变量。 gcc内置的关键字
  */
  // internal
  extern __thread int t_cachedTid;
  extern __thread char t_tidString[32];
  extern __thread int t_tidStringLength;
  extern __thread const char* t_threadName;
  void cacheTid();

  /*
  * inline关键字相当于于预处理器中宏定义函数，使运行时更快。多用于简单函数。
  * __builtin_expect(expr,int) 是gcc内置函数，作用是分支优化预测优化。
  * expr大部分情况是false时，__builtin_expect(expr,0)在运行时效率更高
  * expr大部分情况是true时，__builtin_expect(expr,0)在运行时效率更高
  */
  
  inline int tid()
  {
    if (__builtin_expect(t_cachedTid == 0, 0))
    {
      cacheTid();
    }
    return t_cachedTid;
  }

  inline const char* tidString() // for logging
  {
    return t_tidString;
  }

  inline int tidStringLength() // for logging
  {
    return t_tidStringLength;
  }

  inline const char* name()
  {
    return t_threadName;
  }

  bool isMainThread();

  void sleepUsec(int64_t usec);
}
}

#endif
