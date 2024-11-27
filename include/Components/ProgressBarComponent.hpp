#ifndef PROGRESSBARCOMPONENT_HPP
#define PROGRESSBARCOMPONENT_HPP

#include "WindowComponent.hpp"
#include <imgui.h>
#include <string>
#include <functional>
#include <algorithm>
#include <optional>

namespace Sharingan
{
template<typename TState>
class ProgressBarComponent : public WindowComponent<TState>
{
public:
    ProgressBarComponent() 
        : _label("")
        , _fraction(0.0f)
        , _size{-FLT_MIN, 0}
        , _visible([](const TState&) { return true; })
    {
    }

    explicit ProgressBarComponent(StringProvider label, float fraction = 0.0f,
                                const ImVec2& size = ImVec2(-FLT_MIN, 0))
        : _label(std::move(label))
        , _fraction(fraction)
        , _size(size)
        , _visible([](const TState&) { return true; })
    {
    }

    void Render() override
    {
        if (_visible(this->_state)) {
            ImGui::PushID(this);
            const std::string& label = _label(this->_state);
            ImGui::ProgressBar(_fraction, _size, _overlayText.has_value() ? _overlayText.value()(this->_state).c_str() : nullptr);
            ImGui::PopID();
        }
    }

    // 设置标签
    ProgressBarComponent& SetLabel(const std::string& label) {
        _label = StringProvider(label);
        return *this;
    }

    ProgressBarComponent& SetLabel(std::function<std::string(const TState&)> stateFunc) {
        _label = StringProvider(stateFunc);
        return *this;
    }

    // 设置进度 (0.0-1.0)
    ProgressBarComponent& SetFraction(float fraction) {
        _fraction = std::clamp(fraction, 0.0f, 1.0f);
        return *this;
    }

    // 设置大小
    ProgressBarComponent& SetSize(const ImVec2& size) {
        _size = size;
        return *this;
    }

    // 设置覆盖文本
    ProgressBarComponent& SetOverlayText(const std::string& text) {
        _overlayText = StringProvider(text);
        return *this;
    }

    ProgressBarComponent& SetOverlayText(std::function<std::string(const TState&)> stateFunc) {
        _overlayText = StringProvider(stateFunc);
        return *this;
    }

    // 设置可见性
    ProgressBarComponent& SetVisible(std::function<bool(const TState&)> stateFunc) {
        _visible = ValueProvider<bool>(stateFunc);
        return *this;
    }

    // 获取当前进度
    float GetFraction() const { return _fraction; }

private:
    StringProvider _label;
    float _fraction;
    ImVec2 _size;
    ValueProvider<bool> _visible;
    std::optional<StringProvider> _overlayText;
};

} // namespace Sharingan

#endif // PROGRESSBARCOMPONENT_HPP
