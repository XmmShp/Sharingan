#ifndef BUTTONCOMPONENT_HPP
#define BUTTONCOMPONENT_HPP

#include "WindowComponent.hpp"
#include <imgui.h>
#include <string>
#include <utility>
#include <functional>

namespace Sharingan
{
template<typename TState>
class ButtonComponent : public WindowComponent<TState>
{
public:
    using OnClickCallback = std::function<void(ButtonComponent&)>;

    // 默认构造函数
    ButtonComponent() = default;

    void Render() override
    {
        if (this->IsVisible()) {
            if (ImGui::Button(this->GetLabel().c_str())) { 
                if (_callback) _callback(*this); 
            }
        }
    }

    ButtonComponent& SetCallback(OnClickCallback callback) {
        _callback = std::move(callback);
        return *this;
    }

private:
    OnClickCallback _callback;
};

} // namespace Sharingan

#endif // BUTTONCOMPONENT_HPP
