#ifndef UTILITY_H
#define UTILITY_H
namespace utility{
  //from https://stackoverflow.com/questions/8645058/getting-argument-count-of-a-function-pointer
  template<class R, class... Args>
  constexpr unsigned arity(std::function<R(Args...)> const&){
    return sizeof...(Args);
  }
}
#endif
