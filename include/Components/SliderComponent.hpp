#ifndef SLIDERCOMPONENT_HPP
#define SLIDERCOMPONENT_HPP

#include "WindowComponent.hpp"
#include <imgui.h>
#include <string>
#include <functional>
#include <algorithm>
#include <utility>

namespace Sharingan
{

template<typename TState>
class SliderFloatComponent : public WindowComponent<TState>
{
public:
    SliderFloatComponent() : _label(""), _min(0.0f), _max(1.0f), _value(0.0f), _format("%.3f"), _onChangeCallback(nullptr), _visible(true)
    {
    }

    explicit SliderFloatComponent(StringProvider label, float min = 0.0f, float max = 1.0f,
                                std::function<void(float)> onChangeCallback = nullptr)
        : _label(std::move(label))
        , _min(min)
        , _max(max)
        , _value(0.0f)
        , _format("%.3f")
        , _onChangeCallback(std::move(onChangeCallback))
        , _visible(true)
    {
    }

    void Render() override
    {
        if (_visible(this->_state)) {
            if (ImGui::SliderFloat(_label(this->_state).c_str(), &_value, _min, _max, _format.c_str())) {
                if (_onChangeCallback) {
                    _onChangeCallback(_value);
                }
            }
        }
    }

    // 设置标签
    SliderFloatComponent& SetLabel(const std::string& label) {
        _label = StringProvider(label);
        return *this;
    }

    SliderFloatComponent& SetLabel(std::function<std::string(const TState&)> stateFunc) {
        _label = StringProvider(stateFunc);
        return *this;
    }

    // 设置值
    SliderFloatComponent& SetValue(float value) {
        _value = std::clamp(value, _min, _max);
        return *this;
    }

    // 设置范围
    SliderFloatComponent& SetRange(float min, float max) {
        _min = min;
        _max = max;
        _value = std::clamp(_value, _min, _max);
        return *this;
    }

    // 设置格式
    SliderFloatComponent& SetFormat(const std::string& format) {
        _format = format;
        return *this;
    }

    // 设置回调函数
    SliderFloatComponent& SetOnChangeCallback(std::function<void(float)> callback) {
        _onChangeCallback = std::move(callback);
        return *this;
    }

    // 设置可见性
    SliderFloatComponent& SetVisible(std::function<bool(const TState&)> stateFunc) {
        _visible = ValueProvider<bool>(stateFunc);
        return *this;
    }

    // 获取当前值
    float GetValue() const { return _value; }

private:
    StringProvider _label;
    float _value{0.0f};
    float _min{0.0f};
    float _max{1.0f};
    std::string _format{"%.3f"};
    std::function<void(float)> _onChangeCallback;
    ValueProvider<bool> _visible{true};
};

template<typename TState>
class SliderIntComponent : public WindowComponent<TState>
{
public:
    SliderIntComponent() : _label(""), _min(0), _max(100), _value(0), _format("%d"), _onChangeCallback(nullptr), _visible(true)
    {
    }

    explicit SliderIntComponent(StringProvider label, int min = 0, int max = 100,
                              std::function<void(int)> onChangeCallback = nullptr)
        : _label(std::move(label))
        , _min(min)
        , _max(max)
        , _value(0)
        , _format("%d")
        , _onChangeCallback(std::move(onChangeCallback))
        , _visible(true)
    {
    }

    void Render() override
    {
        if (_visible(this->_state)) {
            if (ImGui::SliderInt(_label(this->_state).c_str(), &_value, _min, _max, _format.c_str())) {
                if (_onChangeCallback) {
                    _onChangeCallback(_value);
                }
            }
        }
    }

    // 设置标签
    SliderIntComponent& SetLabel(const std::string& label) {
        _label = StringProvider(label);
        return *this;
    }

    SliderIntComponent& SetLabel(std::function<std::string(const TState&)> stateFunc) {
        _label = StringProvider(stateFunc);
        return *this;
    }

    // 设置值
    SliderIntComponent& SetValue(int value) {
        _value = std::clamp(value, _min, _max);
        return *this;
    }

    // 设置范围
    SliderIntComponent& SetRange(int min, int max) {
        _min = min;
        _max = max;
        _value = std::clamp(_value, _min, _max);
        return *this;
    }

    // 设置格式
    SliderIntComponent& SetFormat(const std::string& format) {
        _format = format;
        return *this;
    }

    // 设置回调函数
    SliderIntComponent& SetOnChangeCallback(std::function<void(int)> callback) {
        _onChangeCallback = std::move(callback);
        return *this;
    }

    // 设置可见性
    SliderIntComponent& SetVisible(std::function<bool(const TState&)> stateFunc) {
        _visible = ValueProvider<bool>(stateFunc);
        return *this;
    }

    // 获取当前值
    int GetValue() const { return _value; }

private:
    StringProvider _label;
    int _value{0};
    int _min{0};
    int _max{100};
    std::string _format{"%d"};
    std::function<void(int)> _onChangeCallback;
    ValueProvider<bool> _visible{true};
};

} // namespace Sharingan

#endif // SLIDERCOMPONENT_HPP