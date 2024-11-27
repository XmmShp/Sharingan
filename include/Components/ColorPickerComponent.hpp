#ifndef COLORPICKERCOMPONENT_HPP
#define COLORPICKERCOMPONENT_HPP

#include "WindowComponent.hpp"
#include <imgui.h>
#include <array>
#include <string>
#include <utility>
#include <functional>

namespace Sharingan
{
template<typename TState>
class ColorPickerComponent : public WindowComponent<TState>
{
public:
    ColorPickerComponent() : _label(""), _color{1.0f, 1.0f, 1.0f, 1.0f}, _onChangeCallback(nullptr), _visible(true)
    {
    }

    explicit ColorPickerComponent(StringProvider label, 
                                std::function<void(const std::array<float, 4>&)> onChangeCallback = nullptr)
        : _label(std::move(label))
        , _onChangeCallback(std::move(onChangeCallback))
    {
    }

    void Render() override
    {
        if (_visible(this->_state)) {
            if (ImGui::ColorPicker4(_label(this->_state).c_str(), _color.data(), 
                                  ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreview)) {
                if (_onChangeCallback) {
                    _onChangeCallback(_color);
                }
            }
        }
    }

    // 设置标签
    ColorPickerComponent& SetLabel(const std::string& label) {
        _label = StringProvider(label);
        return *this;
    }

    ColorPickerComponent& SetLabel(std::function<std::string(const TState&)> stateFunc) {
        _label = StringProvider(stateFunc);
        return *this;
    }

    // 设置颜色 (RGBA, 每个分量范围0-1)
    ColorPickerComponent& SetColor(const std::array<float, 4>& color) {
        _color = color;
        return *this;
    }

    // 设置颜色回调
    ColorPickerComponent& SetOnChangeCallback(std::function<void(const std::array<float, 4>&)> callback) {
        _onChangeCallback = std::move(callback);
        return *this;
    }

    // 设置可见性
    ColorPickerComponent& SetVisible(std::function<bool(const TState&)> stateFunc) {
        _visible = ValueProvider<bool>(stateFunc);
        return *this;
    }

    // 获取当前颜色
    const std::array<float, 4>& GetColor() const { return _color; }

private:
    StringProvider _label;
    std::array<float, 4> _color{1.0f, 1.0f, 1.0f, 1.0f}; // 默认白色
    std::function<void(const std::array<float, 4>&)> _onChangeCallback;
    ValueProvider<bool> _visible{true};
};

} // namespace Sharingan

#endif // COLORPICKERCOMPONENT_HPP
