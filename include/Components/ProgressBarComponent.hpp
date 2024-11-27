#ifndef PROGRESSBARCOMPONENT_HPP
#define PROGRESSBARCOMPONENT_HPP

#include "WindowComponent.hpp"
#include <imgui.h>
#include <string>
#include <functional>
#include <optional>

namespace Sharingan
{
template<typename TState>
class ProgressBarComponent : public WindowComponent<TState>
{
public:
    ProgressBarComponent() 
        : _fraction(0.0f)
        , _size{ImVec2(-FLT_MIN, 0)}
    {
    }

    void Render() override
    {
        if (this->IsVisible()) {
            ImGui::PushID(this);
            const std::string& label = this->GetLabel();
            ImGui::ProgressBar(
                _fraction(this->_state), 
                _size(this->_state), 
                _overlayText.has_value() ? _overlayText.value()(this->_state).c_str() : nullptr
            );
            ImGui::PopID();
        }
    }

    // 设置进度 (0.0-1.0)
    ProgressBarComponent& SetFraction(float fraction) {
        _fraction = ValueProvider<float>(fraction);
        return *this;
    }

    ProgressBarComponent& SetFraction(std::function<float(const TState&)> stateFunc) {
        _fraction = ValueProvider<float>(stateFunc);
        return *this;
    }

    // 设置大小
    ProgressBarComponent& SetSize(const ImVec2& size) {
        _size = ValueProvider<ImVec2>(size);
        return *this;
    }

    ProgressBarComponent& SetSize(std::function<ImVec2(const TState&)> stateFunc) {
        _size = ValueProvider<ImVec2>(stateFunc);
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

private:
    ValueProvider<float> _fraction;
    ValueProvider<ImVec2> _size;
    std::optional<StringProvider> _overlayText;
};

} // namespace Sharingan

#endif // PROGRESSBARCOMPONENT_HPP
