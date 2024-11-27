#ifndef BUTTONCOMPONENT_HPP
#define BUTTONCOMPONENT_HPP

#include "ImGuiDialogComponent.h"
#include <imgui.h>
#include <string>
#include <utility>
#include <functional>

template <typename TState>
class ButtonComponent : public ImGuiDialogComponent<TState>
{
template<typename TState>
class ButtonComponent : public WindowComponent<TState>
{
public:
    // 默认构造函数
    ButtonComponent() = default;

    void Render() override
    {
        if (ImGui::Button(_title(this->_state).c_str())) { 
            if (_callback) _callback(); 
        }
    }

    // 支持直接值
    ButtonComponent& SetTitle(const std::string& title) {
        _title = StringProvider(title);
        return *this;
    }

    // 支持状态感知lambda
    ButtonComponent& SetTitle(std::function<std::string(const TState&)> stateFunc) {
        _title = StringProvider(stateFunc);
        return *this;
    }

    ButtonComponent& SetCallback(Callback callback) {
        _callback = std::move(callback);
        return *this;
    }

private:
    StringProvider _title{""};  // 默认空字符串
    Callback _callback;
    std::shared_ptr<TState> _state;
};

} // namespace Sharingan

#endif // BUTTONCOMPONENT_HPP
