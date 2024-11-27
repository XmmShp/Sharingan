#ifndef WINDOWCOMPONENT_HPP
#define WINDOWCOMPONENT_HPP

#include <functional>
#include <string>
#include <utility>
#include <memory>
#include <type_traits>

namespace Sharingan
{
using Callback = std::function<void()>;

// 用于提供动态值的模板类
template<typename T>
class ValueProvider {
public:
    // 支持直接值
    ValueProvider(const T& value) : _provider([value](const void*) { return value; }) {}
    
    // 支持基于状态的lambda
    template<typename TState>
    ValueProvider(std::function<T(const TState&)> stateFunc) 
        : _provider([stateFunc](const void* state) { 
              return stateFunc(*static_cast<const TState*>(state)); 
          }) 
    {}

    // 获取值
    T operator()(const void* state = nullptr) const {
        return _provider(state);
    }

private:
    std::function<T(const void*)> _provider;
};

// 特化StringProvider
using StringProvider = ValueProvider<std::string>;

template<typename TState>
class WindowComponent
{
public:
    virtual ~WindowComponent() = default;
    virtual void Render() = 0;
    
    void SetState(const TState* state) { _state = state; }
    const TState* GetState() const { return _state; }

protected:
    const TState* _state = nullptr;
};

} // namespace Sharingan

#endif // WINDOWCOMPONENT_HPP
