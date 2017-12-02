#ifndef _OBSERVER_H_
#define _OBSERVER_H_

template <typename InfoType, typename NotifFromType> class Publisher;

template <typename InfoType, typename NotifFromType> class Observer {
 public:
  virtual void notify(Publisher<InfoType, NotifFromType> &whoFrom) = 0; // pass the Publisher that called the notify method
  virtual ~Observer() = default;
};
#endif

