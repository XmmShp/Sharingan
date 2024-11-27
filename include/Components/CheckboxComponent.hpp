#ifndef CHECKBOXCOMPONENT_HPP
#define CHECKBOXCOMPONENT_HPP

#include "WindowComponent.hpp"
#include <imgui.h>
#include <string>
#include <utility>
#include <functional>

namespace Sharingan
{
template<typename TState>
class CheckboxComponent : public WindowComponent<TState>
{
public:
    using OnChangeCallback = std::function<void(CheckboxComponent&, bool)>;

    CheckboxComponent() : _onChangeCallback(nullptr)
    {
    }

    void Render() override
    {
        if (!_valueBinder) return;
        if (this->IsVisible()) {
            bool& checked = _valueBinder(*const_cast<TState*>(this->_state));
            if (ImGui::Checkbox(this->GetLabel().c_str(), &checked)) {
                if (_onChangeCallback) {
                    _onChangeCallback(*this, checked);
                }
            }
        }
    }

    // 设置值路由
    CheckboxComponent& SetValueRoute(std::function<bool&(TState&)> valueBinder) {
        _valueBinder = std::move(valueBinder);
        return *this;
    }

    // 设置回调函数
    CheckboxComponent& SetOnChangeCallback(OnChangeCallback callback) {
        _onChangeCallback = std::move(callback);
        return *this;
    }

private:
    OnChangeCallback _onChangeCallback;
    std::function<bool&(TState&)> _valueBinder;
};

} // namespace Sharingan

#endif // CHECKBOXCOMPONENT_HPP
