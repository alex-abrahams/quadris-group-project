#ifndef _OBSERVER_H_
#define _OBSERVER_H_


template <typename InfoType> class Publisher;
class Cell;

template <typename InfoType> class Observer {
 public:
  virtual void notify(Publisher<InfoType> &whoFrom) = 0; // pass the Publisher that called the notify method
  virtual ~Observer() = default;
};
#endif

