#ifndef SLIDERCOMPONENT_HPP
#define SLIDERCOMPONENT_HPP

#include "WindowComponent.hpp"
#include <imgui.h>
#include <string>
#include <utility>
#include <functional>

namespace Sharingan
{
template<typename TState>
class SliderFloatComponent : public WindowComponent<TState>
{
public:
    using OnChangeCallback = std::function<void(SliderFloatComponent&, float)>;

    SliderFloatComponent() : _min(0.0f), _max(1.0f), _onChangeCallback(nullptr)
    {
    }

    void Render() override
    {
        if (!_valueBinder) return;
        if (this->IsVisible()) {
            float& value = _valueBinder(*const_cast<TState*>(this->_state));
            if (ImGui::SliderFloat(this->GetLabel().c_str(), &value, _min, _max)) {
                if (_onChangeCallback) {
                    _onChangeCallback(*this, value);
                }
            }
        }
    }

    // 设置值路由
    SliderFloatComponent& SetValueRoute(std::function<float&(TState&)> valueBinder) {
        _valueBinder = std::move(valueBinder);
        return *this;
    }

    // 设置范围
    SliderFloatComponent& SetRange(float min, float max) {
        _min = min;
        _max = max;
        return *this;
    }

    // 设置回调函数
    SliderFloatComponent& SetOnChangeCallback(OnChangeCallback callback) {
        _onChangeCallback = std::move(callback);
        return *this;
    }

private:
    float _min, _max;
    OnChangeCallback _onChangeCallback;
    std::function<float&(TState&)> _valueBinder;
};

template<typename TState>
class SliderIntComponent : public WindowComponent<TState>
{
public:
    using OnChangeCallback = std::function<void(SliderIntComponent&, int)>;

    SliderIntComponent() : _min(0), _max(100), _onChangeCallback(nullptr)
    {
    }

    void Render() override
    {
        if (!_valueBinder) return;
        if (this->IsVisible()) {
            int& value = _valueBinder(*const_cast<TState*>(this->_state));
            if (ImGui::SliderInt(this->GetLabel().c_str(), &value, _min, _max)) {
                if (_onChangeCallback) {
                    _onChangeCallback(*this, value);
                }
            }
        }
    }

    // 设置值路由
    SliderIntComponent& SetValueRoute(std::function<int&(TState&)> valueBinder) {
        _valueBinder = std::move(valueBinder);
        return *this;
    }

    // 设置范围
    SliderIntComponent& SetRange(int min, int max) {
        _min = min;
        _max = max;
        return *this;
    }

    // 设置回调函数
    SliderIntComponent& SetOnChangeCallback(OnChangeCallback callback) {
        _onChangeCallback = std::move(callback);
        return *this;
    }

private:
    int _min, _max;
    OnChangeCallback _onChangeCallback;
    std::function<int&(TState&)> _valueBinder;
};

} // namespace Sharingan

#endif // SLIDERCOMPONENT_HPP