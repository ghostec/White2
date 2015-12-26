#ifndef __MESSAGE_QUEUE__
#define __MESSAGE_QUEUE__

#include <queue>
#include <mutex>
#include <condition_variable>
#include <iostream>

template<typename T>
class MessageQueue {
private:
  std::queue<T> q;
  std::mutex m;
  std::condition_variable c;
public:
  void push(const T _message);
  const T front();
  void pop();
  bool empty();
};

template<typename T>
inline void MessageQueue<T>::push(const T _message)
{
  std::lock_guard<std::mutex> lock(m);
  q.push(_message);
  c.notify_one();
}

template<typename T>
inline const T MessageQueue<T>::front()
{
  std::unique_lock<std::mutex> lock(m);
  while(q.empty())
  {
    c.wait(lock);
  }
  
  T item = q.front();
  return item;
}

template<typename T>
inline void MessageQueue<T>::pop()
{
  std::unique_lock<std::mutex> lock(m);
  while(q.empty())
  {
    c.wait(lock);
  }  
  q.pop();
}

template<typename T>
inline bool MessageQueue<T>::empty()
{
  std::unique_lock<std::mutex> lock(m);
  while(q.empty())
  {
    c.wait(lock);
  }
  bool v = q.empty();
  return v;
}

#endif