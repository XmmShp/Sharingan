#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP

#include "WindowComponent.hpp"
#include <imgui.h>
#include <string>
#include <utility>

namespace Sharingan
{
template<typename TState>
class TextComponent : public WindowComponent<TState>
{
public:
    TextComponent() = default;

    void Render() override
    {
        if (_visible(this->_state)) {
            ImGui::Text("%s", _text(this->_state).c_str());
        }
    }

    // 支持直接值
    TextComponent& SetText(const std::string& text) {
        _text = StringProvider(text);
        return *this;
    }

    // 支持状态感知lambda
    TextComponent& SetText(std::function<std::string(const TState&)> stateFunc) {
        _text = StringProvider(stateFunc);
        return *this;
    }

    // 设置可见性
    TextComponent& SetVisible(std::function<bool(const TState&)> stateFunc) {
        _visible = ValueProvider<bool>(stateFunc);
        return *this;
    }

private:
    StringProvider _text{""};
    ValueProvider<bool> _visible{true};
};
} // namespace Sharingan

#endif // TEXTCOMPONENT_HPP
