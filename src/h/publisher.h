#ifndef PUBLISHER_H
#define PUBLISHER_H
#include <vector>
#include <memory>

template <typename InfoType> class Observer;

template <typename InfoType> class Publisher {
  std::vector<std::shared_ptr<Observer<InfoType>>> observers;
 public:
  void attach(std::shared_ptr<Observer<InfoType>> o);  
  void notifyObservers();
  virtual InfoType getInfo() const = 0;
};

template <typename InfoType>
void Publisher<InfoType>::attach(std::shared_ptr<Observer<InfoType>> o) {
  observers.emplace_back(o);
}

template <typename InfoType>
void Publisher<InfoType>::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

#endif

