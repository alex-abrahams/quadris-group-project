#ifndef PUBLISHER_H
#define PUBLISHER_H
#include <vector>
#include <memory>
template <typename InfoType,typename NotifFromType> class Observer;

template <typename InfoType, typename NotifFromType> class Publisher {
  std::vector<std::shared_ptr<Observer<InfoType, NotifFromType>>> observers;  
  NotifFromType from;

  protected:
    void setNotifFrom(NotifFromType nfType);
  public:
  void attach(std::shared_ptr<Observer<InfoType, NotifFromType>> o);  
  void notifyObservers();
  virtual InfoType getInfo() const = 0;
  NotifFromType getNotifFrom() const;
};

template <typename InfoType, typename NotifFromType>
void Publisher<InfoType, NotifFromType>::attach(std::shared_ptr<Observer<InfoType, NotifFromType>> o) {
  observers.emplace_back(o);
}

#include <iostream> // testing

template <typename InfoType, typename NotifFromType>
void Publisher<InfoType, NotifFromType>::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

template <typename InfoType, typename NotifFromType>
void Publisher<InfoType, NotifFromType>::setNotifFrom(NotifFromType nfType) {
  from = nfType;
}

template <typename InfoType, typename NotifFromType>
NotifFromType Publisher<InfoType, NotifFromType>::getNotifFrom() const {
  return from;
}

#endif
