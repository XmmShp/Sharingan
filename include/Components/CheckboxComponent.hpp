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
    CheckboxComponent() : _label(""), _checked(false), _onChangeCallback(nullptr), _visible(true)
    {
    }

    explicit CheckboxComponent(StringProvider label, std::function<void(bool)> onChangeCallback = nullptr)
        : _label(std::move(label))
        , _onChangeCallback(std::move(onChangeCallback))
    {
    }

    void Render() override
    {
        if (_visible(this->_state)) {
            if (ImGui::Checkbox(_label(this->_state).c_str(), &_checked)) {
                if (_onChangeCallback) {
                    _onChangeCallback(_checked);
                }
            }
        }
    }

    // 设置标签
    CheckboxComponent& SetLabel(const std::string& label) {
        _label = StringProvider(label);
        return *this;
    }

    CheckboxComponent& SetLabel(std::function<std::string(const TState&)> stateFunc) {
        _label = StringProvider(stateFunc);
        return *this;
    }

    // 设置选中状态
    CheckboxComponent& SetChecked(bool checked) {
        _checked = checked;
        return *this;
    }

    // 设置回调函数
    CheckboxComponent& SetOnChangeCallback(std::function<void(bool)> callback) {
        _onChangeCallback = std::move(callback);
        return *this;
    }

    // 设置可见性
    CheckboxComponent& SetVisible(bool visible) {
        _visible = ValueProvider<bool>(visible);
        return *this;
    }

    CheckboxComponent& SetVisible(std::function<bool(const TState&)>& stateFunc) {
        _visible = ValueProvider<bool>(stateFunc);
        return *this;
    }

    // 获取当前状态
    bool IsChecked() const { return _checked; }

private:
    StringProvider _label;
    bool _checked{false};
    std::function<void(bool)> _onChangeCallback;
    ValueProvider<bool> _visible{true};
};

} // namespace Sharingan

#endif // CHECKBOXCOMPONENT_HPP
