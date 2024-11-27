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
    WindowComponent() : _label(""), _visible(true) {}
    virtual ~WindowComponent() = default;
    virtual void Render() = 0;
    
    void SetState(const TState* state) { _state = state; }
    const TState* GetState() const { return _state; }

    // 设置标签
    WindowComponent& SetLabel(const std::string& label) {
        _label = StringProvider(label);
        return *this;
    }

    WindowComponent& SetLabel(std::function<std::string(const TState&)> stateFunc) {
        _label = StringProvider(stateFunc);
        return *this;
    }

    // 设置可见性

    WindowComponent& SetVisible(std::function<bool(const TState&)> stateFunc) {
        _visible = ValueProvider<bool>(stateFunc);
        return *this;
    }

protected:
    const TState* _state = nullptr;
    StringProvider _label;
    ValueProvider<bool> _visible;

    bool IsVisible() const {
        return _visible(this->_state);
    }

    std::string GetLabel() const {
        return _label(this->_state);
    }
};

} // namespace Sharingan

#endif // WINDOWCOMPONENT_HPP
