#ifndef INPUTTEXTCOMPONENT_HPP
#define INPUTTEXTCOMPONENT_HPP

#include "WindowComponent.hpp"
#include <imgui.h>
#include <string>
#include <vector>
#include <utility>
#include <functional>

namespace Sharingan
{
template<typename TState>
class InputTextComponent : public WindowComponent<TState>
{
public:
    InputTextComponent() : _label(""), _buffer(256, '\0'), _onChangeCallback(nullptr), _visible(true)
    {
    }

    explicit InputTextComponent(StringProvider label, std::function<void(const std::string&)> onChangeCallback = nullptr)
        : _label(std::move(label)), _onChangeCallback(std::move(onChangeCallback))
    {
        _buffer.resize(256); // Default buffer size
    }

    void Render() override
    {
        if (_visible(this->_state)) {
            if (ImGui::InputText(_label(this->_state).c_str(), _buffer.data(), _buffer.size())) {
                if (_onChangeCallback) {
                    _onChangeCallback(_buffer.data());
                }
            }
        }
    }

    // 设置标签
    InputTextComponent& SetLabel(const std::string& label) {
        _label = StringProvider(label);
        return *this;
    }

    InputTextComponent& SetLabel(std::function<std::string(const TState&)> stateFunc) {
        _label = StringProvider(stateFunc);
        return *this;
    }

    // 设置缓冲区大小
    InputTextComponent& SetBufferSize(size_t size) {
        _buffer.resize(size);
        return *this;
    }

    // 设置回调函数
    InputTextComponent& SetOnChangeCallback(std::function<void(const std::string&)> callback) {
        _onChangeCallback = std::move(callback);
        return *this;
    }

    // 设置可见性
    InputTextComponent& SetVisible(std::function<bool(const TState&)> stateFunc) {
        _visible = ValueProvider<bool>(stateFunc);
        return *this;
    }

private:
    StringProvider _label;
    std::vector<char> _buffer;
    std::function<void(const std::string&)> _onChangeCallback;
    ValueProvider<bool> _visible{true};
};

} // namespace Sharingan

#endif // INPUTTEXTCOMPONENT_HPP
