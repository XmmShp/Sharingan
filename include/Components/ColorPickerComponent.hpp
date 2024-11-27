#ifndef COLORPICKERCOMPONENT_HPP
#define COLORPICKERCOMPONENT_HPP

#include "WindowComponent.hpp"
#include <imgui.h>
#include <string>
#include <array>
#include <utility>
#include <functional>

namespace Sharingan
{
template<typename TState>
class ColorPickerComponent : public WindowComponent<TState>
{
public:
    using OnChangeCallback = std::function<void(ColorPickerComponent&, const std::array<float, 4>&)>;

    ColorPickerComponent() : _onChangeCallback(nullptr)
    {
    }

    void Render() override
    {
        if (!_valueBinder) return;
        if (this->IsVisible()) {
            auto& color = _valueBinder(*const_cast<TState*>(this->_state));
            if (ImGui::ColorPicker4(this->GetLabel().c_str(), color.data())) {
                if (_onChangeCallback) {
                    _onChangeCallback(*this, color);
                }
            }
        }
    }

    // 设置值路由
    ColorPickerComponent& SetValueRoute(std::function<std::array<float, 4>&(TState&)> valueBinder) {
        _valueBinder = std::move(valueBinder);
        return *this;
    }

    // 设置回调函数
    ColorPickerComponent& SetOnChangeCallback(OnChangeCallback callback) {
        _onChangeCallback = std::move(callback);
        return *this;
    }

private:
    OnChangeCallback _onChangeCallback;
    std::function<std::array<float, 4>&(TState&)> _valueBinder;
};

} // namespace Sharingan

#endif // COLORPICKERCOMPONENT_HPP
