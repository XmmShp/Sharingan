#ifndef INPUTTEXTCOMPONENT_HPP
#define INPUTTEXTCOMPONENT_HPP

#include "WindowComponent.hpp"
#include <imgui.h>
#include <string>
#include <utility>
#include <functional>
#include <vector>

namespace Sharingan
{
template<typename TState>
class InputTextComponent : public WindowComponent<TState>
{
public:
    using OnChangeCallback = std::function<void(InputTextComponent&, const std::string&)>;

    InputTextComponent() : _bufferSize(256), _onChangeCallback(nullptr)
    {
    }

    void Render() override
    {
        if (!_valueBinder) return;
        if (this->IsVisible()) {
            std::string& text = _valueBinder(*const_cast<TState*>(this->_state));
            std::vector<char> buffer(text.begin(), text.end());
            buffer.resize(_bufferSize);

            if (ImGui::InputText(this->GetLabel().c_str(), buffer.data(), buffer.size())) {
                text = buffer.data();
                if (_onChangeCallback) {
                    _onChangeCallback(*this, text);
                }
            }
        }
    }

    // 设置值路由
    InputTextComponent& SetValueRoute(std::function<std::string&(TState&)> valueBinder) {
        _valueBinder = std::move(valueBinder);
        return *this;
    }

    // 设置缓冲区大小
    InputTextComponent& SetBufferSize(size_t size) {
        _bufferSize = size;
        return *this;
    }

    // 设置回调函数
    InputTextComponent& SetOnChangeCallback(OnChangeCallback callback) {
        _onChangeCallback = std::move(callback);
        return *this;
    }

private:
    size_t _bufferSize;
    OnChangeCallback _onChangeCallback;
    std::function<std::string&(TState&)> _valueBinder;
};

} // namespace Sharingan

#endif // INPUTTEXTCOMPONENT_HPP
